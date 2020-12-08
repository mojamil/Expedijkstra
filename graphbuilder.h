#pragma once
#include <iostream>
#include <vector>
#include "airport.h"
#include "route.h"
#include "graph.h"
#include <cmath>

class GraphBuilder{
    public:
        /**
        * Constructor to initialize graphbuilder class
        * @param airports - Vector containing all airports as Airport object
        * @param routes - Vector containing all airports as Route object
        * @param  airbc- A map whose keys are the string airport code 
        * and their value is the corresponding Airport object
        */
        GraphBuilder(std::vector<Airport>,std::vector<Route>,std::map<std::string,Airport>);
         /**
        * Creates a graph out of the airports and domestic routes in a certain country 
        * @param country - The name of the country from where we will get the airports
        * @return A graph with a vertex for each airport in the given country and edges
        * that are the routes between the airports
        */
        Graph country_subgraph(std::string);
        /**
        * Creates a graph out of the airports and routes of multiple countries 
        * @param countries - A vector of countries from where we will get the airports
        * @return A graph with a vertex for each airport in the given countries and edges
        * that are the routes between the airports
        */
        Graph countries_subgraph(std::vector<std::string>);

        /**
        * Creates a graph out of all the airports 
        * @return A graph with a vertex for each airport in the dataset and edges
        * that are the routes between the airports
        */
        Graph get_full_graph();
        
    private:
        /**
        * A function to find the distance between two airports to weight the graphs 
        * @param source - One of the airports
        * @param dest   - The other airport
        * @return The distance in miles between the two airports
        */
        double distance(Airport,Airport);
        std::map<std::string,Airport> airports_by_code;
        std::map<std::string,std::vector<Airport>> airports_by_country;
        std::vector<Route> routes_;
        Graph all_airports;
};