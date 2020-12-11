#include "drawer.h"
#include "cs225/Animation.h"

Drawer::Drawer(const std::string output) : output_file_name(output) {
//this->output_file_name = output;
    this->png = new cs225::PNG();
    png->readFromFile(empty_map_file);    
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
    //Inspired by https://stackoverflow.com/questions/14329691/convert-latitude-longitude-point-to-a-pixels-x-y-on-mercator-projection

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

void Drawer::drawAirport(Airport a, cs225::HSLAPixel color) {
    const std::pair<double, double> coords = std::pair<double, double>(a.latitude, a.longitude);
    drawAirport(coords, color);
}

void Drawer::drawAirport(const std::pair<double, double> coords, cs225::HSLAPixel color) {
    auto pixel_coords = convertCoordsToPixel(coords.first, coords.second);
    for (int x = std::max(0, pixel_coords.first - (this->map_width/AIRPORT_SIZE_MULTIPLIER)); x < std::min(this->map_width, pixel_coords.first + (this->map_width/AIRPORT_SIZE_MULTIPLIER)); ++x)  {
        for (int y = std::max(0, pixel_coords.second - (this->map_width/AIRPORT_SIZE_MULTIPLIER)); y < std::min(this->map_height, pixel_coords.second + this->map_width/AIRPORT_SIZE_MULTIPLIER);++y) {
            png->getPixel(x, y) = color;
        }
    }
}


void Drawer::drawFlight(Airport a, Airport b, cs225::HSLAPixel color) {
    drawFlight(std::pair<double, double>(a.latitude, a.longitude), std::pair<double, double>(b.latitude, b.longitude), color);
}

void Drawer::drawFlight(std::pair<double, double> coorda, std::pair<double, double> coordb, cs225::HSLAPixel color) {
    std::pair<int, int> first_pixel = convertCoordsToPixel(coorda.first, coorda.second);
    std::pair<int, int> second_pixel = convertCoordsToPixel(coordb.first, coordb.second);
    if (first_pixel.first > second_pixel.first) {
        //Algorithm goes left to right, so swap nessisary
        std::swap(first_pixel, second_pixel);
    }

    //pseudocode based on https://en.wikipedia.org/wiki/Line_drawing_algorithm
    auto dx = second_pixel.first - first_pixel.first;
    auto dy = second_pixel.second - first_pixel.second;

    for (int x = first_pixel.first; x < second_pixel.first; ++x) {
        int y = first_pixel.second + dy * (x - first_pixel.first) / dx;
        png->getPixel(x - 1, y) = color;
        png->getPixel(x, y) = color;
        png->getPixel(x + 1, y) = color;
    }
}



void Drawer::drawPrebuiltMap(cs225::HSLAPixel route_color = {216, 1, .7, 1}) {

    cs225::HSLAPixel color;
    for (unsigned long f = 0; f < airport_coords.size(); ++f) {
        std::pair<int, int> pixel_coords = convertCoordsToPixel(airport_coords[f].first, airport_coords[f].second);
        if (f == 0) {
            color = RED;
        } else if (f == airport_coords.size() - 1) {
            color = GREEN;
        } else {
            color = LIGHT_BLUE;
        }

        drawAirport(airport_coords[f], color);
    }

    for (unsigned long f = 0; f < this->airport_coords.size() - 1; ++f) {
        drawFlight(airport_coords[f], airport_coords[f + 1], route_color);
    }

    png->writeToFile(output_file_name);
}

cs225::PNG* Drawer::getPNG() {
    return this->png;
}
