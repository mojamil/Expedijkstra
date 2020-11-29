#include "filereader.h"
#include "graph.h"
#include "graphbuilder.h"
#include <iostream>
int main() {
    Reader reader;
    std::vector<Airport> airports = reader.getAirportsFromFile("Data/airports.dat");
    std::vector<Route> routes = reader.getRoutesFromFile("Data/routes.dat");
    std::map<std::string,Airport> airports_by_code;
    // Initialize a weighted and directed graph
    for(auto &i:airports){
        // Store a subset of airports in the graph for testing
        airports_by_code[i.code]=i;
    }
    GraphBuilder builder(airports,routes);
    builder.country_subgraph("Greenland").print();
    return 0;
}