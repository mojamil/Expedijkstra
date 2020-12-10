#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include "airport.h"
#include "route.h"
#include "graph.h"


class Search{
    public:
        /**
        * Runs a BFS traversal starting at a random vertex and 
        * traverese every single vertex in the graph.
        * @param G - The graph to run the algorithm on
        */
        void BFS(Graph * G);

        /**
        * Runs a BFS traversal starting at the source vertex
        * traverses to vertices in that vertex's connected
        * component
        * @param G - The graph to run the algorithm on
        * @param source - The starting vertex
        */
        void BFS(Graph * G, Vertex source);
        
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
        * @return a path in a vector
        */
        std::vector<std::string> find_route(Graph G,Vertex start,Vertex end);
        std::vector<Vertex> visited_vertices;
    private:

        unordered_map<Vertex,Vertex> predecessor;
};