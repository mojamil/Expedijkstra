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
         * Animates the bfs algorithm in the requested output file. Every layer of bfs is made
         * into a frame. Very similiar to other bfs method here, just with animation provided. Use is 
         * much quicker to run and produces a smaller gif file than regular animateBFS because their are much 
         * fewer layers for it to add to the animation. 
         * @param  G - graph running algorithm on
         * @param  Builder - graphbuilder object for use with airport.get_airport_from_code, which allows map to access latlon
         * @param  source - Vertex that traversal starts at
         * @param  output_file - file to output data to. .gif is what the endpoint should be to work correctly.
         * @param  max_edges - number of edges that are desired in animation.
         * @param  color - Color of routes.
         */
        void animateBFSByLayer(Graph* G, GraphBuilder& builder, Vertex source, string output_file = "Maps/output.gif", cs225::HSLAPixel color = cs225::HSLAPixel({.5, .5, .5, .5}));
        
        /** Animates the bfs algorithm in the requested output file. Every step of bfs that produces a path edge is made
         * into a frame. Very similiar to other bfs method here, just with animation provided. Takes much longer and much
         * bigger than previous method. Keep max_edges reasonable to avoid size failure.
         * @param  G - graph running algorithm on
         * @param  Builder - graphbuilder object for use with airport.get_airport_from_code, which allows map to access latlon
         * @param  source - Vertex that traversal starts at
         * @param  output_file - file to output data to. .gif is what the endpoint should be to work correctly.
         * @param  max_edges - number of edges that are desired in animation. Without this parameter, animation will take an incredibly large 
         * time to build and take up a lot of space. For reference 4 should be decent while 100 can take several minutes to build.
         * @param  color - Color of routes.
         */
        void animateBFSByEdges(Graph* G, GraphBuilder& builder, Vertex source, int max_edges, string output_file = "Maps/output.gif", cs225::HSLAPixel color = cs225::HSLAPixel({.5, .5, .5, .5}));

        /**
        * Runs Dijikstra's algorithm on a graph, G with starting vertex s.
        * The predecessors are stored in the map name predecessors 
        * @param G - The graph to run the algorithm on
        * @param s - The starting vertex
        */
        void Dijkstra(Graph G, Vertex s);

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