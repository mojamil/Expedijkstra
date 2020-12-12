#pragma once
#include <iostream>
#include <vector>
#include "airport.h"
#include "route.h"
class Reader {
    public:
    /**
     * Reads airport from file, and creates a vector of Airport objects. See Airport.h for more 
     * explanation on what airports are.
     * @param file_name - name of file
     * @return vector of airports from file
     */
        std::vector<Airport> getAirportsFromFile(const std::string& file_name);
    /**
     * Reads the route from the file and creates a vector of them. Read route.h for more explanation
     * on what routes are. 
     * @param file_name - name of file
     * @return vector of routes file
     */
        std::vector<Route> getRoutesFromFile(const std::string& file_name);
    private:
        const std::vector<std::vector<std::string>> readCSV(const std::string& file_name) const;

};