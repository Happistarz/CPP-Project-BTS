#pragma once

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <SFML/Graphics.hpp>

namespace HELPER {
	/// <summary>
	/// Retourne la position d'une forme en fonction de sa taille et de sa position centrale
	/// </summary>
	/// <param name="f_centerPos"></param>
	/// <param name="s_size"></param>
	/// <returns></returns>
	sf::Vector2f getShapePosition(const sf::Vector2f& f_centerPos, const sf::Vector2f& f_size, const sf::Vector2f& s_size);
	/// <summary>
	/// Retourne la position centr�e sur l'axe X d'une forme en fonction de sa taille et de sa position centrale
	/// </summary>
	/// <param name="f_centerPos"></param>
	/// <param name="f_size"></param>
	/// <param name="s_size"></param>
	/// <returns></returns>
	sf::Vector2f getXShapePosition(const sf::Vector2f& f_centerPos, const sf::Vector2f& f_size, const sf::Vector2f& s_size);
	/// <summary>
	/// Retourne la position centr�e sur l'axe Y d'une forme en fonction de sa taille et de sa position centrale
	/// </summary>
	/// <param name="f_centerPos"></param>
	/// <param name="f_size"></param>
	/// <param name="s_size"></param>
	/// <returns></returns>
	sf::Vector2f getYShapePosition(const sf::Vector2f& f_centerPos, const sf::Vector2f& f_size, const sf::Vector2f& s_size);

	void centerText(sf::Text& text, const sf::Vector2f& rectSize, const sf::Vector2f& rectPos);
	/// <summary>
	/// Retourne un nombre aleatoire entre deux nombres
	/// </summary>
	//int (*getRandomInt)(int, int) = [](int min, int max) { return rand() % (max - min + 1) + min; };
}


#endif // !FUNCTIONS_H
