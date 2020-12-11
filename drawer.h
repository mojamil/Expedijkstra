
#include <iostream>
#include <vector>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "graphbuilder.h"

class Drawer {
public:

/**
 *Create drawer object with only file name to output to.
 * @param output_file_name - file name to output to
 */
Drawer(const string output_file_name);

/**
 * Creates drawer with latitude longitude prebuilt inside
 * @param output_file_name - file name to output to
 */
Drawer(const string& output_file_name, std::pair<double, double> longlats);

//destructor
~Drawer();

/**
 * Draws map to a file. It does this by drawing every ariport in order it was added to object.
 * Note this shouldn't be used for anything that is more complex than ordered data, and all of 
 * that i.e BFS should be added manually using below drawAirport and drawFlight methods, this is
 * just a bit of a shortcut in this program used for Djkistras
 * @param route_color - color of route(edges)
 */
void drawPrebuiltMap(cs225::HSLAPixel route_color);

/**
 * Adds latdue and longitude of an. Note should be in order if using drawprebuilt funciton
 * @param coords - latlong of indiviudal airport
 */
void addAirport(const std::pair<double, double>& coords);

/**
 * Adds latdue and longitude of all the airports. Note should be in order if using drawprebuiltmap function, which is what
 * this function is primarily used.
 * @param coords - latlong of indiviudal airport
 */
void addAirports(std::vector<const std::pair<double, double>>& coords);

/**
 * Adds multiple airport to objects for use in drawPrebuiltMap function. This must be added in order, in order to 
 * be used in drawPrebuiltMap function
 * @param g - graph that is being used
 * @param builder - a graphbuilder object. This is needed because of the get_airport_from_code fucntion in 
 * the graphbuilder objects.
 */
void addAirports(Graph& g, GraphBuilder& builder, std::vector<Vertex> route);

/**
 * Draws airport onto screen. Needs no prior knowledge about airport, only an airport object. This is called in BFS, 
 * where the airports aren't stored. Draws it as a square with Color color if in valid coordinates
 * @param a - an Airport object
 * @param color = color wanted 
 */
void drawAirport(Airport a, cs225::HSLAPixel color);

/**
 * See above but with a set of coordinates that represent the latlong coordinates rather than an airport object
 */
void drawAirport(const std::pair<double, double> coords, cs225::HSLAPixel color);

/**
 * Draws flight from airport a to airport b. This is done in the color requested in a 3 pixel wide line
 * @param a - Source airport
 * @param b - Dest airport
 * @param color - Color of line
 */
void drawFlight(Airport a, Airport b, cs225::HSLAPixel color);

/**
 * See above but with coordinates rather than airport objects
 */
void drawFlight(std::pair<double, double> coorda, std::pair<double, double> coordb, cs225::HSLAPixel color);

/**
 * Returns the picture of the map at the time it is called. Used in Search.animateBFS() to create animation
 */
cs225::PNG* getPNG();

private:

const std::string empty_map_file = std::string("Maps/empty_map.png"); //currently not adaptable to other maps 

/** Stored png object, which is painting as a result of actions*/
cs225::PNG* png;

const std::string output_file_name;

const int map_width = 1350;
const int map_height = 675; 

//These are pixel parameters, because equator wasn't exactly middle and prime meridian were also not.
//If not using empty_map.png this needs to be recalibrated along with map_width and map_height
const int PRIME_MERIDIAN = 1350/2 - 1350/28; //This was done by trial and error 
const int LEFT_SIDE_LONG = -167; 
const int EQUATOR = 337;

//Colors in HSLAP: see note on bottom 
cs225::HSLAPixel LIGHT_BLUE = {216, 1, .8 , 1};
cs225::HSLAPixel RED = {0,1,.5};
cs225::HSLAPixel GREEN = {120,1., .25};

//reverse multipier, larger means that point is smaller
const int AIRPORT_SIZE_MULTIPLIER = 200;

/**A vector of airport_coords that is loaded and used in drawPrebuiltMaps(). It must be in order to print correctly*/
std::vector<std::pair<double, double>> airport_coords;

/**Converts from {lat, long} that data comes in into {x, y}. Note lat represents y direction and long represents x direction.*/
std::pair<int, int> convertCoordsToPixel(double latitude, double longitude);


};

//Notes -
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