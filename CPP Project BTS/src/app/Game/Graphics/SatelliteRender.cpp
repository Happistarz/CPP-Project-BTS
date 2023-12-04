#include "SatelliteRender.h"

namespace GRAPHICS {
	SatelliteRender::SatelliteRender(sf::RenderWindow& window, sf::Font& font, sf::Font& term, sf::TcpSocket& connected, GRAPHICS::Simulator& simulator, UI::Modal& modal) {

		// initialisation des objets
		int port = 5000;

		// initialisation de la communication
		logDisplayer = new HELPER::LogDisplayer(CONSTANT::LOGLINESIZE + 27, CONSTANT::LOGLINECOUNT);
		satellite = new METIER::Satellite(sf::IpAddress::getLocalAddress().toString(), port, *logDisplayer, connected);

		// initialisation des formes

		sf::Vector2f backgroundSize(window.getSize().x / 3, window.getSize().y / 2);
		float borderSize = 2.f;

		// background
		background.setSize(backgroundSize);
		background.setPosition(window.getSize().x / 1.5, window.getSize().y / 2);
		background.setFillColor(sf::Color::Cyan);

		// satelliteBox
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


		// initialisation des boutons

		// ping
		ping = new UI::Button(
			HELPER::getXShapePosition(
				background.getPosition(),
				backgroundSize / 2.f,
				CONSTANT::BUTTON_SIZE
			) + sf::Vector2f(0.f, satelliteBox.getGlobalBounds().height / 1.3f),
			CONSTANT::BUTTON_SIZE,
			"Ping",
			font,
			CONSTANT::charSize,
			window,
			[&]() {sendCommunicable("Ping", simulator); }
		);


		// send
		send = new UI::Button(
			HELPER::getXShapePosition(
				sf::Vector2f(background.getPosition().x + backgroundSize.x / 2.f, background.getPosition().y),
				backgroundSize / 2.f,
				CONSTANT::BUTTON_SIZE
			) + sf::Vector2f(0.f, satelliteBox.getGlobalBounds().height / 1.3f),
			CONSTANT::BUTTON_SIZE,
			"Send",
			font,
			CONSTANT::charSize,
			window,
			[&]() {
				modal.openModal();
				modal.setCallback([&](std::string msg) {
					sendCommunicable(msg, simulator);
				});
			}
		);

		// initialisation des textes
		connect = new UI::TextBox(
			HELPER::getXShapePosition(
				background.getPosition(),
				backgroundSize,
				CONSTANT::TEXTBOX_SIZE
			),
			CONSTANT::TEXTBOX_SIZE,
			"Deconnected",
			font,
			CONSTANT::charSize,
			window
		);
		connect->setTextColor(sf::Color::White);
		connect->setShapeColor(CONSTANT::DISCONNECTED_COLOR);


		// log
		log = new UI::TextBox(
			HELPER::getShapePosition(
				background.getPosition(),
				backgroundSize,
				CONSTANT::LOG_SIZE
			),
			CONSTANT::LOG_SIZE,
			"",
			term,
			17U,
			window
		);
		log->setTextColor(sf::Color::White);
		log->setShapeColor(sf::Color::Black);
		log->setOutlineColor(sf::Color::White);
		log->changeLocalTextPosition(sf::Vector2f(7.f, 7.f));


		// title
		title.setString("Satellite | S:" + std::to_string(port));
		title.setFont(font);
		title.setCharacterSize(CONSTANT::charSize);
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

	void SatelliteRender::update(float deltaTime, sf::RenderWindow& window) {

		// update les objets
		ping->update(window);
		send->update(window);


		// update les textes
		if (satellite->isConnected()) {
			connect->setText("Connected");
			connect->setShapeColor(CONSTANT::CONNECTED_COLOR);
			connect->setTextColor(sf::Color::Black);
		}
		else {
			connect->setText("Disconnected");
			connect->setShapeColor(CONSTANT::DISCONNECTED_COLOR);
			connect->setTextColor(sf::Color::White);
		}

		connect->centerText();

		// affiche le log
		log->setText(logDisplayer->buildString());
	}

	void SatelliteRender::draw(sf::RenderWindow& window) {
		// affiche les formes
		window.draw(satelliteBox);
		ping->draw();
		send->draw();
		connect->draw(window);
		log->draw(window);
		window.draw(title);
	}

	void SatelliteRender::sendCommunicable(std::string msg, GRAPHICS::Simulator& simulator) {
		// envoie un message
		satellite->sendMessage(msg);
		simulator.setDrawLineConnection(true, 2);
	}
}