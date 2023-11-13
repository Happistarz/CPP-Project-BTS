#include "Simulator.h"

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
		earth.setScale(0.8f,0.8f);
		earth.setPosition(
			HELPER::getShapePosition(
				sky.getPosition(),
				sky.getSize(),
				sf::Vector2f(earth.getGlobalBounds().width, earth.getGlobalBounds().height)
			)
		);

		satelliteTexture.loadFromFile(root + "data/assets/satellite.png");
		satellite.setTexture(satelliteTexture);
		satellite.setScale(0.2f, 0.2f);
		satellite.setPosition(
			HELPER::getXShapePosition(
				sky.getPosition(),
				sky.getSize(),
				sf::Vector2f(satellite.getGlobalBounds().width, satellite.getGlobalBounds().height)
			) + sf::Vector2f(0.f, 10.f)
		);

		stationTexture.loadFromFile(root + "data/assets/station.png");
		station.setTexture(stationTexture);
		station.setScale(0.2f, 0.2f);
		station.setPosition(
			HELPER::getXShapePosition(
				sky.getPosition(),
				sky.getSize(),
				sf::Vector2f(station.getGlobalBounds().width, station.getGlobalBounds().height)
			) + sf::Vector2f(0.f, 60.f)
		);
	}

	Simulator::~Simulator() {

	}

	void Simulator::draw(sf::RenderWindow& window) {
		window.draw(sky);
		window.draw(earth);
		window.draw(satellite);
		window.draw(station);
	}
}