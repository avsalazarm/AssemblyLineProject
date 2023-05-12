// Name: Astrid Salazar
// Date of completion: November 27th, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "Station.h"
#include "CustomerOrder.h"
#include "Utilities.h"


using namespace std;

namespace sdds {
	//initialize class variable to default values
	std::size_t CustomerOrder::m_widthField{ 1 };

	//default constructor
	//values already initialized in header file
	CustomerOrder::CustomerOrder() {}

	//extracts tokes from the string and populates the current instance
	CustomerOrder::CustomerOrder(const std::string data) {
		Utilities util{};
		string temp{};
		size_t next_pos{};
		bool more{ false };
		//extract customerName
		m_name = util.extractToken(data, next_pos, more);
		//extract product
		m_product = util.extractToken(data, next_pos, more);
		//extract items
		for (size_t i = next_pos; i < data.size(); i++) {
			if (data[i] == util.getDelimiter()) {
				m_cntItem++;
			}
		}
		m_cntItem++; // +1 bc the last item doesn't end in a delimiter
		m_lstItem = new Item * [m_cntItem + 1];
		for (size_t i = 0; i < m_cntItem; i++)
		{
			m_lstItem[i] = new Item(util.extractToken(data, next_pos, more));
		}

		//update CustomerOrder::m_widthField
		m_widthField = util.getFieldWidth() > m_widthField ? util.getFieldWidth() : m_widthField;
	}

	//a CustomerOrder obj shuld not allow copy operations
	CustomerOrder::CustomerOrder(const CustomerOrder&) {
		//throws exception if called 
		throw("Error: a Customer Order can't be copied!");
	}

	//move constructor
	CustomerOrder::CustomerOrder(CustomerOrder&& co) noexcept {
		*this = std::move(co);
	}

	//move assignment operator
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& co) noexcept {
		if (this != &co) {
			//dellocate
			for (auto i = 0u; i < m_cntItem; ++i) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			//move values
			m_name = co.m_name;
			m_product = co.m_product;
			m_lstItem = co.m_lstItem;
			m_cntItem = co.m_cntItem;
			//set old values to safe empty state
			co.m_name = "";
			co.m_product = "";
			co.m_lstItem = nullptr;
			co.m_cntItem = 0;
		}
		return *this;
	}

	//destructor
	CustomerOrder::~CustomerOrder() {
		for (std::size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}

	//returns true if all the items in the order have been filled
	bool CustomerOrder::isOrderFilled() const {
		bool filled{ true };
		for (size_t i = 0; i < m_cntItem; i++) {
			if (!m_lstItem[i]->m_isFilled) {
				filled = false;
			}
		}
		return filled;
	}

	//returns true if all items specified by itemName have been filled
	//returns true if the item doesnt exist in the order
	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool filled = true;
		for (std::size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				filled = m_lstItem[i]->m_isFilled;
			}
		}
		return filled;
	}

	//fills one item in the current order that Station specifies
	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		bool flag = true;
		for (std::size_t i = 0; i < m_cntItem && flag; i++) {
			//if the order contains the item handled && is not filled
			if (station.getItemName() == m_lstItem[i]->m_itemName && !m_lstItem[i]->m_isFilled) {
				if (station.getQuantity() > 0) {
					flag = false;
					//substract one from inventory
					station.updateQuantity();
					//update serial number and isFilled
					m_lstItem[i]->m_isFilled = true;
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					os << "    Filled " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << std::endl;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << std::endl;

				}
			}
		}
	}

	//display the state of the current object
	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << "[";
			os.width(6);
			os.fill('0');
			os.setf(ios::right);
			os << m_lstItem[i]->m_serialNumber;
			os << "] ";
			os.fill(' ');
			os.width(m_widthField + 2);
			os.unsetf(ios::right);
			os.setf(ios::left);
			os << m_lstItem[i]->m_itemName;
			os << " - ";
			m_lstItem[i]->m_isFilled ? os << "FILLED" << endl : os << "TO BE FILLED" << endl;
		}
	}

}