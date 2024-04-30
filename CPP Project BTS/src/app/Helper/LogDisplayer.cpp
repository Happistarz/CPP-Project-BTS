#include "LogDisplayer.h"


namespace HELPER {
	LogDisplayer::LogDisplayer(unsigned int maxChar, unsigned int maxLine) 
		: maxChar(maxChar), maxLine(maxLine), start(std::chrono::high_resolution_clock::now())
	{
		log.clear();
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

	std::string LogDisplayer::getFormattedTime() {
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = end - start;

		// mm:ss:ms
		int minutes = (int)elapsed.count() / 60;
		int seconds = (int)elapsed.count() % 60;
		int milliseconds = (int)(elapsed.count() * 1000) % 1000;

		std::string result = "";
		if (minutes < 10) {
			result += "0";
		}

		result += std::to_string(minutes) + ":";
		if (seconds < 10) {
			result += "0";
		}

		result += std::to_string(seconds) + ":";
		if (milliseconds < 10) {
			result += "00";
		}
		else if (milliseconds < 100) {
			result += "0";
		}

		result += std::to_string(milliseconds);

		return result;
	}

	void LogDisplayer::addLine(std::string line) {

		line = "["+getFormattedTime() + "] " + line;

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