#include "LogDisplayer.h"


namespace HELPER {
	LogDisplayer::LogDisplayer(unsigned int maxChar, unsigned int maxLine) : maxChar(maxChar), maxLine(maxLine) {
	}

	LogDisplayer::~LogDisplayer() {
		log.clear();
	}

	std::string LogDisplayer::buildString() {
		std::string result = "";
		for (std::string line : log) {
			result += line + "\n";
		}
		return result;
	}

	void LogDisplayer::addLine(std::string line) {
		// si la ligne est trop longue
		/*if (line.size() > maxChar) {
			// on la coupe en plusieurs lignes
			std::string temp = "";
			for (unsigned int i = 0; i < line.size(); i++) {
				temp += line[i];
				if (i % maxChar == 0 && i != 0) {
					log.push_back(temp);
					temp = "";
				}
			}
			log.push_back(temp);
		}
		else {
			log.push_back(line);
		}

		// si il y a trop de lignes
		if (log.size() > maxLine) {
			// on supprime la premiere
			log.pop_front();
		}*/

		// if the line is too long
		// cut it in several lines
		// and add them to the log
		// if there is too many lines
		// remove the first one or for each cutted line pop them firsts
		unsigned int count = 1;

		if (line.size() > maxChar) {
			std::string temp = "";
			for (unsigned int i = 0; i < line.size(); i++) {
				temp += line[i];
				if (i % maxChar == 0 && i != 0) {
					log.push_back(temp);
					temp = "";
					count++;
				}
			}
			log.push_back(temp);
		}
		else {
			log.push_back(line);
		}

		if (log.size() > maxLine) {
			for (unsigned int i = 0; i < count; i++) {
				log.pop_front();
			}
		}
	}
}