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
        void BFS(Graph * G, Vertex source, Vertex destination);

        void animateBFS(Graph* G, GraphBuilder& builder, Vertex source, Vertex destination, string output_file, int max_depth, cs225::HSLAPixel color);
        
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
        //todo make doc
        std::vector<std::string> find_route_in_vector(Graph& G, Vertex start, Vertex end);
    private:

        unordered_map<Vertex,Vertex> predecessor;
        std::vector<Vertex> visited_vertices;
};