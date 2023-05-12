// Name: Astrid Salazar
// Date of completion: December 3rd, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "Workstation.h"
#include "Utilities.h"


using namespace std;

namespace sdds {
	std::deque<CustomerOrder> g_pending{};
	std::deque<CustomerOrder> g_completed{};
	std::deque<CustomerOrder> g_incomplete{};

	// one argument constructor
	Workstation::Workstation(const std::string& record): Station(record) {}

	// fills the order at the front of the queue if there are CustomerOrders in the queue
	void Workstation::fill(std::ostream& os) {
		if (m_orders.size() > 0) { //if CustomerOrders is not empty
			m_orders.front().fillItem(*this, os);
		}
	}

	//moves the order at the front of the queue to the next station
	bool Workstation::attemptToMoveOrder() {
		bool moved{ false };
		//if the order requires no more service or not enough inventory
				//move to next station
		if (m_orders.size() > 0) {
			if (!getQuantity() || m_orders.front().isItemFilled(getItemName())) {
				moved = true;
				//if there's a next station
				if (m_pNextStation != nullptr) {
					*m_pNextStation += std::move(m_orders.front());
				}//else the order is moved into g_completed or g_incomplete
				else if (m_orders.front().isOrderFilled()) {
					g_completed.push_back(std::move(m_orders.front()));
				}
				else {
					g_incomplete.push_back(std::move(m_orders.front()));
				}
				//remove from m_orders array after adding to list
				m_orders.pop_front();
			}
		}
		
		//return true if an order has been moved, false otherwise
		return moved;
	}


	//stores the address of the referenced WorkStation into the m_pNextStation pointer
	void Workstation::setNextStation(Workstation* station) { m_pNextStation = station; }

	//returns the address of the next WorkStation
	Workstation* Workstation::getNextStation() const { return m_pNextStation; }

	//inserts the name of the Item 
	void Workstation::display(std::ostream& os) const {
		os << getItemName() << " --> ";
		//display next station or end of line if it's the last station
		m_pNextStation ? os << m_pNextStation->getItemName() : os << "End of Line";
		os << endl;
	}

	//moves the CustomerOrder referenced in the parameter to the back of the queue
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}