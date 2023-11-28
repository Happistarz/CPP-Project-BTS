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
	/// Retourne la position centrée sur l'axe X d'une forme en fonction de sa taille et de sa position centrale
	/// </summary>
	/// <param name="f_centerPos"></param>
	/// <param name="f_size"></param>
	/// <param name="s_size"></param>
	/// <returns></returns>
	sf::Vector2f getXShapePosition(const sf::Vector2f& f_centerPos, const sf::Vector2f& f_size, const sf::Vector2f& s_size);

	/// <summary>
	/// Retourne la position centrée sur l'axe Y d'une forme en fonction de sa taille et de sa position centrale
	/// </summary>
	/// <param name="f_centerPos"></param>
	/// <param name="f_size"></param>
	/// <param name="s_size"></param>
	/// <returns></returns>
	sf::Vector2f getYShapePosition(const sf::Vector2f& f_centerPos, const sf::Vector2f& f_size, const sf::Vector2f& s_size);

	/// <summary>
	/// Centre un texte dans un rectangle
	/// </summary>
	/// <param name="text"></param>
	/// <param name="rectSize"></param>
	/// <param name="rectPos"></param>
	void centerText(sf::Text& text, const sf::Vector2f& rectSize, const sf::Vector2f& rectPos);

	/// <summary>
	/// Retourne le centre d'une forme
	/// </summary>
	/// <param name="size"></param>
	/// <returns></returns>
	sf::Vector2f getCenter(const sf::Vector2f& size);
}


#endif // !FUNCTIONS_H
