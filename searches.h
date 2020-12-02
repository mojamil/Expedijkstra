#pragma once
#include <iostream>
#include <vector>
#include "airport.h"
#include "route.h"
#include "graph.h"

class Search{
    public:
        void BFS(Graph G);
        void Dijkstra(Graph G, Vertex s);
};