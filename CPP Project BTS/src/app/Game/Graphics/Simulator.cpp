#include "Simulator.h"

const float M_PI = 3.14159265358979323846f;

const float TOTALKM = 42171.f;
const float TOTALPIXEL = 512.f;
const float TOTALPIXELRADIUS = 512.f;
const float EARTHRADIUS = 6371.f;
const float EARTHPIXELPNG = 512.f;
const float SATELLITESPEED = 0.055f;
const float EARTHSPEED = 0.008f;

const float KMPERPIXEL = TOTALKM / TOTALPIXELRADIUS;
const float EARTHPIXELRADIUS = EARTHRADIUS / KMPERPIXEL;
const float EARTHPIXELRADIUSRATIO = EARTHPIXELRADIUS / (EARTHPIXELPNG / 2);

float angleSAT = 90.f;
float angleSTA = 90.f;
int displayLine = 0;
int bufferLine = 0;

namespace GRAPHICS {
	Simulator::Simulator(sf::RenderWindow& window, std::string& root, READER::JsonReader& jsonReader) : drawLineConnection(false) {

		// initialisation des objets
		sf::Vector2f backgroundSize(window.getSize().x / 1.5, window.getSize().y);
		float borderSize = 2.f;

		// initialisation des formes

		// sky
		sky.setSize(backgroundSize - sf::Vector2f(20.f, 20.f));
		sky.setFillColor(sf::Color(7, 22, 48));
		sky.setOutlineThickness(borderSize);
		sky.setOutlineColor(sf::Color::White);

		sky.setPosition(
			HELPER::getShapePosition(
				sf::Vector2f(),
				backgroundSize,
				sky.getSize() + sf::Vector2f(borderSize, borderSize)
			)
		);

		// earth
		earthTexture.loadFromFile(root + "data/assets/earth.png");
		earth.setTexture(earthTexture);
		earth.setScale(EARTHPIXELRADIUSRATIO, EARTHPIXELRADIUSRATIO);
		earth.setOrigin(earth.getLocalBounds().getSize() / 2.f);
		earth.setPosition(
			HELPER::getShapePosition(
				sky.getPosition(),
				sky.getSize(),
				sf::Vector2f()
			)
		);

		// satelliteOrbit
		satelliteOrbit.setRadius(TOTALPIXELRADIUS);
		satelliteOrbit.setPointCount(100);
		satelliteOrbit.setFillColor(sf::Color::Transparent);
		satelliteOrbit.setOutlineThickness(1.f);
		satelliteOrbit.setOutlineColor(sf::Color::White);
		satelliteOrbit.setPosition(
			HELPER::getShapePosition(
				sky.getPosition(),
				sky.getSize(),
				satelliteOrbit.getGlobalBounds().getSize()
			)
		);

		// satellite
		satelliteTexture.loadFromFile(root + "data/assets/satellite.png");
		satellite.setTexture(satelliteTexture);
		satellite.setScale(0.15f, 0.15f);
		satellite.setOrigin(satellite.getGlobalBounds().getSize() / 2.f);
		satellite.setRotation(180.f);
		satellite.setPosition(
			HELPER::getShapePosition(
				sky.getPosition(),
				sky.getSize(),
				satellite.getGlobalBounds().getSize()
			) + satellite.getOrigin()
		);

		// station
		stationTexture.loadFromFile(root + "data/assets/station.png");
		station.setTexture(stationTexture);
		station.setScale(0.15f, 0.15f);
		station.setOrigin(station.getLocalBounds().getSize() * 0.5f);
		station.setPosition(
			HELPER::getShapePosition(
				sky.getPosition(),
				sky.getSize(),
				station.getGlobalBounds().getSize()
			) - sf::Vector2f(0.f, EARTHPIXELRADIUS) + station.getOrigin()
		);

		// lineConnection
		lineConnection.setFillColor(sf::Color::Red);
		lineConnection.setSize(sf::Vector2f(5.f, TOTALPIXELRADIUS - EARTHPIXELRADIUS));
		lineConnection.setOrigin(lineConnection.getSize() / 2.f);
		lineConnection.setPosition(
			HELPER::getShapePosition(
				sky.getPosition(),
				sky.getSize(),
				lineConnection.getGlobalBounds().getSize()
			) - sf::Vector2f(0.f, EARTHPIXELRADIUS)
		);

	}

	Simulator::~Simulator() {}

	void Simulator::draw(sf::RenderWindow& window) {
		// affiche les formes
		window.draw(sky);
		window.draw(earth);
		window.draw(satelliteOrbit);
		window.draw(satellite);
		window.draw(station);

		// affiche la ligne de connexion si il y a un signal envoye pendant 1s
		if (drawLineConnection && displayLine < bufferLine * 60) {
			window.draw(lineConnection);
			displayLine++;
		} 
		else {
			drawLineConnection = false;
			displayLine = 0;
			bufferLine = 0;
		}
	}

	void Simulator::setDrawLineConnection(bool drawLineConnection, int time)
	{
		this->drawLineConnection = drawLineConnection;
		bufferLine += time;
	}

	void Simulator::update(float deltaTime) {
		angleSAT += (SATELLITESPEED * deltaTime) / TOTALPIXEL;

		float xa= TOTALPIXEL * cos(angleSAT);
		float ya= TOTALPIXEL * sin(angleSAT);

		satellite.setPosition(
			HELPER::getShapePosition(
				sky.getPosition(),
				sky.getSize(),
				satellite.getGlobalBounds().getSize()
			) - sf::Vector2f(xa, ya) + satellite.getOrigin()
		);


		angleSTA += (EARTHSPEED * deltaTime) / EARTHPIXELRADIUS;

		float xb = EARTHPIXELRADIUS * cos(angleSTA);
		float yb = EARTHPIXELRADIUS * sin(angleSTA);

		sf::Vector2f pos = HELPER::getShapePosition(
			sky.getPosition(),
			sky.getSize(),
			station.getGlobalBounds().getSize()
		) - sf::Vector2f(xb, yb);

		station.setPosition(pos);

		sf::Vector2f direction = station.getPosition() - satellite.getPosition();
		float angle = atan2(direction.y, direction.x) * 180 / M_PI;
		satellite.setRotation(angle + 90.f);

		earth.rotate(EARTHSPEED * deltaTime);


		lineConnection.setPosition(
			HELPER::getShapePosition(
				sky.getPosition(),
				sky.getSize(),
				station.getGlobalBounds().getSize()
			) - sf::Vector2f(xb, yb) - direction / 2.f
		);

		direction = satellite.getPosition() - station.getPosition();
		angle = atan2(direction.y, direction.x) * 180 / M_PI;

		lineConnection.setRotation(angle + 90.f);
	}
}