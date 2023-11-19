#include "Functions.h"

namespace HELPER {
	sf::Vector2f getShapePosition(const sf::Vector2f& f_centerPos, const sf::Vector2f& f_size, const sf::Vector2f& s_size) {
		return sf::Vector2f(
			getXShapePosition(f_centerPos, f_size, s_size).x,
			getYShapePosition(f_centerPos, f_size, s_size).y
		);
	}

	sf::Vector2f getXShapePosition(const sf::Vector2f& f_centerPos, const sf::Vector2f& f_size, const sf::Vector2f& s_size) {
		return sf::Vector2f(
			f_centerPos.x + f_size.x / 2 - s_size.x / 2,
			f_centerPos.y);
	}

	sf::Vector2f getYShapePosition(const sf::Vector2f& f_centerPos, const sf::Vector2f& f_size, const sf::Vector2f& s_size) {
		return sf::Vector2f(
			f_centerPos.x,
			f_centerPos.y + f_size.y / 2 - s_size.y / 2);
	}

	void centerText(sf::Text& text, const sf::Vector2f& rectSize, const sf::Vector2f& rectPos) {
		// centre le texte dans le rectangle
		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		text.setPosition(
			sf::Vector2f(
				rectPos.x + rectSize.x / 2.0f,
				rectPos.y + rectSize.y / 2.0f
			)
		);
	}
}