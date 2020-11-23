#pragma once
#include <iostream>
#include <vector>
#include "graph.h"
class Reader {
    public:
        void makeAirports(Graph& graph, const std::string& file_name);
        void makeRoutes(Graph& graph, const std::string& file_name);
    private:
        const std::vector<std::vector<std::string>> readCSV(const std::string& file_name) const;

};