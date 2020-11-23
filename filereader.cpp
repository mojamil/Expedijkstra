//#pragma once
#include "filereader.h"
#include <fstream>
void Reader::makeAirports(Graph& graph, const std::string& file_name) {
    std::vector<std::vector<std::string>> airports = readCSV(file_name);
    for (auto airport : airports) {
        
    }
}

void Reader::makeRoutes(Graph& graph, const std::string& file_name) {
    std::vector<std::vector<std::string>> routes = readCSV(file_name);
}

const std::vector<std::vector<std::string>> Reader::readCSV(const std::string& file_name) const {
    std::vector<std::vector<std::string>> vec = std::vector<std::vector<std::string>>();
    std::ifstream file (file_name);
    string line;
    while (std::getline(file,line))
    {
        std::stringstream stream_line(line);
        std::vector<string> line_properties;
        while(stream_line.good())
        {
            string element;
            getline(stream_line, element, ',' );
            line_properties.push_back(element);
        }
        vec.push_back(line_properties);
    }
    file.close();
    return vec;
}