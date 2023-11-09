#pragma once

#ifndef JSONREADER_H
#define JSONREADER_H

// include rapidjson
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include <fstream>

namespace READER {
	/// <summary>
	/// Classe JsonReader qui permet de lire et d'ecrire dans un fichier json
	/// </summary>
	class JsonReader {
	private:
		rapidjson::Document document;
		std::string path;
	public:
		/// <summary>
		/// Initialise le JsonReader
		/// </summary>
		/// <param name="path"></param>
		JsonReader(std::string path);
		~JsonReader();

		/// <summary>
		/// Retourne le document
		/// </summary>
		/// <returns></returns>
		rapidjson::Document& getDocument();

		/// <summary>
		/// Ajoute une valeur au document json
		/// </summary>
		/// <param name="key"></param>
		/// <param name="value"></param>
		void addValue(std::string key, std::string value);

		/// <summary>
		/// Charge le fichier json dans le document
		/// </summary>
		void load();

		/// <summary>
		/// Ecrit le document dans le fichier json
		/// </summary>
		void save();
	};
}



#endif // !JSONREADER_H