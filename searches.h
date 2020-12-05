#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include "airport.h"
#include "route.h"
#include "graph.h"
class Search{
    public:
        void BFS(Graph G);
        void Dijkstra(Graph G, Vertex s);
        std::string find_route(Graph G,Vertex start,Vertex end);
    private:
        bool compare(Vertex v1,Vertex v2);
        unordered_map<Vertex,Vertex> p;
};