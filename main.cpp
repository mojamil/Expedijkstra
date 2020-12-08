#include "filereader.h"
#include "graph.h"
#include "graphbuilder.h"
#include <iostream>
#include "searches.h"

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
    GraphBuilder builder(airports,routes,airports_by_code);
    Graph india=builder.country_subgraph("India");
    Graph all=builder.get_full_graph();
    Search search;
    std::cout<<search.find_route(all,"TKK","JFK")<<std::endl;
    return 0;
}