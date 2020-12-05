#include "searches.h"
unordered_map<Vertex,double> d;
//Custom comparator class to use for priority queue
class Comparator{
    public:
        bool operator() (Vertex v1,Vertex v2){
            return d[v1]>d[v2];
        }
};

void Search::BFS(Graph G){

}

void Search::Dijkstra(Graph G, Vertex s){
    // Priority queue of vertexes
    std::priority_queue<Vertex, std::vector<Vertex>, Comparator> pq;
    //Set distance of each vertex to infinity and the predecessor to empty string
    for(auto &v:G.getVertices()){
        d[v]=INT_MAX;
        p[v]="";
    }
    //Set the source to 0
    d[s]=0;
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
                if((cost+d[u])<d[v]){
                    d[v]=(cost+d[u]);
                    p[v]=u;
                }
                //push the vertex after it's weight is set to the priority queue
                pq.push(v);
            }
        }
    }
}

std::string Search::find_route(Graph G,Vertex start,Vertex end){
    //Run Djikstra's algorithm and then print out the stops in order
    if(!G.vertexExists(end)||!G.vertexExists(start)){
        return "Airport Code Incorrect";
    }
    std::string out="";
    Dijkstra(G, start);
    Vertex curr=end;
    out+=end;
    while(curr!=start){
        curr=p[curr];
        out=curr+" -> "+out;
    }
    return out;
}