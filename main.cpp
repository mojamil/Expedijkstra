#include <iostream>
#include <map>
#include "filereader.h"
#include "graph.h"
#include "drawer.h"
#include "graphbuilder.h"
#include "searches.h"

/**
 * input options:
 * no flags = graph bfs, djikstras, and vizualize
 * -d = djikstras 
 * -b = bfs 
 * -v = vizualize 
 * note they have to be seperated i.e -d -v -b and not -bdv
*/

void vizualize(Graph& g, GraphBuilder& builder, std::vector<Vertex> route, cs225::HSLAPixel Color = {.5, .5, .5}) {
        Drawer drawer = Drawer("Maps/output.png");

        drawer.addAirports(g, builder, route);
        auto dA = route.size();
        for (auto dB : route) {
            std::cout << dB << std::endl;
        }
        drawer.drawMap(Color);
}

void performBFS(Graph& g, Vertex begin, Vertex end, bool toVizualize = false) {

}

void performDjikstras(Graph& g, GraphBuilder& builder, Vertex begin, Vertex end, bool toVizualize = false) {
    Search search;
    string route = search.find_route(g, begin, end);
    if (route != "") {
        std::cout << "Shortest path is: " << route << std::endl;
    }

    if (toVizualize && route != "") {
        std::vector<Vertex> vector_route = search.find_route_in_vector(g, begin, end);
        vizualize(g, builder, vector_route);
        std::cout << "Vizualized to output.png" << std::endl;
    }
    

}

//new version
int main(int argc, char *argv[]) {
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
    if (argc <= 1) {
        while (true) {
            

        
            std::cout<<"Enter Code of Airport Your Flying From (type Q to quit): ";
            Vertex begin="";
            std::cin>>begin;
            std::cout<<begin<<std::endl;
            if(begin=="Q" || begin=="q"){
                break;
            }
            std::cout<<"Enter Code of Airport Your Flying Too (type Q to quit): ";
            Vertex end="";
            std::cin>>end;
            std::cout<<end<<std::endl;
            performBFS(all, begin, end, true);
            performDjikstras(all, builder, begin, end, true);
            //

        }

    } else {
        
    }
    return 0;
}





/*
int main(int argc, char *argv[]) {
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

    if(argc>1){
      Vertex begin=argv[1];
      Vertex end=argv[2];
      std::cout<<"Here's the shortest path by distance between these airports: "<<std::endl;
      std::cout<<search.find_route(all,begin,end)<<std::endl;
      return 0;
    }
    while(1){
      std::cout<<"Enter Code of Airport Your Flying From (type Q to quit): ";
      Vertex begin="";
      std::cin>>begin;
      std::cout<<begin<<std::endl;
      if(begin=="Q" || begin=="q"){
        break;
      }
      std::cout<<"Enter Code of Airport Your Flying Too (type Q to quit): ";
      Vertex end="";
      std::cin>>end;
      std::cout<<end<<std::endl;
      if(end=="Q" || end=="q"){
        break;
      }
      std::cout<<"Here's the shortest path by distance between these airports: "<<std::endl;
      std::cout<<search.find_route(all,begin,end)<<std::endl;
    }
    //g_.print();


    Drawer drawer = Drawer("Maps/output.png");
    std::pair<double, double> coord = {69, 420};
    //drawer.addAirport(coord);
    std::pair<double, double> JFK = {40.6398,-73.7789};
    std::pair<double, double> nothercoord = {450.5, 69.1234};

    drawer.addAirport({-55.340392,-68.243426});
    drawer.addAirport({35.998230,-5.601901});
    drawer.addAirport({71.061224,-156.349617});
    drawer.addAirport(JFK);
    drawer.drawMap();

    return 0;
}*/