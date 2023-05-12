// Name: Astrid Salazar
// Date of completion: November 18th, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

using namespace std;

namespace sdds {

	//initialize class variables to default values
	size_t Station::id_generator{ 0 };
	size_t Station::m_widthField{ 1 };

	Station::Station(const std::string& record) {
		//utilities object defined locally
		Utilities util;
		//generate new id
		m_id = ++id_generator;
		size_t next_pos{};
		bool more{ false };
		//extract name, starting serial number and quantity
		m_itemName = util.extractToken(record, next_pos, more);
		m_serialNum = stoi(util.extractToken(record, next_pos, more));
		m_itemQty = stoi(util.extractToken(record, next_pos, more));
		//update Station::m_widthField before extracting description
		m_widthField > util.getFieldWidth() ?
			m_widthField = m_widthField : m_widthField = util.getFieldWidth();
		m_description = util.extractToken(record, next_pos, more);
	}

	const std::string& Station::getItemName() const { return m_itemName; }

	size_t Station::getNextSerialNumber() { return m_serialNum++; }

	size_t Station::getQuantity() const { return m_itemQty; }

	void Station::updateQuantity() {
		//subtracts 1 from the available quantity
		//should not drop below 0
		m_itemQty == 0 ? m_itemQty = 0 : --m_itemQty;
	}

	void Station::display(std::ostream& os, bool full) const {
		os << setw(3);
		os << setfill('0');
		os << right << m_id << " | ";
		os << setw(m_widthField + 1) << left << setfill(' ') << m_itemName << " | ";
		os << setw(6) << setfill('0');
		os << right << m_serialNum << " | ";
		if (full) {
			os << setw(4) << setfill(' ') << m_itemQty << " | " << m_description;
		}
		os << endl;
	}
}