#include "Simulator.h"

const float M_PI = 3.14159265358979323846f;

const float TOTALKM = 42171.f;
const float TOTALPIXEL = 512.f;
const float EARTHRADIUS = 6371.f;
const float EARTHPIXELPNG = 512.f;
const float SATELLITESPEED = 0.0134f;
const float EARTHSPEED = 0.005f;

const float KMPERPIXEL = TOTALKM / TOTALPIXEL;
const float EARTHPIXELRADIUS = EARTHRADIUS / KMPERPIXEL;
const float EARTHPIXELRADIUSRATIO = EARTHPIXELRADIUS / (EARTHPIXELPNG / 2);

float angleSAT = 90.f;
float rotSAT = 180.f;

namespace GRAPHICS {
	Simulator::Simulator(sf::RenderWindow& window, std::string& root, READER::JsonReader& jsonReader) {
		sf::Vector2f backgroundSize(window.getSize().x / 1.5, window.getSize().y);
		float borderSize = 2.f;

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

		earthTexture.loadFromFile(root + "data/assets/earth.png");
		earth.setTexture(earthTexture);
		earth.setScale(EARTHPIXELRADIUSRATIO, EARTHPIXELRADIUSRATIO);
		earth.setOrigin(
			earth.getLocalBounds().width / 2,
			earth.getLocalBounds().height / 2
		);
		earth.setPosition(
			HELPER::getShapePosition(
				sky.getPosition(),
				sky.getSize(),
				sf::Vector2f()
			)
		);

		satelliteOrbit.setRadius(TOTALPIXEL);
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

		satelliteTexture.loadFromFile(root + "data/assets/satellite.png");
		satellite.setTexture(satelliteTexture);
		satellite.setScale(0.15f, 0.15f);
		//satellite.setOrigin(
		//	satellite.getLocalBounds().width / 2,
		//	satellite.getLocalBounds().height / 2
		//);
		satellite.setRotation(180.f);
		satellite.setPosition(
			HELPER::getShapePosition(
				sky.getPosition(),
				sky.getSize(),
				satellite.getGlobalBounds().getSize()
			) - sf::Vector2f(0.f, TOTALPIXEL)
		);

		stationTexture.loadFromFile(root + "data/assets/station.png");
		station.setTexture(stationTexture);
		station.setScale(0.15f, 0.15f);

		station.setPosition(
			HELPER::getShapePosition(
				sky.getPosition(),
				sky.getSize(),
				station.getGlobalBounds().getSize()
			) - sf::Vector2f(0.f, EARTHPIXELRADIUS)
		);


		debug.setFillColor(sf::Color::Transparent);
		debug.setOutlineThickness(1.f);
		debug.setOutlineColor(sf::Color::Red);
		debug.setSize(station.getGlobalBounds().getSize());
		debug.setPosition(
			station.getPosition()
		);
	}

	Simulator::~Simulator() {

	}

	void Simulator::draw(sf::RenderWindow& window) {
		window.draw(sky);
		window.draw(satelliteOrbit);
		window.draw(satellite);
		window.draw(earth);
		window.draw(station);
		window.draw(debug);
	}

	void Simulator::update(float deltaTime) {
		// update satellite position
		angleSAT += (1.0f * deltaTime) / TOTALPIXEL;

		float x = TOTALPIXEL * cos(angleSAT);
		float y = TOTALPIXEL * sin(angleSAT);

		//float rot = -atan2(y, x) * 180 / M_PI

		satellite.setPosition(
			HELPER::getShapePosition(
				sky.getPosition(),
				sky.getSize(),
				sf::Vector2f(satellite.getGlobalBounds().width, satellite.getGlobalBounds().height)
			) - sf::Vector2f(x, y)
		);

		//satellite.rotate(1.f);

		// update earth rotation with rotate()

		//angleEARTH += (EARTHSPEED * deltaTime) / EARTHPIXELRADIUS;


		//debug.rotate(1.f);
		//earth.rotate(1.0f);
	}
}