#include <iostream>
#include <map>
#include <unordered_map>
#include "filereader.h"
#include "graph.h"
#include "drawer.h"
#include "graphbuilder.h"
#include "searches.h"
#include <array>

/**
 * input options:
 * no flags = graph bfs, djikstras, and vizualize
 * -d = djikstras 
 * -b = bfs 
 * -v = vizualize 
 * note they have to be seperated i.e -d -v -b and not -bdv
 * Order should matter
 * ex. ./air -b JFK; Does bfs traversal begininng at JFK
 * ex. ./air -d JFK; SFO - Does Dijkstras from JFK to SFO
 * ex. ./air -b -v JFK; Performs and vizualizes bfs from JFK
 * ex. ./air -d -v JFK SFO - Does Dijkstras from JFK to SFO and vizualizes it
 * ex. ./air Allows user to input to airports in loop to continueally find best route with Dijikstras.
 * 
*/

void vizualizeDijikstras(Graph& g, GraphBuilder& builder, std::vector<Vertex> route, cs225::HSLAPixel Color = {.5, .5, .5}) {
        Drawer drawer = Drawer("Maps/dijikstras.png");

        drawer.addAirports(g, builder, route);
        drawer.drawPrebuiltMap(Color);
        std::cout << "vizualized dijkstras algoirthm at Maps/dijikstras.png" << std::endl;
}

bool removeFlag(std::vector<string>& args, string flag) {
    for (unsigned long f = 0; f < args.size(); ++f) {
        if (args[f] == flag) {
            args.erase(args.begin() + f);
            return true;
        } 
    }
    return false;
}

int main(int argc, char *argv[]) {
    Reader reader;
    std::vector<std::string> arguements;
    //note doesn't put in first command
    //ex. ./air -bfs JFK = {-bfs, JFK} and not {./air, -bfs, JFK}
    for (int f = 1; f < argc; ++f) {
        arguements.push_back(argv[f]);
    }
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
    
    //bfs
    if(removeFlag(arguements, "-bfs") || removeFlag(arguements, "-b") || removeFlag(arguements, "-B")) {
        if (removeFlag(arguements, "-v")) {
          string file_name = "Maps/bfs.gif";
            search.animateBFS(&all, builder, arguements[0], file_name, 100);
            std::cout << "BFS vizaualized at: " << file_name << std::endl;
        } else if (arguements.size() > 0) {
            search.BFS(&all, arguements[0]); //bfs with provided params
        } else {
            search.BFS(&all); //bfs with no params
        }

        std::ofstream file;
        string file_name = "traversal_order.txt";
        file.open(file_name);
        for(auto &i:search.visited_vertices){
          file<<i<<"->";
        }
        std::cout << "BFS traversal printed to " << file_name << std::endl;
        file.close();
        return 0;
      }

      //dfs
      else if (removeFlag(arguements, "-d") || removeFlag(arguements, "-D")) {
        bool toVizualize = removeFlag(arguements, "-v");

        Vertex begin=arguements[0];
        Vertex end=arguements[1];
        std::cout<<"Here's the shortest path by distance between these airports: "<<std::endl;
        std::vector<std::string> path=search.find_route_in_vector(all,begin,end);
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

        if (toVizualize) {
            vizualizeDijikstras(all, builder, path);
        }
        
        return 0;
      }
    
    //no input or flags were given which means it keeps giving optimal route based on route
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
      std::vector<std::string> path=search.find_route_in_vector(all,begin,end);
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
