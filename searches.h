#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include "cs225/Animation.h"
#include "airport.h"
#include "route.h"
#include "graph.h"
#include "graphbuilder.h"


class Search{
    public:
        /**
        * Runs a BFS traversal starting at a random vertex and 
        * traverese every single vertex in the graph.
        * @param G - The graph to run the algorithm on
        */
        void BFS(Graph * G);

        void BFS(Graph * G, Vertex source);

        /**
         * Animates the bfs algorithm in the requested output file. Every step of bfs that produces a path edge is made
         * into a frame. Very similiar to other bfs method here, just with animation provided.
         * @param  G - graph running algorithm on
         * @param  Builder - graphbuilder object for use with airport.get_airport_from_code, which allows map to access latlon
         * @param  source - Vertex that traversal starts at
         * @param  output_file - file to output data to. .gif is what the endpoint should be to work correctly.
         * @param  max_edges - number of edges that are desired in animation.
         * @param  color - Color of routes.
         */
        void animateBFS(Graph* G, GraphBuilder& builder, Vertex source, string output_file = "Maps/output.gif", int max_edges = 4, cs225::HSLAPixel color = cs225::HSLAPixel({.5, .5, .5, .5}));
        
        /**
        * Runs Dijikstra's algorithm on a graph, G with starting vertex s.
        * The predecessors are stored in the map name predecessors 
        * @param G - The graph to run the algorithm on
        * @param s - The starting vertex
        */
        void Dijkstra(Graph G, Vertex s);

        /**
        * Wrapper function for the Dijsktra's algorithm that traces
        * the path from a certain destination to the starting
        * vertex
        * @param G - The graph to run the algorithm on
        * @param start - The starting vertex
        * @param end - The destination vertex
        * @return a path in string format
        */
        std::string find_route(Graph& G,Vertex start,Vertex end);

        /**
         * Finds the route by listing every element in the travesal order in vector form.
         * @param G - Graph being searched
         * @param start -Starting node of traversal
         * @param end - Ending node of travesal
         * @return - The path of traversal in vector format
         */ 
        std::vector<std::string> find_route_in_vector(Graph& G, Vertex start, Vertex end);

        /**The Vertcies that were visited in the travesal*/
        std::vector<Vertex> visited_vertices;

    private:

        unordered_map<Vertex,Vertex> predecessor;
};