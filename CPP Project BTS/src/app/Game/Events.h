#pragma once

#include <functional>
#include <vector>
#include <SFML/Graphics.hpp>

namespace APP {
	class Event {
	public:
		using Function = std::function<void()>;
		using KeyFunction = std::function<void(sf::Keyboard::Key k)>;

		static std::vector<Function> onClick;
		static std::vector<Function> onHover;
		static std::vector<Function> onUnhover;
		static std::vector<KeyFunction> onKey;
		static std::vector<Function> onTextEntered;

		static void processEvents(sf::RenderWindow& window);

		static void addOnClick(Function function);
		static void addOnHover(Function function);
		static void addOnUnhover(Function function);
		static void addOnKey(KeyFunction function);
		static void addOnTextEntered(Function function);

		static void callOnClick();
		static void callOnHover();
		static void callOnUnhover();
		static void callOnKey(sf::Keyboard::Key key);
		static void callOnTextEntered();

	private:
		static Event& getInstance();
	};
}