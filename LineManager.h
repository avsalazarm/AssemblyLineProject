// Name: Astrid Salazar
// Date of completion: December 3rd, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include <string>
#include <vector>
#include "Workstation.h"

namespace sdds {
	class LineManager {
		//collection of workstations for the current assembly line
		std::vector<Workstation*> m_activeLine;
		//total number of CustomerOrder objects
		size_t m_cntCustomerOrder{};
		//points to the first active station on the current line
		Workstation* m_firstStation{};

	public:
		//constructor
		LineManager(const std::string& filename, const std::vector<Workstation*>& stations);
		//reorders the workstations in m_activeLine
		void reorderStations();
		//performs one iteration of operations on all the workstations
		bool run(std::ostream& os);
		// displays all active stations on the assemblt line
		void display(std::ostream& os) const;
	};
}

#endif // !SDDS_LINEMANAGER_H
