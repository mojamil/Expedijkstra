#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include "airport.h"
#include "route.h"
#include "graph.h"


class Search{
    public:
        void BFS(Graph * G, Vertex source, Vertex destination);
        
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
        std::string find_route(Graph G,Vertex start,Vertex end);
    private:

        unordered_map<Vertex,Vertex> predecessor;
        std::vector<Vertex> visited_vertices;
};