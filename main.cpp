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
 * 
 * basics
 * no flags = Continually input two airports to get optimal route in command line
 * -d = djikstras 
 * -b = bfs
 * -v = vizualize 
 * 
 * bfs vizualizations customizations (must use -d and -b)
 * 
 * -ve or -v or -ve NUM: vizulize bfs with edge every second. Takes long time depending on num inputed.
 *  If no num or invalid num, it defaults to 4. Takes much quicker
 * -vl or -vl : vizualization of bfs with a new layer every frame, with the inputed number of edges.
 * 
 * note they have to be seperated i.e -d -v -b and not -bdv
 * Order should matter
 * ex. ./air -b JFK; Does bfs traversal begininng at JFK
 * ex. ./air -d JFK; SFO - Does Dijkstras from JFK to SFO
 * ex. ./air -b -ve JFK 100; Performs and vizualizes bfs from JFK. Vizualization adds a frame every edge, so very slow. Will add 100 frames.
 * ex. ./air -b -vl JFK; Performs and vizualizes bfs from JFK by layer (every bfs is done with that layer of depth).
 * ex. ./air -d -v JFK SFO - Does Dijkstras from JFK to SFO and vizualizes it
 * ex. ./air Allows user to input to airports in loop to continueally find best route with Dijikstras.
*/

/**
 * Quick helper function to draw Djikstras on map
 */
void vizualizeDijikstras(Graph& g, GraphBuilder& builder, std::vector<Vertex> route, cs225::HSLAPixel Color = {.5, .5, .5}) {
        Drawer drawer = Drawer("Maps/dijikstras.png");
        drawer.addAirports(g, builder, route);
        drawer.drawPrebuiltMap(Color);
        std::cout << "vizualized dijkstras algorithm at Maps/dijikstras.png" << std::endl;
}

/**
 * Returns true if flag is found, false otherwise. If that flag is found it is remove from vector.
 */
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
        if (removeFlag(arguements, "-v") || removeFlag(arguements, "-V") || removeFlag(arguements, "-ve") || removeFlag(arguements, "VE")) { // bfs by edges
          string file_name = "Maps/bfs_by_edges.gif";
            if (arguements.size() > 1 && !arguements[1].empty() && std::all_of(arguements[1].begin(), arguements[1].end(), ::isdigit)) {
              search.animateBFSByEdges(&all, builder, arguements[0], std::stoi(arguements[1]), file_name);
            } else { 
                int default_edges = 4;   
                std::cout << "No arguements for number of edges desired in vizualization, so defaulting to " << default_edges << std::endl;        
                search.animateBFSByEdges(&all, builder, arguements[0], default_edges, file_name);
            }
            std::cout << "BFS vizaualized at: " << file_name << std::endl;
        } else if (removeFlag(arguements, "-vl") || removeFlag(arguements, "-VL")) { //bfs by layer
          string file_name = "Maps/bfs_by_layer.gif";
          search.animateBFSByLayer(&all, builder, arguements[0], file_name); 
          std::cout << "BFS vizualized at: " << file_name << " by layer." << std::endl; 
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
        std::vector<std::string> path=search.find_route_in_vector(all,begin,end);

        if(path.size()<=1){
          std::cout << "No path between 2 airports. Potentially invalid airport, or no path. Exiting now." << std::endl;
          return 0;
        }

        std::cout<<"Here's the shortest path by distance between these airports: "<<std::endl;

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
