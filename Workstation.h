// Name: Astrid Salazar
// Date of completion: December 3rd, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <string>
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

namespace sdds {
	//each queue is accessible outside this module's translation unit = extern
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation: public Station {
		//double ended queue of orders
		std::deque<CustomerOrder> m_orders;
		//pointer to the next Workstation on the assembly line
		Workstation* m_pNextStation{};

	public:
		// one argument constructor
		Workstation(const std::string& record);
		//object cannot be copied or moved 
		Workstation(const Workstation& src) = delete;
		Workstation& operator=(const Workstation& src) = delete;
		Workstation(Workstation&& src) = delete;
		Workstation& operator=(Workstation&& src) = delete;
		// fills the order at the front of the queue if there are CustomerOrders 
		void fill(std::ostream& os);
		//moves the order at the front of the queue to the next station
		bool attemptToMoveOrder();
		//stores the address of the referenced WorkStation into the m_pNextStation pointer
		void setNextStation(Workstation* station);
		//returns the address of the next WorkStation
		Workstation* getNextStation() const;
		//inserts the name of the Item 
		void display(std::ostream& os) const;
		//moves the CustomerOrder referenced in the parameter
		Workstation& operator+=(CustomerOrder&& newOrder);
	};
}

#endif // !SDDS_WORKSTATION_H
