#include "searches.h"
#include "drawer.h"
std::unordered_map<Vertex,double> distance;
//Custom comparator class to use for priority queue
//We figured out how to write a custom comparator using this tutorial https://neutrofoton.github.io/blog/2016/12/29/c-plus-plus-priority-queue-with-comparator/
class Comparator{
    public:
        /**
        * A class that is passed as an argument to the priority queue intialization
        * Compares the value of two vertices using the distance map.
        * @param v1 - One of the vertices to compare
        * @param v2 - The other vertex to compare
        * @return If vertex v1 has a greater distance from source
        */
        bool operator() (Vertex v1,Vertex v2){
            return distance[v1]>distance[v2];
        }
};

void Search::animateBFS(Graph* G, GraphBuilder& builder, Vertex source, Vertex destination, string output_file = "Maps/output.gif", int max_edges = 4, cs225::HSLAPixel color = cs225::HSLAPixel({.5, .5, .5, .5})) {
    unordered_map<Vertex, string> nodeStateList;
    int given_source = 1;
    // creating two unordered maps which store the state of the node and edge
    
    //unordered_map<Edge, string> edgeStateList; 

    //depth variable helps keep track of path length
    Animation animation;
    Drawer drawer("Maps/bfs.png");
    if(given_source){
        for (Vertex vertex : G -> getVertices()) {
            nodeStateList.insert({vertex, "UNEXPLORED"});
        }
        for (Edge edge : G -> getEdges()) {
            G->setEdgeLabel(edge.source,edge.dest,"UNEXPLORED");
            //edgeStateList.insert({edge, "UNUSED"});
        }
    }

    if (!G->vertexExists(source)) {
        //return "Invalid Input";
    } else {
        Vertex vert=source;
        if(nodeStateList[vert]=="UNEXPLORED"){
            std::queue <Vertex> myQueue;
            if(nodeStateList[vert]!="VISITED"){
                visited_vertices.push_back(vert);
            }
            nodeStateList[vert] = "VISITED";

            int num_flights = 0;
            
            myQueue.push(vert);
            while (!myQueue.empty()) {
                source=myQueue.front();
                myQueue.pop();
                for (Vertex vertex : G -> getAdjacent(source)) {
                    Edge edge = G -> getEdge(source, vertex);
                    if (nodeStateList[vertex] == "UNEXPLORED") {
                        if(nodeStateList[vertex]!="VISITED"){
                            visited_vertices.push_back(vertex);
                        }
                        nodeStateList[vertex] = "VISITED";
                        G->setEdgeLabel(edge.source,edge.dest,"DISCOVERY");
                        drawer.drawAirport(builder.get_airport_from_code(edge.source),
                                {60, 1, .5});
                        drawer.drawFlight(builder.get_airport_from_code(edge.source), 
                                builder.get_airport_from_code(edge.dest), {.5, .5, .5, .5});
                        drawer.drawAirport(builder.get_airport_from_code(edge.dest),
                             {60, 1, .5});
                        //edgeStateList[edge] == "PATH EDGE";
                        animation.addFrame(*drawer.getPNG());
                        num_flights += 1;
                        if (num_flights >= max_edges) {
                            animation.write(output_file);
                            return;
                        }
                        myQueue.push(vertex);
                    } else if (edge.getLabel() == "UNEXPLORED") {
                        G->setEdgeLabel(edge.source,edge.dest,"CROSS EDGE");
                    }
                }
            }
        } 
    }
    animation.write(output_file);

    /*
        // creating two unordered maps which store the state of the node and edge
    unordered_map<Vertex, string> nodeStateList;
    //unordered_map<Edge, string> edgeStateList; 
    Animation animation;
    Drawer drawer("Maps/bfs.png");

    animation.addFrame(*drawer.getPNG());
    
    //depth variable helps keep track of path length
    int depth = 0;
    
    // for loops for initialising states of nodes and edges
    for (Vertex vertex : G -> getVertices()) {
        nodeStateList.insert({vertex, "UNEXPLORED"});
    }

    for (Edge edge : G -> getEdges()) {
        G->setEdgeLabel(edge.source,edge.dest,"UNEXPLORED");
        //edgeStateList.insert({edge, "UNUSED"});
    }

    // for (Vertex vertex : G -> getVertices()) {
    //     myQueue.push(vertex);
    // 

    if (!G->vertexExists(source) && !G->vertexExists(destination)) {
        //return "Invalid Input";
    } else {
        int num_edges = 0; 
        for (Vertex vert : G -> getVertices()) {
            if(nodeStateList[vert]=="UNEXPLORED"){
                std::queue <Vertex> myQueue;
                if(nodeStateList[vert]!="VISITED"){
                    visited_vertices.push_back(vert);
                }
                nodeStateList[vert] = "VISITED";

                
                myQueue.push(vert);
                while (!myQueue.empty()) {
                    source=myQueue.front();
                    myQueue.pop();
                    for (Vertex vertex : G -> getAdjacent(source)) {
                        Edge edge = G -> getEdge(source, vertex);
                        if (nodeStateList[vertex] == "UNEXPLORED") {
                            if(nodeStateList[vertex]!="VISITED"){
                                visited_vertices.push_back(vertex);
                            }
                            nodeStateList[vertex] = "VISITED";
                            G->setEdgeLabel(edge.source,edge.dest,"PATH EDGE");
                            //draws airport onto png
                            drawer.drawAirport(builder.get_airport_from_code(edge.source),
                                {60, 1, .5});
                            drawer.drawFlight(builder.get_airport_from_code(edge.source), 
                                builder.get_airport_from_code(edge.dest), {.5, .5, .5, .5});
                            drawer.drawAirport(builder.get_airport_from_code(edge.dest),
                                {60, 1, .5});
                            animation.addFrame(*drawer.getPNG());
                            //animation.write(output_file); ////
                            ++num_edges;
                            //edgeStateList[edge] == "PATH EDGE";
                        } else if (edge.getLabel() == "UNEXPLORED") {
                            G->setEdgeLabel(edge.source,edge.dest,"CROSS EDGE");
                            //todo maybe add different color edge here
                        }
                        if (num_edges >= max_edges) {
                            animation.write(output_file);
                            return;
                        }
                    }
                }
            } 
        }
    }*/
}

void Search::BFS(Graph * G, Vertex source, Vertex destination){
    
    // creating two unordered maps which store the state of the node and edge
    unordered_map<Vertex, string> nodeStateList;
    //unordered_map<Edge, string> edgeStateList; 

    //depth variable helps keep track of path length
    int depth = 0;
    
    // for loops for initialising states of nodes and edges
    for (Vertex vertex : G -> getVertices()) {
        nodeStateList.insert({vertex, "UNEXPLORED"});
    }

    for (Edge edge : G -> getEdges()) {
        G->setEdgeLabel(edge.source,edge.dest,"UNEXPLORED");
        //edgeStateList.insert({edge, "UNUSED"});
    }

    // for (Vertex vertex : G -> getVertices()) {
    //     myQueue.push(vertex);
    // 

    if (!G->vertexExists(source) && !G->vertexExists(destination)) {
        //return "Invalid Input";
    } else {
        for (Vertex vert : G -> getVertices()) {
            if(nodeStateList[vert]=="UNEXPLORED"){
                std::queue <Vertex> myQueue;
                if(nodeStateList[vert]!="VISITED"){
                    visited_vertices.push_back(vert);
                }
                nodeStateList[vert] = "VISITED";

                
                myQueue.push(vert);
                while (!myQueue.empty()) {
                    source=myQueue.front();
                    myQueue.pop();
                    for (Vertex vertex : G -> getAdjacent(source)) {
                        Edge edge = G -> getEdge(source, vertex);
                        if (nodeStateList[vertex] == "UNEXPLORED") {
                            if(nodeStateList[vertex]!="VISITED"){
                                visited_vertices.push_back(vertex);
                            }
                            nodeStateList[vertex] = "VISITED";
                            G->setEdgeLabel(edge.source,edge.dest,"PATH EDGE");
                            //edgeStateList[edge] == "PATH EDGE";
                        } else if (edge.getLabel() == "UNEXPLORED") {
                            G->setEdgeLabel(edge.source,edge.dest,"CROSS EDGE");
                        }
                    }
                }
            } 
        }
    }
    // for (Vertex vertex : visited_vertices) {
    //     std::cout<<vertex<<std::endl;
    // }
}

void Search::Dijkstra(Graph G, Vertex s){
    // Priority queue of vertexes
    std::priority_queue<Vertex, std::vector<Vertex>, Comparator> pq;
    //Set distance of each vertex to infinity and the predecessor to empty string
    for(auto &v:G.getVertices()){
        distance[v]=INT_MAX;
        predecessor[v]="";
    }
    //Set the source to 0
    distance[s]=0;
    //Push all the vertexes to the priority queue
    for(auto &v:G.getVertices()){
        pq.push(v);
    }
    //Graph to keep track of visited vertexes
    Graph T(true,true);
    while(pq.size()!=0){
        
        //Get the vertex with minimum distance from the source
        Vertex u=pq.top();
        while(T.vertexExists(u)&&pq.size()!=0){
            u=pq.top();
            pq.pop();
        }
        T.insertVertex(u);

        //Loop through the adjacent vertices
        
        for (auto &v : G.getAdjacent(u))
        {
            // If the vertex was not visited
            // std::cout<<v<<std::endl;
            if(!T.vertexExists(v)){
                int cost=G.getEdgeWeight(u,v);

                // Set the distance between source and vertex to the smallest distance
                if((cost+distance[u])<distance[v]){
                    distance[v]=(cost+distance[u]);
                    predecessor[v]=u;
                }
                //push the vertex after it's weight is set to the priority queue
                pq.push(v);
            }
        }
    }
}

std::vector<std::string> Search::find_route_in_vector(Graph& G, Vertex start, Vertex end) {
    std::vector<std::string> path;
    if(!G.vertexExists(end)||!G.vertexExists(start)){
        //std::cout << "Airport Code Incorrect" << std::endl;
        return std::vector<std::string>();
    }
    std::string out="";
    Dijkstra(G, start);

    Vertex curr=end;
    out+=end;

    path.insert(path.begin(), 1, curr);
    while(curr!=start){
        if(predecessor[curr]==""){
            //std::cout << "No route between two airports" << std::endl;
            return std::vector<std::string>();
        }
        curr=predecessor[curr];
        path.insert(path.begin(), 1, curr);
        //out=curr+" -> "+out;
    }
    return path;
}

std::string Search::find_route(Graph& G,Vertex start,Vertex end){
    //Run Djikstra's algorithm and then print out the stops in order
    if(!G.vertexExists(end)||!G.vertexExists(start)){
        return "Airport Code Incorrect";
    }
    std::string out="";
    Dijkstra(G, start);

    Vertex curr=end;
    out+=end;
    while(curr!=start){
        if(predecessor[curr]==""){
            return "No route between two airports";
        }
        curr=predecessor[curr];
        out=curr+" -> "+out;
    }
    return out;
}