#include "filereader.h"
#include "graph.h"
#include "graphbuilder.h"
#include <iostream>
#include "searches.h"

int main(int argc, char *argv[]) {
    Reader reader;
    std::vector<Airport> airports = reader.getAirportsFromFile("Data/airports.dat");
    std::vector<Route> routes = reader.getRoutesFromFile("Data/routes.dat");
    std::unordered_map<std::string,Airport> airports_by_code;
    // Initialize a weighted and directed graph
    for(auto &i:airports){
        // Store a subset of airports in the graph for testing
        airports_by_code[i.code]=i;
    }
    GraphBuilder builder(airports,routes,airports_by_code);
    Graph bd=builder.country_subgraph("Bangladesh");
    Graph all=builder.get_full_graph();
    Search search;
    search.BFS(&bd,"DAC","ZYL");
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
      if(begin=="Q"){
        break;
      }
      std::cout<<"Enter Code of Airport Your Flying Too (type Q to quit): ";
      Vertex end="";
      std::cin>>end;
      std::cout<<end<<std::endl;
      if(end=="Q"){
        break;
      }
      std::cout<<"Here's the shortest path by distance between these airports: "<<std::endl;
      std::cout<<search.find_route(all,begin,end)<<std::endl;
    }
    return 0;
}