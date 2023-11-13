#include "StationRender.h"

namespace GRAPHICS {
	StationRender::StationRender(sf::RenderWindow& window) {
		sf::Vector2f backgroundSize(window.getSize().x / 3, window.getSize().y / 2);
		float borderSize = 2.f;
		background.setSize(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 2));
		background.setPosition(window.getSize().x / 1.5, 0.f);
		background.setFillColor(sf::Color::Green);

		stationBox.setSize(backgroundSize - sf::Vector2f(20.f, 10.f));
		stationBox.setPosition(
			HELPER::getXShapePosition(
				background.getPosition(),
				backgroundSize,
				stationBox.getSize() + sf::Vector2f(borderSize, borderSize)
			) 
			+ sf::Vector2f(0.f, 10.f)
		);
		stationBox.setFillColor(sf::Color::Black);
		stationBox.setOutlineThickness(borderSize);
		stationBox.setOutlineColor(sf::Color::White);
	}

	StationRender::~StationRender() {

	}

	void StationRender::draw(sf::RenderWindow& window) {
		//window.draw(background);
		window.draw(stationBox);
	}
}