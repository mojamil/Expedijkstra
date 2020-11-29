#pragma once
#include <iostream>
#include <vector>
#include "airport.h"
#include "route.h"
#include "graph.h"

class GraphBuilder{
    public:
        GraphBuilder(std::vector<Airport>,std::vector<Route>);
        Graph country_subgraph(std::string);
    private:
        std::map<std::string,std::vector<Airport>> airports_by_country;
        std::vector<Route> routes_;
};