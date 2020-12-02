#pragma once
#include <iostream>
#include <vector>
#include "airport.h"
#include "route.h"
#include "graph.h"
#include <cmath>

class GraphBuilder{
    public:
        GraphBuilder(std::vector<Airport>,std::vector<Route>,std::map<std::string,Airport>);
        Graph country_subgraph(std::string);
        Graph countries_subgraph(std::vector<std::string>);
    private:
        double distance(Airport,Airport);
        std::map<std::string,Airport> airports_by_code;
        std::map<std::string,std::vector<Airport>> airports_by_country;
        std::vector<Route> routes_;
};