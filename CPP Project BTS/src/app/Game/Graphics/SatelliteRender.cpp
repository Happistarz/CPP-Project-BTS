#include "SatelliteRender.h"


sf::Vector2f BUTTON_SIZE = sf::Vector2f(100.f,25.f);

namespace GRAPHICS {
	SatelliteRender::SatelliteRender(sf::RenderWindow& window, sf::Font& font) {
		satellite->startListening();


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

		ping = new UI::Button(
			HELPER::getXShapePosition(
				background.getPosition(),
				backgroundSize,
				BUTTON_SIZE
			),
			BUTTON_SIZE,
			"Ping",
			font,
			24U,
			window,
			[this]() {pingCommunicable(); }
		);

		send = new UI::Button(
			HELPER::getXShapePosition(
				background.getPosition(),
				backgroundSize,
				BUTTON_SIZE
			) + sf::Vector2f(0.f, backgroundSize.y),
			BUTTON_SIZE,
			"Send",
			font,
			24U,
			window,
			[this]() {sendCommunicable("MESSAGE DE LA FRANCE OUI"); }
		);
	}

	SatelliteRender::~SatelliteRender() {

	}

	void SatelliteRender::draw(sf::RenderWindow& window) {
		//window.draw(background);
		window.draw(satelliteBox);
	}

	void SatelliteRender::pingCommunicable() {
		satellite->sendMessage("Ping");
	}

	void SatelliteRender::sendCommunicable(std::string msg) {
		satellite->sendMessage(msg);
	}
}