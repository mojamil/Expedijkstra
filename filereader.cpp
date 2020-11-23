//#pragma once
#include "filereader.h"
#include "airport.h"
#include <fstream>
#include <sstream>

std::vector<Airport> Reader::getAirportsFromFile(const std::string& file_name) {
    std::vector<std::vector<std::string>> raw_airports = readCSV(file_name);
    std::vector<Airport> airports = std::vector<Airport>();
    for (auto& airport_properties : raw_airports) {
        Airport airport;
        airport.id = std::stoi(airport_properties[0]);
        airport.name = airport_properties[1];
        airport.city = airport_properties[2];
        airport.country = airport_properties[3];
        airport.code = airport_properties[4];
        airport.latitude = std::stod(airport_properties[6]); //todo worry about negatice
        airport.longitude = std::stod(airport_properties[7]);
        airports.push_back(airport);
    }
    return airports;
    
}

//This is used to convert string to its respective int. It handles Null or '\N' as -1, so use it 
//instead of stoi in getroutesfromfile, as a lot of their values for the airports codes that 
//I believe are unknown are '\N'
int convertStringToInt(std::string str) {
    try {
        int num = std::stoi(str);
        return num;
    } catch(...) {
        return -1;
    }
}

std::vector<Route> Reader::getRoutesFromFile(const std::string& file_name) {
    std::vector<std::vector<std::string>> raw_routes = readCSV(file_name);
    std::vector<Route> routes = std::vector<Route>();
    for (auto& route_properties : raw_routes) {
        Route route;
        route.source_code = route_properties[2];
        route.source_id = convertStringToInt(route_properties[3]);
        //route.source_id = std::stoi(route_properties[3]);
        route.destination_code = route_properties[4];
        route.destination_id = convertStringToInt(route_properties[5]);
        //route.destination_id = std::stoi(route_properties[5]);
        route.num_stops = convertStringToInt(route_properties[7]);
        //route.num_stops = std::stoi(route_properties[7]);
        routes.push_back(route);
    }
    return routes;
}

const std::vector<std::vector<std::string>> Reader::readCSV(const std::string& file_name) const {
    std::vector<std::vector<std::string>> vec = std::vector<std::vector<std::string>>();
    std::ifstream file (file_name);
    std::string line;
    while (std::getline(file,line))
    {
        std::stringstream stream_line(line);
        std::vector<std::string> line_properties;
        while(stream_line.good())
        {
            std::string element;
            std::getline(stream_line, element, ',' );
            line_properties.push_back(element);
        }
        vec.push_back(line_properties);
    }
    file.close();
    return vec;
}