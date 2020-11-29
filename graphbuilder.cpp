#include "graphbuilder.h"

GraphBuilder::GraphBuilder(std::vector<Airport> airports,std::vector<Route> routes): routes_(routes){
    for(auto &i:airports){
        // Store a subset of airports in the graph for testing
        airports_by_country[i.country].push_back(i);
    }
}

Graph GraphBuilder::country_subgraph(std::string country){
    Graph graph(true,true);
    for(auto &i:airports_by_country[country]){
        if(i.code!="\\N"){
            graph.insertVertex(i.code);
        }
    }
    for(auto &i:routes_){
        // Store only the routes related to the airports in the graph
        if(graph.vertexExists(i.source_code)&&graph.vertexExists(i.destination_code)){
            graph.insertEdge(i.source_code,i.destination_code);
        }
    }
    return graph;
}