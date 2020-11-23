#pragma once
#include <iostream>
#include <vector>
#include "airport.h"
#include "route.h"
class Reader {
    public:
        std::vector<Airport> getAirportsFromFile(const std::string& file_name);
        std::vector<Route> getRoutesFromFile(const std::string& file_name);
    private:
        const std::vector<std::vector<std::string>> readCSV(const std::string& file_name) const;

};