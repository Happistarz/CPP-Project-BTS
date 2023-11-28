#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <deque>
#include "Functions.h"

namespace HELPER {
	/// <summary>
	/// Class pour afficher les logs et les garder en memoire dans une deque
	/// </summary>
	class LogDisplayer {
	private:
		std::deque<std::string> log;

		// les parametres
		unsigned int maxChar;
		unsigned int maxLine;
	public:
		/// <summary>
		/// Constructeur de la classe
		/// </summary>
		/// <param name="maxChar"></param>
		/// <param name="maxLine"></param>
		LogDisplayer(unsigned int maxChar, unsigned int maxLine);

		/// <summary>
		/// Destructeur de la classe
		/// </summary>
		~LogDisplayer();

		/// <summary>
		/// Retourne une string avec toutes les lignes de log
		/// </summary>
		/// <returns></returns>
		std::string buildString();

		/// <summary>
		/// Ajoute une ligne de log et gere les parametres
		/// </summary>
		/// <param name="line"></param>
		void addLine(std::string line);
	};
}