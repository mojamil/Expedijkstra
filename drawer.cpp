#include "drawer.h"
#include "cs225/Animation.h"

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

void Drawer::addAirports(Graph& g, GraphBuilder& builder, std::vector<Vertex> route) {
    for (Vertex vertex : route) {
        Airport airport = builder.get_airport_from_code(vertex);
        const std::pair<double, double>& coord = {airport.latitude, airport.longitude};
        addAirport(coord);
    }
}


std::pair<int, int> Drawer::convertCoordsToPixel(double latitude, double longitude) {
    //remeber goes in lat long, but comes out x, y which is opposite
    //there are 360 longitudinal lines
    if (longitude < -180 || longitude > 180 || latitude < -90 || latitude > 90) {
        std::cout << "Warning. Airport with coordinates " << latitude << ", " << longitude << " are invalid and may not print!" << std::endl;
    }
    int x = PRIME_MERIDIAN + ((this->map_width * longitude) / 360);
    if (longitude < LEFT_SIDE_LONG) {
        x = this->map_width + x;
    } 
    //-3 was just trial and error specific to b/w map
    int y = EQUATOR - ((this->map_height * latitude) / 180) - 3;
    return std::pair<int, int>(x, y);
}



void Drawer::drawMap(cs225::HSLAPixel route_color = {216, 1, .7, 1}) {

   // for (std::pair<double, double> airport_coord : this->airport_coords) {
    
 
    //airport_coords.push_back({-1.2120699882507324,-78.57460021972656,8502}
    cs225::HSLAPixel Color;
    for (unsigned long f = 0; f < airport_coords.size(); ++f) {
        std::pair<int, int> pixel_coords = convertCoordsToPixel(airport_coords[f].first, airport_coords[f].second);
        //std::cout << pixel_coords.first << "," << pixel_coords.second << std::endl;
        if (f == 0) {
            Color = {0, 1, .25};
        } else if (f == airport_coords.size() - 1) {
            Color = GREEN;
        } else {
            Color = LIGHT_BLUE;
        }
        for (int x = std::max(0, pixel_coords.first - (this->map_width/AIRPORT_SIZE_MULTIPLIER)); x < std::min(this->map_width, pixel_coords.first + (this->map_width/AIRPORT_SIZE_MULTIPLIER)); ++x)  {
            for (int y = std::max(0, pixel_coords.second - (this->map_width/AIRPORT_SIZE_MULTIPLIER)); y < std::min(this->map_height, pixel_coords.second + this->map_width/AIRPORT_SIZE_MULTIPLIER);++y) {
                png->getPixel(x, y) = Color;
            }
        }
    }

    cs225::Animation animation;

    for (unsigned long f = 0; f < this->airport_coords.size() - 1; ++f) {
        std::pair<double, double> curr_airport = airport_coords[f];
        std::pair<double, double> next_airport = airport_coords[f + 1];
        std::pair<int, int> first_pixel = convertCoordsToPixel(curr_airport.first, curr_airport.second);
        std::pair<int, int> second_pixel = convertCoordsToPixel(next_airport.first, next_airport.second);
        if (first_pixel.first > second_pixel.first) {
            //Algorithm goes left to right, so swap nessisary
            std::swap(first_pixel, second_pixel);
        }

        //pseudocode based on https://en.wikipedia.org/wiki/Line_drawing_algorithm
        auto dx = second_pixel.first - first_pixel.first;
        auto dy = second_pixel.second - first_pixel.second;

        for (int x = first_pixel.first; x < second_pixel.first; ++x) {
            int y = first_pixel.second + dy * (x - first_pixel.first) / dx;
            png->getPixel(x - 1, y) = route_color;
            png->getPixel(x, y) = route_color;
            png->getPixel(x + 1, y) = route_color;
        }
    }

    png->writeToFile(output_file_name);
}
