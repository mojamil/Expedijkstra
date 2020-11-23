#include "filereader.h"
#include "graph.h"
int main() {
    Reader reader;
    Graph graph(false);
    reader.makeAirports(graph, "Data/airports.dat");
    return 0;
}