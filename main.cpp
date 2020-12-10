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
    Graph all=builder.get_full_graph();
    Search search;
    if(argc>1){
      int tag=strcmp(argv[1],"-bfs");
      if(tag==0){
        if(argc>2){
          search.BFS(&all,argv[2]);
        }
        else{
          search.BFS(&all);
        }
        //all.print("BFS.txt");
        std::ofstream file;
        file.open("traversal_order");
        for(auto &i:search.visited_vertices){
          file<<i<<"->";
        }
        file.close();
      }
      else{
        Vertex begin=argv[1];
        Vertex end=argv[2];
        std::cout<<"Here's the shortest path by distance between these airports: "<<std::endl;
        std::vector<std::string> path=search.find_route(all,begin,end);
        if(path.size()==1){
          std::cout<<path[0]<<std::endl;
          return 0;
        }
        for(auto &i:path){
          if(i!=path[path.size()-1]){
            std::cout<<airports_by_code[i].name<<", "<<airports_by_code[i].city<<" -> ";
          }
          else{
            
            std::cout<<airports_by_code[i].name<<", "<<airports_by_code[i].city<<std::endl;
          }
        }
      }
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
      std::vector<std::string> path=search.find_route(all,begin,end);
      if(path.size()==1){
        std::cout<<path[0]<<std::endl;
        return 0;
      }
      for(auto &i:path){
        if(i!=path[path.size()-1]){
          std::cout<<airports_by_code[i].name<<", "<<airports_by_code[i].city<<" -> ";
        }
        else{
          std::cout<<airports_by_code[i].name<<", "<<airports_by_code[i].city<<std::endl;
        }
      }
    }
    return 0;
}