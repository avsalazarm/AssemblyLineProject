// Name: Astrid Salazar
// Date of completion: November 18th, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>

namespace sdds {
	class Station {
		size_t m_id{};
		std::string m_itemName{};
		std::string m_description{};
		size_t m_serialNum{};
		size_t m_itemQty{};
		//class variables
		static size_t m_widthField;
		static size_t id_generator;

	public:
		Station(const std::string& record);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}

#endif // !SDDS_STATION_H
