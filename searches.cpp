#include "searches.h"
unordered_map<Vertex,double> distance;
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

unordered_map<Vertex, string> nodeStateList;
int given_source=1;
void Search::BFS(Graph * G){
        // for loops for initialising states of nodes and edges
    for (Vertex vertex : G -> getVertices()) {
        nodeStateList.insert({vertex, "UNEXPLORED"});
    }

    for (Edge edge : G -> getEdges()) {
        G->setEdgeLabel(edge.source,edge.dest,"UNEXPLORED");
        //edgeStateList.insert({edge, "UNUSED"});
    }
    given_source=0;
    for (Vertex vertex : G -> getVertices()) {
        if(nodeStateList[vertex]=="UNEXPLORED"){
            BFS(G,vertex);
        }
    }
}

void Search::BFS(Graph * G, Vertex source){

    // creating two unordered maps which store the state of the node and edge
    
    //unordered_map<Edge, string> edgeStateList; 

    //depth variable helps keep track of path length
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
                        //edgeStateList[edge] == "PATH EDGE";
                        myQueue.push(vertex);
                    } else if (edge.getLabel() == "UNEXPLORED") {
                        G->setEdgeLabel(edge.source,edge.dest,"CROSS EDGE");
                    }
                }
            }
        } 
    }
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

std::vector<std::string> Search::find_route(Graph G,Vertex start,Vertex end){
    //Run Djikstra's algorithm and then print out the stops in order

    std::vector<std::string> path;
    if(!G.vertexExists(end)||!G.vertexExists(start)){
        return {"Airport Code Incorrect"};
    }
    Dijkstra(G, start);

    Vertex curr=end;
    path.insert(path.begin(),curr);
    while(curr!=start){
        if(predecessor[curr]==""){
            return {"No route between two airports"};
        }
        curr=predecessor[curr];
        path.insert(path.begin(),curr);
        
    }
    return path;
}