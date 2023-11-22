#include "SatelliteRender.h"

unsigned int charSize = 20U;
unsigned int LOGLINECOUNT = 10U;
unsigned int LOGLINESIZE = 25U;

sf::Vector2f BUTTON_SIZE = sf::Vector2f(175.f, 50.f);
sf::Vector2f TEXTBOX_SIZE = sf::Vector2f(150.f, 50.f);
sf::Vector2f LOG_SIZE = sf::Vector2f(charSize * LOGLINESIZE + 10.f, charSize * LOGLINECOUNT + 10.f);

sf::Color CONNECTED_COLOR = sf::Color(0, 255, 0);
sf::Color DISCONNECTED_COLOR = sf::Color(255, 0, 0);

int t = 0;
int a = 0;

namespace GRAPHICS {
	SatelliteRender::SatelliteRender(sf::RenderWindow& window, sf::Font& font) {
		satellite = new METIER::Satellite("127.0.0.1", 5000);
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
				satelliteBox.getSize() + sf::Vector2f(borderSize, borderSize)
			)
		);

		satelliteBox.setFillColor(sf::Color::Black);
		satelliteBox.setOutlineThickness(borderSize);
		satelliteBox.setOutlineColor(sf::Color::White);

		ping = new UI::Button(
			HELPER::getXShapePosition(
				background.getPosition(),
				backgroundSize / 2.f,
				BUTTON_SIZE
			) + sf::Vector2f(0.f, satelliteBox.getGlobalBounds().height / 1.3f),
			BUTTON_SIZE,
			"Ping",
			font,
			charSize,
			window,
			[this]() {pingCommunicable(); }
		);

		send = new UI::Button(
			HELPER::getXShapePosition(
				sf::Vector2f(background.getPosition().x + backgroundSize.x / 2.f, background.getPosition().y),
				backgroundSize / 2.f,
				BUTTON_SIZE
			) + sf::Vector2f(0.f, satelliteBox.getGlobalBounds().height / 1.3f),
			BUTTON_SIZE,
			"Send",
			font,
			charSize,
			window,
			[this]() {sendCommunicable("MESSAGE DE LA FRANCE OUI"); }
		);


		connect = new UI::TextBox(
			HELPER::getXShapePosition(
				background.getPosition(),
				backgroundSize,
				TEXTBOX_SIZE
			),
			TEXTBOX_SIZE,
			"Deconnected",
			font,
			charSize,
			window
		);
		connect->setTextColor(sf::Color::White);
		connect->setShapeColor(DISCONNECTED_COLOR);


		//////// continuer le log displayer pour qu'il affiche les messages dans le textbox
		logDisplayer = new HELPER::LogDisplayer(LOGLINESIZE - 5, LOGLINECOUNT - 2);

		log = new UI::TextBox(
			HELPER::getShapePosition(
				background.getPosition(),
				backgroundSize,
				LOG_SIZE
			),
			LOG_SIZE,
			"",
			font,
			charSize,
			window
		);
		log->setTextColor(sf::Color::White);
		log->setShapeColor(sf::Color::Black);
		log->setOutlineColor(sf::Color::White);
		log->changeLocalTextPosition(sf::Vector2f(7.f, 7.f));

		title.setString("Satellite");
		title.setFont(font);
		title.setCharacterSize(charSize);
		title.setFillColor(sf::Color::White);
		title.setPosition(
			HELPER::getYShapePosition(
				satelliteBox.getPosition(),
				connect->getShape().getSize(),
				title.getGlobalBounds().getSize()
			) + sf::Vector2f(10.f, 0.f)
		);
	}

	SatelliteRender::~SatelliteRender() {
		// delete les pointeurs
		delete satellite;
		delete ping;
		delete send;
		delete connect;
		delete log;
		delete logDisplayer;
	}

	void SatelliteRender::update(float deltaTime) {
		ping->update();
		send->update();

		if (satellite->isConnected()) {
			connect->setText("Connected");
			connect->setShapeColor(CONNECTED_COLOR);
		}
		else {
			connect->setText("Disconnected");
			connect->setShapeColor(DISCONNECTED_COLOR);
		}
		if (a > 50) return;
		a++;
		logDisplayer->addLine("Log aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" + std::to_string(t));
		t++;

		log->setText(logDisplayer->buildString());
	}

	void SatelliteRender::draw(sf::RenderWindow& window) {
		window.draw(satelliteBox);
		ping->draw();
		send->draw();
		connect->draw(window);
		log->draw(window);
		window.draw(title);
	}

	void SatelliteRender::pingCommunicable() {
		satellite->sendMessage("Ping");
	}

	void SatelliteRender::sendCommunicable(std::string msg) {
		satellite->sendMessage(msg);
	}
}