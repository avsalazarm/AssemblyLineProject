// Name: Astrid Salazar
// Date of completion: November 27th, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <string>
#include <iostream>
#include "Station.h"

namespace sdds {
	class CustomerOrder {
		struct Item
		{
			std::string m_itemName;
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };

			Item(const std::string& src) : m_itemName(src) {};
		};

		std::string m_name{};  // name of the customer
		std::string m_product{}; // name of the product
		std::size_t m_cntItem{};  // number of items in the customer's order
		Item** m_lstItem{};  // dynamic array of Items
		//class variable 
		static size_t m_widthField; //max width of a field

	public:
		CustomerOrder();
		CustomerOrder(const std::string);
		//copy constructor
		CustomerOrder(const CustomerOrder&);
		//copy assignment
		//deleted since it should not allow copy operations
		CustomerOrder& operator=(const CustomerOrder&) = delete;
		//move constructor
		CustomerOrder(CustomerOrder&&) noexcept;
		//move assingment operaror
		CustomerOrder& operator=(CustomerOrder&&) noexcept;
		//destructor
		~CustomerOrder();
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};

}

#endif // !SDDS_CUSTOMERORDER_H