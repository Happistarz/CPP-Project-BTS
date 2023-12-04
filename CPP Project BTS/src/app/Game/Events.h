#pragma once

#include <functional>
#include <vector>
#include <SFML/Graphics.hpp>

namespace APP {
	class Event {
	public:
		using Function = std::function<void()>;
		using KeyFunction = std::function<void(sf::Keyboard::Key)>;
		using TextFunction = std::function<void(sf::Uint32)>;

		static std::vector<Function> onClick;
		static std::vector<Function> onHover;
		static std::vector<Function> onUnhover;
		static std::vector<KeyFunction> onKey;
		static std::vector<TextFunction> onTextEntered;

		static void processEvents(sf::RenderWindow& window);

		static void addOnClick(Function function);
		static void addOnHover(Function function);
		static void addOnUnhover(Function function);
		static void addOnKey(KeyFunction function);
		static void addOnTextEntered(TextFunction function);

		static void callOnClick();
		static void callOnHover();
		static void callOnUnhover();
		static void callOnKey(sf::Keyboard::Key key);
		static void callOnTextEntered(sf::Uint32 unicode);

	private:
		static Event& getInstance();
	};
}