#include "filereader.h"
#include "graph.h"
#include <iostream>
int main() {
    Reader reader;
    std::vector<Airport> airports = reader.getAirportsFromFile("Data/airports.dat");
    std::vector<Route> routes = reader.getRoutesFromFile("Data/routes.dat");
    std::map<std::string,Airport> airports_by_code;
    // Initialize a weighted and directed graph
    Graph g_(true,true);
    for(auto &i:airports){
        // Store a subset of airports in the graph for testing
        airports_by_code[i.code]=i;
        if(i.country=="Greenland"){
            if(i.code!="\\N"){
                g_.insertVertex(i.code.substr(1,3));
            }
        }
    }
    int count=0;
    for(auto &i:routes){
        // Store only the routes related to the airports in the graph
        if(i.num_stops>0){
            count+=1;
        }
        if(g_.vertexExists(i.source_code)&&g_.vertexExists(i.destination_code)){
            g_.insertEdge(i.source_code,i.destination_code);
        }
    }
    std::cout<<count<<std::endl;
    g_.print();
    return 0;
}