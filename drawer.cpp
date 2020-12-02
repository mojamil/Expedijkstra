#include "drawer.h"


Drawer::Drawer(const std::string output) : output_file_name(output) {
//this->output_file_name = output;
    this->png = new cs225::PNG();
    png->readFromFile(empty_map_file);
    this->map_width = png->width();
    this->map_height = png->height();
    
}

Drawer::~Drawer() {
    delete this->png;
}

void Drawer::addAirport(const std::pair<double, double>& coords) {
    this->airport_coords.push_back(coords);
}

void Drawer::addAirports(std::vector<const std::pair<double, double>>& coords) {
    for (const std::pair<double, double>& coord : coords) {
        addAirport(coord);
    }
}



void Drawer::drawMap() {

   // for (std::pair<double, double> airport_coord : this->airport_coords) {
    
    
    //std::pair<double, double> pair = {69, 450};
    auto dA = this->airport_coords.size();
    auto dB = this->airport_coords[1];
    for (std::pair<double, double>& airport_coord : this->airport_coords) {
        for (int x = std::max(0.0, airport_coord.first - (this->map_width/AIRPORT_SIZE_MULTIPLIER)); x < std::min((double)this->map_width, airport_coord.first + (this->map_width/AIRPORT_SIZE_MULTIPLIER)); ++x)  {
            for (int y = std::max(0.0, airport_coord.second - (this->map_width/AIRPORT_SIZE_MULTIPLIER)); y < std::min((double)this->map_height, airport_coord.second + this->map_width/AIRPORT_SIZE_MULTIPLIER);++y) {
                png->getPixel(x, y) = LIGHT_BLUE;
            }
        }
    }

/*
    for (int x = 0; x < this->map_width; ++x) {
        for (int y = 0; y < this->map_height; ++y) {
            //if (x % 2 == 0 && (y % 2 == 0)) {
                png->getPixel(x, y) = {40, .5, .5 , 1};
            //}
        }
    }*/
    png->writeToFile(output_file_name);
}
