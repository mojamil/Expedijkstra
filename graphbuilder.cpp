#include "graphbuilder.h"
      
GraphBuilder::GraphBuilder(std::vector<Airport> airports,std::vector<Route> routes, std::map<std::string,Airport> airbc): airports_by_code(airbc), routes_(routes){
    for(auto &i:airports){
        // Map of airports by country so its faster to create graphs
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
            graph.setEdgeWeight(i.source_code,i.destination_code,distance(airports_by_code[i.source_code],airports_by_code[i.destination_code]));
        }
    }
    for (auto &i : graph.getVertices())
    {
        if(graph.getAdjacent(i).size()==0){
            graph.removeVertex(i);
        }
    }
    
    return graph;
}

Graph GraphBuilder::countries_subgraph(std::vector<std::string> countries){
    Graph graph(true,true);
    for(auto &country:countries){
        for(auto &i:airports_by_country[country]){
            if(i.code!="\\N"){
                graph.insertVertex(i.code);
            }
        }
    }
    for(auto &i:routes_){
        // Store only the routes related to the airports in the graph
        if(graph.vertexExists(i.source_code)&&graph.vertexExists(i.destination_code)){
            graph.insertEdge(i.source_code,i.destination_code);
            graph.setEdgeWeight(i.source_code,i.destination_code,distance(airports_by_code[i.source_code],airports_by_code[i.destination_code]));
        }
    }
    for (auto &i : graph.getVertices())
    {
        if(graph.getAdjacent(i).size()==0){
            graph.removeVertex(i);
        }
    }
    return graph;
}
double GraphBuilder::distance(Airport source,Airport dest){
    // Using Haversine Formula
    std::vector<double> latlon;
    latlon.push_back(source.latitude*((M_PI)/180));
    latlon.push_back(source.longitude*((M_PI)/180));
    latlon.push_back(dest.latitude*((M_PI)/180));
    latlon.push_back(dest.longitude*((M_PI)/180));
    double latdiff=latlon[2]-latlon[0];
    double londiff=latlon[3]-latlon[1];
    double dist=(sin(latdiff/2)*sin(latdiff/2))+cos(latlon[2])*cos(latlon[0])*(sin(londiff/2)*sin(londiff/2));
    dist = sqrt(dist);
    dist = 2*asin(dist);
    // 3956 radius of earth in miles
    dist = 3956 * dist;
    return dist;
}