// Name: Astrid Salazar
// Date of completion: November 18th, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <string>

namespace sdds {
	class Utilities {
		size_t m_widthField{ 1 };
		//class variable (static)
		static char m_delimiter;

	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
		std::string& trim(std::string& s);
	};

}

#endif // !SDDS_UTILITIES_H
