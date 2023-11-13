#include "Functions.h"

namespace HELPER {
	sf::Vector2f getShapePosition(const sf::Vector2f& f_centerPos, const sf::Vector2f& f_size, const sf::Vector2f& s_size) {
		return sf::Vector2f(
			getXShapePosition(f_centerPos, f_size, s_size).x,
			getYShapePosition(f_centerPos, f_size, s_size).y);
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
}