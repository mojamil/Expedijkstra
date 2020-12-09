
#include <iostream>
#include <vector>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "graphbuilder.h"

class Drawer {
public:
//see below, input is hardcoded to prevent complications
//output should be .png file
Drawer(const string output_file_name);
Drawer(const string& output_file_name, std::pair<double, double> longlats);
~Drawer();
void drawMap(cs225::HSLAPixel route_color);
void addAirport(const std::pair<double, double>& coords);
void addAirports(std::vector<const std::pair<double, double>>& coords);
void addAirports(Graph& g, GraphBuilder& builder, std::vector<Vertex> route);


private:
//hard coded cuz I don't believe method would be adaptible to 
//other maps maybe change later
const std::string empty_map_file = std::string("Maps/empty_map.png"); 
cs225::PNG* png;
const std::string output_file_name;
int map_width; //1350 in black white map
int map_height; //675 in black white map
std::vector<std::pair<double, double>> airport_coords;
const int PRIME_MERIDIAN = 1350/2 - 1350/28; //only true in 
const int LEFT_SIDE_LONG = -167; //i can make it more formulaic later
const int EQUATOR = 337;

//Colors: see note on bottom 
cs225::HSLAPixel LIGHT_BLUE = {216, 1, .8 , 1};
cs225::HSLAPixel RED = {0,1,.5};
cs225::HSLAPixel GREEN = {120,1., .25};
//reverse multipier, larger means that point is smaller
const int AIRPORT_SIZE_MULTIPLIER = 200;
std::pair<int, int> convertCoordsToPixel(double latitude, double longitude);



};
//https://stackoverflow.com/questions/14329691/convert-latitude-longitude-point-to-a-pixels-x-y-on-mercator-projection
// https://www.december.com/html/spec/colorhsla.html
/*
Hue (denoted as h) defines the color itself, for example, red in distinction to blue or yellow. The values for the hue axis run from 0–360° beginning and ending with red and running through green, blue and all intermediary colors like greenish-blue, orange, purple, etc.

There are two hues that we’ll use later in this lab:

    “Illini Orange” has a hue of 11
    “Illini Blue” has a hue of 216

Saturation (denoted as s) indicates the degree to which the hue differs from a neutral gray. The values run from 0%, which is no color saturation, to 100%, which is the fullest saturation of a given hue at a given percentage of illumination.

Luminance (denoted as l) indicates the level of illumination. The values run as percentages; 0% appears black (no light) while 100% is full illumination, which washes out the color (it appears white).

The full HSL color space is a three-dimensional space, but it is not a cube (nor exactly cylindrical). The area truncates towards the two ends of the luminance axis and is widest in the middle range. The ellipsoid reveals several properties of the HSL color space:

    At l=0 or l=1 (the top and bottom points of the ellipsoid), the 3D space is a single point (the color black and the color white). Hue and saturation values don’t change the color.
    At s=0 (the vertical core of the ellipsoid), the 3D space is a line (the grayscale colors, defined only by the luminance). The values of the hue do not change the color.
    At s=1 (the outer shell of the ellipsoid), colors are vivid and dramatic!
*/