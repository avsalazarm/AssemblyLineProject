// Name: Astrid Salazar
// Date of completion: November 18th, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include "Utilities.h"

using namespace std;

namespace sdds {
	//initialize class variables to default values
	char Utilities::m_delimiter{ ',' };

	void Utilities::setFieldWidth(size_t newWidth) { m_widthField = newWidth; }

	size_t Utilities::getFieldWidth() const { return m_widthField; }

	void Utilities::setDelimiter(char newDelimiter) { m_delimiter = newDelimiter; }

	char Utilities::getDelimiter() { return m_delimiter; }

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		std::string token{};
		//uses delimiter to extract next token from str starting at next_pos
		size_t start = str.find(m_delimiter, next_pos);
		//reports an exception if the delimiter is found at next_pos
		if (str[next_pos] == m_delimiter) {
			more = false;
			throw("Invalid position");
		}
		//if successful
		if (start != string::npos) {
			token = str.substr(next_pos, start - next_pos);
			token = trim(token);
			more = true;
			//update next_post with the position of the next token
			next_pos = start + 1;
		}
		else {
			token = str.substr(next_pos);
			token = trim(token);
			more = false;
		}
		//update the current object's m_widthField
		if (m_widthField < token.length()) {
			m_widthField = token.length();
		}
		//return a copy of the extracted token found
		return token;
	}

	//trims all leading and trailing white spaces
	//function from https://www.toptip.ca/2010/03/trim-leading-or-trailing-white-spaces.html
	//modififed to make it return the trimmed string
	std::string& Utilities::trim(std::string& s) {
		size_t p = s.find_first_not_of(" \t");
		s.erase(0, p);
		p = s.find_last_not_of(" \t");
		if (string::npos != p) { s.erase(p + 1); }

		return s;
	}
}