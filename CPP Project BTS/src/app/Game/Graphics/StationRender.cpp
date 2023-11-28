#include "StationRender.h"


namespace GRAPHICS {
	StationRender::StationRender(sf::RenderWindow& window, sf::Font& font, sf::Font& term, sf::TcpSocket& connected) {

		// initialisation des objets
		int port = 6000;

		// initialisation de la communication
		logDisplayer = new HELPER::LogDisplayer(CONSTANT::LOGLINESIZE + 27, CONSTANT::LOGLINECOUNT);
		station = new METIER::Station(sf::IpAddress::getLocalAddress().toString(), port, *logDisplayer, connected);

		// initialisation des formes

		sf::Vector2f backgroundSize(window.getSize().x / 3, window.getSize().y / 2);
		float borderSize = 2.f;


		// background
		background.setSize(backgroundSize);
		background.setPosition(window.getSize().x / 1.5, 0.f);
		background.setFillColor(sf::Color::Cyan);

		// stationBox
		stationBox.setSize(backgroundSize - sf::Vector2f(20.f, 10.f));
		stationBox.setPosition(
			HELPER::getXShapePosition(
				background.getPosition(),
				backgroundSize,
				stationBox.getSize() + sf::Vector2f(borderSize, borderSize)
			) + sf::Vector2f(0.f, 10.f)
		);

		stationBox.setFillColor(sf::Color::Black);
		stationBox.setOutlineThickness(borderSize);
		stationBox.setOutlineColor(sf::Color::White);


		// initialisation des boutons

		// ping
		ping = new UI::Button(
			HELPER::getXShapePosition(
				background.getPosition(),
				backgroundSize / 2.f,
				CONSTANT::BUTTON_SIZE
			) + sf::Vector2f(0.f, stationBox.getGlobalBounds().height / 1.3f),
			CONSTANT::BUTTON_SIZE,
			"Ping",
			font,
			CONSTANT::charSize,
			window,
			[this]() {pingCommunicable(); }
		);

		// send
		send = new UI::Button(
			HELPER::getXShapePosition(
				sf::Vector2f(background.getPosition().x + backgroundSize.x / 2.f, background.getPosition().y),
				backgroundSize / 2.f,
				CONSTANT::BUTTON_SIZE
			) + sf::Vector2f(0.f, stationBox.getGlobalBounds().height / 1.3f),
			CONSTANT::BUTTON_SIZE,
			"Send",
			font,
			CONSTANT::charSize,
			window,
			[this]() {sendCommunicable("MESSAGE DE LA FRANCE OUI"); }
		);

		// initialisation des textes

		// connect
		connect = new UI::TextBox(
			HELPER::getXShapePosition(
				background.getPosition(),
				backgroundSize,
				CONSTANT::TEXTBOX_SIZE
			) + sf::Vector2f(0.f, 10.f),
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
		title.setString("Station | S:" + std::to_string(port));
		title.setFont(font);
		title.setCharacterSize(CONSTANT::charSize);
		title.setFillColor(sf::Color::White);
		title.setPosition(
			HELPER::getYShapePosition(
				stationBox.getPosition(),
				connect->getShape().getSize(),
				title.getGlobalBounds().getSize()
			) + sf::Vector2f(10.f, 0.f)
		);
	}

	StationRender::~StationRender() {
		// delete les pointeurs
		delete station;
		delete ping;
		delete send;
		delete connect;
		delete log;
		delete logDisplayer;
	}

	void StationRender::update(float deltaTime) {
		// update les boutons
		ping->update();
		send->update();


		// update les textes
		if (station->isConnected()) {
			connect->setText("Connected");
			connect->setShapeColor(CONSTANT::CONNECTED_COLOR);
			connect->setTextColor(sf::Color::Black);
		}
		else {
			connect->setText("Disconnected");
			connect->setShapeColor(CONSTANT::DISCONNECTED_COLOR);
			connect->setTextColor(sf::Color::Black);
		}

		connect->centerText();

		// affiche le log
		log->setText(logDisplayer->buildString());
	}

	void StationRender::draw(sf::RenderWindow& window) {
		// affiche les objets
		window.draw(stationBox);
		ping->draw();
		send->draw();
		connect->draw(window);
		log->draw(window);
		window.draw(title);
	}

	void StationRender::pingCommunicable() {
		// ping le communicable
		if (station->sendMessage("Ping")) {
			std::cout << "ping success" << std::endl;
		}
		else {
			std::cout << "ping failed" << std::endl;
		}
	}

	void StationRender::sendCommunicable(std::string msg) {
		// envoie un message au communicable
		station->sendMessage(msg);
	}

}