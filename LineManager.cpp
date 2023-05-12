// Name: Astrid Salazar
// Date of completion: December 3rd, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "LineManager.h"
#include "Utilities.h"


using namespace std;

namespace sdds {
	//constructor
	LineManager::LineManager(const std::string& filename, const std::vector<Workstation*>& stations) {
        std::ifstream file(filename);
		std::string temp{};
        std::size_t entries{ 0 };
        if (file) {
			//load contents of the file
            while (file) {
                // read each line of the file
                std::getline(file, temp);
                if (file) {
                    m_activeLine.resize(entries + 1);
                   //copy one station at a time
                    std::copy_if(stations.begin(), stations.end(), m_activeLine.begin() + entries, [&](Workstation* ws) -> bool {
                        bool found = false;
                        // check for a second station
                        if (temp.find('|') != std::string::npos && ws->getItemName().compare(temp.substr(0, temp.find('|'))) == 0) {
                            // find the second station
                            auto next = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws2) -> bool {
                                return ws2->getItemName().compare(temp.substr(temp.find('|') + 1)) == 0;
                                });
                            // set next station
                            ws->setNextStation(*next);
                            found = true;
                        }
                        else if (ws->getItemName().compare(temp) == 0) {
                            found = true;
                        }
                        return found;
                        });
                }
				//keep count of entries
                entries++;
            }
			//identify the first station in the assembly line
			for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws1) {
				auto first = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws2) {
					return ws1 == ws2->getNextStation(); });
				if (first == m_activeLine.end())
					//store the address of the first station in the member variable
					m_firstStation = ws1;
			});

			// update amount of customer orders
			m_cntCustomerOrder = g_pending.size();
        }
        else {
			throw string("Failed to open: [ " + filename + " ]");
        }
	}

		

	//reorders the workstations in m_activeLine
	void LineManager::reorderStations() {
		std::vector<Workstation*> ws{};
		Workstation* temp = m_firstStation;
		ws.push_back(temp);
		while (temp->getNextStation()) {
			temp = temp->getNextStation();
			ws.push_back(temp);
		}
		m_activeLine = ws;
	}

	//performs one iteration of operations on all the workstations
	bool LineManager::run(std::ostream& os) {
		//keep track of the current iteration number and insert into os
		static size_t count{};
		os << "Line Manager Iteration: " << ++count << endl;

		if (g_pending.size() > 0) {
			//move the order at the front of the g_pending queue to the m_firstStation
			*m_firstStation += std::move(g_pending.front());
			//remove it from the queue
			g_pending.pop_front();
		}
		
		//for each station on the line, fill
		for (Workstation* ws : m_activeLine) {
			ws->fill(os);
		}
		//for each station on the line, attempt to move an order down the line
		for (Workstation* ws : m_activeLine) {
			ws->attemptToMoveOrder();
		}

		//return true if all orders have been filled or cant be filled, otherwise false
		return m_cntCustomerOrder == g_completed.size() + g_incomplete.size();
	}

	// displays all active stations on the assembly line
	void LineManager::display(std::ostream& os) const {
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
			ws->display(os);
		});
	}

}