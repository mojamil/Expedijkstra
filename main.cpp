#include "filereader.h"
#include "graph.h"
#include "drawer.h"
#include <iostream>


int main() {
    Reader reader;
    std::vector<Airport> airports = reader.getAirportsFromFile("Data/airports.dat");
    std::vector<Route> routes = reader.getRoutesFromFile("Data/routes.dat");
    // Initialize a weighted and directed graph
    Graph g_(true,true);
    for(auto &i:airports){
        // Store a subset of airports in the graph for testing
        if(i.country=="Greenland"){
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


    Drawer drawer = Drawer("Maps/output.png");
    std::pair<double, double> coord = {69, 420};
    drawer.addAirport(coord);
    std::pair<double, double> JFK = {40.6398,-73.7789};
    std::pair<double, double> nothercoord = {450.5, 69.1234};
    drawer.addAirport(nothercoord);
    //std::pair<double, double> JFK = {40,-73};

    drawer.addAirport(JFK);
    drawer.drawMap();

    return 0;
}