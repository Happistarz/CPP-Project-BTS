#include "SatelliteRender.h"

namespace GRAPHICS {
	SatelliteRender::SatelliteRender(sf::RenderWindow& window) {
		sf::Vector2f backgroundSize(window.getSize().x / 3, window.getSize().y / 2);
		float borderSize = 2.f;
		background.setSize(backgroundSize);
		background.setPosition(window.getSize().x / 1.5, window.getSize().y / 2);
		background.setFillColor(sf::Color::Cyan);

		satelliteBox.setSize(backgroundSize - sf::Vector2f(20.f, 10.f));
		satelliteBox.setPosition(
			HELPER::getXShapePosition(
				background.getPosition(),
				backgroundSize,
				satelliteBox.getSize() + sf::Vector2f(borderSize,borderSize)
			)
		);

		satelliteBox.setFillColor(sf::Color::Black);
		satelliteBox.setOutlineThickness(borderSize);
		satelliteBox.setOutlineColor(sf::Color::White);
	}

	SatelliteRender::~SatelliteRender() {

	}

	void SatelliteRender::draw(sf::RenderWindow& window) {
		//window.draw(background);
		window.draw(satelliteBox);
	}
}