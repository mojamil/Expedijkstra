#include "filereader.h"
#include "graph.h"
#include <iostream>
int main() {
    Reader reader;
    std::vector<Airport> airports = reader.getAirportsFromFile("Data/airports.dat");
    std::vector<Route> routes = reader.getRoutesFromFile("Data/routes.dat");
    // Initialize a weighted and directed graph
    Graph g_(true,true);
    for(auto &i:airports){
        // Store a subset of airports in the graph for testing
        if(i.country=="\"Greenland\""){
            if(i.code!="\\N"){
                g_.insertVertex(i.code.substr(1,3));
            }
        }
    }
    for(auto &i:routes){
        // Store only the routes related to the airports in the graph
        if(g_.vertexExists(i.source_code)&&g_.vertexExists(i.destination_code)){
            g_.insertEdge(i.source_code,i.destination_code);
        }
    }
    g_.print();
    return 0;
}