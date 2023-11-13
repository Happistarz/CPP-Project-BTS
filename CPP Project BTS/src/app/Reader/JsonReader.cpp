#include "JsonReader.h"

namespace READER {
	JsonReader::JsonReader(std::string path) : path(path) {
		load();

		document.SetObject();

	}

	JsonReader::~JsonReader() {
		save();
	}

	rapidjson::Document& JsonReader::getDocument() {
		return document;
	}

	void JsonReader::addValue(std::string key, std::string value) {
		// ajoute la valeur au document
		document.AddMember(
			rapidjson::Value(key.c_str(), document.GetAllocator()),
			rapidjson::Value(value.c_str(), document.GetAllocator()),
			document.GetAllocator()
		);
		// enregistre le document
		save();
	}

	std::string JsonReader::getValue(std::string key) {
		// recupere la valeur du document
		return document[key.c_str()].GetString();
	}

	void JsonReader::load() {

		// charge le fichier
		std::ifstream InputFileStream(path);
		rapidjson::IStreamWrapper InputStreamWrapper(InputFileStream);

		// parse le fichier
		document.ParseStream(InputStreamWrapper);
	}

	void JsonReader::save() {
		// sauvegarde le fichier
		std::ofstream OutputFileStream(path);
		rapidjson::OStreamWrapper OutputStreamWrapper(OutputFileStream);
		rapidjson::Writer<rapidjson::OStreamWrapper> writer(OutputStreamWrapper);

		// ecrit le document dans le fichier
		document.Accept(writer);
	}

}