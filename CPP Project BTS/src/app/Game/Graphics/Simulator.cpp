#include "Simulator.h"

const float M_PI = 3.14159265358979323846f;

const float TOTALKM = 42171.f;
const float TOTALPIXELRADIUS = 512.f;
const float EARTHRADIUS = 6371.f;
const float EARTHPIXELPNG = 512.f;
const float SATELLITESPEED = 0.0134f;
const float EARTHSPEED = 0.005f;

const float KMPERPIXEL = TOTALKM / TOTALPIXELRADIUS;
const float EARTHPIXELRADIUS = EARTHRADIUS / KMPERPIXEL;
const float EARTHPIXELRADIUSRATIO = EARTHPIXELRADIUS / (EARTHPIXELPNG / 2);

float angleSAT = 90.f;
float angleSTAorbit = 90.f;
float angleSTA = 0.f;

namespace GRAPHICS {
	Simulator::Simulator(sf::RenderWindow& window, std::string& root, READER::JsonReader& jsonReader) : drawLineConnection(false) {
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
		earth.setOrigin( earth.getLocalBounds().getSize() / 2.f );
		earth.setPosition(
			HELPER::getShapePosition(
				sky.getPosition(),
				sky.getSize(),
				sf::Vector2f()
			)
		);

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
			) - sf::Vector2f(0.f, TOTALPIXELRADIUS)
		);

		stationTexture.loadFromFile(root + "data/assets/station.png");
		station.setTexture(stationTexture);
		station.setScale(0.15f, 0.15f);
		station.setOrigin( station.getGlobalBounds().getSize() / 2.f );
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

		// line connecting satellite and station, the size of the line is the distance between the two
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

	Simulator::~Simulator() {

	}

	void Simulator::draw(sf::RenderWindow& window) {
		window.draw(sky);
		window.draw(satelliteOrbit);
		window.draw(satellite);
		window.draw(earth);
		window.draw(station);
		//window.draw(debug);
		window.draw(lineConnection);
	}

	void Simulator::update(float deltaTime) {
		//// update satellite position
		//angleSAT += (.5f * deltaTime) / TOTALPIXEL;

		//float xa= TOTALPIXEL * cos(angleSAT);
		//float ya= TOTALPIXEL * sin(angleSAT);

		////float rot = -atan2(y, x) * 180 / M_PI

		//satellite.setPosition(
		//	HELPER::getShapePosition(
		//		sky.getPosition(),
		//		sky.getSize(),
		//		satellite.getGlobalBounds().getSize()
		//	) - sf::Vector2f(xa, ya)
		//);
		////satellite.rotate(1.0f);

		//lineConnection.setPosition(
		//	HELPER::getShapePosition(
		//		sky.getPosition(),
		//		sky.getSize(),
		//		lineConnection.getGlobalBounds().getSize()
		//	) - sf::Vector2f(xa, ya)
		//);

		//lineConnection.setRotation(atan2(ya, xa) * 180 / M_PI);

		//angleSTAorbit += (.05f * deltaTime) / EARTHPIXELRADIUS;
		//angleSTA += (.1f * deltaTime);

		//float xb = EARTHPIXELRADIUS * cos(angleSTAorbit);
		//float yb = EARTHPIXELRADIUS * sin(angleSTAorbit);

		//sf::Transform transform;
		//transform.rotate(angleSTA);

		//sf::Vector2f pos = HELPER::getShapePosition(
		//	sky.getPosition(),
		//	sky.getSize(),
		//	station.getGlobalBounds().getSize()
		//) - sf::Vector2f(xb, yb);

		//pos = transform.transformPoint(pos);

		//station.setPosition(pos);
		//station.setRotation(angleSTA);

		//debug.setPosition(
		//	HELPER::getShapePosition(
		//		sky.getPosition(),
		//		sky.getSize(),
		//		debug.getGlobalBounds().getSize()
		//	) - sf::Vector2f(xb, yb)
		//);

		angleSAT += 0.005 * deltaTime;
		angleSTAorbit += 0.003 * deltaTime;

		sf::Vector2f earthCenter = earth.getPosition() + sf::Vector2f(earth.getGlobalBounds().width / 2, earth.getGlobalBounds().height / 2);

		sf::Vector2f satellitePosition = sf::Vector2f(
			earthCenter.x + cos(angleSAT) * TOTALPIXELRADIUS,
			earthCenter.y + sin(angleSAT) * TOTALPIXELRADIUS
		);

		satellite.setPosition(
			HELPER::getShapePosition(
				sky.getPosition(),
				sky.getSize(),
				satellite.getGlobalBounds().getSize()
			)
		);

		sf::Vector2f stationPosition = sf::Vector2f(
			earthCenter.x + cos(angleSTAorbit) * EARTHPIXELRADIUS,
			earthCenter.y + sin(angleSTAorbit) * EARTHPIXELRADIUS
		);

		station.setPosition(stationPosition - sf::Vector2f(station.getGlobalBounds().width / 2, station.getGlobalBounds().height / 2));
		
		sf::Vector2f direction = satellite.getPosition() - station.getPosition();
		float angle = atan2(direction.y, direction.x) * 180 / M_PI;
		station.setRotation(angle + 90.f);

		direction = station.getPosition() - satellite.getPosition();
		angle = atan2(direction.y, direction.x) * 180 / M_PI;
		satellite.setRotation(angle + 90.f);


		//debug.rotate(1.f);
		earth.rotate(.05f);
		//station.rotate(.3f);
	}
}