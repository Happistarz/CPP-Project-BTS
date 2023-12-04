#include "Events.h"

namespace APP {
	std::vector<Event::Function> Event::onClick;
	std::vector<Event::Function> Event::onHover;
	std::vector<Event::Function> Event::onUnhover;
	std::vector<Event::KeyFunction> Event::onKey;
	std::vector<Event::TextFunction> Event::onTextEntered;

	void Event::processEvents(sf::RenderWindow& window) {
		Event& instance = getInstance();
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					instance.callOnClick();
				}
				break;
			case sf::Event::MouseMoved:
				instance.callOnHover();
				break;
			case sf::Event::MouseLeft:
				instance.callOnUnhover();
				break;
			case sf::Event::KeyPressed:
				instance.callOnKey(event.key.code);
				break;
			case sf::Event::TextEntered:
				if (event.text.unicode < 128)
					instance.callOnTextEntered(event.text.unicode);
				break;
			default:
				break;
			}
		}
	}

	void Event::addOnClick(Function function) {
		getInstance().onClick.push_back(function);
	}

	void Event::addOnHover(Function function) {
		getInstance().onHover.push_back(function);
	}

	void Event::addOnUnhover(Function function) {
		getInstance().onUnhover.push_back(function);
	}

	void Event::addOnKey(KeyFunction function) {
		getInstance().onKey.push_back(function);
	}

	void Event::addOnTextEntered(TextFunction function) {
		getInstance().onTextEntered.push_back(function);
	}

	void Event::callOnClick() {
		for (auto& function : getInstance().onClick) {
			function();
		}
	}

	void Event::callOnHover() {
		for (auto& function : getInstance().onHover) {
			function();
		}
	}

	void Event::callOnUnhover() {
		for (auto& function : getInstance().onUnhover) {
			function();
		}
	}

	void Event::callOnKey(sf::Keyboard::Key key) {
		for (auto& function : getInstance().onKey) {
			function(key);
		}
	}

	void Event::callOnTextEntered(sf::Uint32 unicode) {
		for (auto& function : getInstance().onTextEntered) {
			function(unicode);
		}
	}

	Event& Event::getInstance() {
		static Event instance; // Une seule instance est créée
		return instance;
	}
}