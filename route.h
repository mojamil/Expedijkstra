#pragma once
#include <iostream>
struct Route {
    std::string source_code;
    int source_id;
    std::string destination_code;
    int destination_id;
};

/*
Copied and pasted from website, currently only using ones with stars in begining. Indeces of csv line is number before definition
0 Airline 	2-letter (IATA) or 3-letter (ICAO) code of the airline. 
1 Airline ID 	Unique OpenFlights identifier for airline (see Airline). 
*2 Source airport 	3-letter (IATA) or 4-letter (ICAO) code of the source airport. 
*3 Source airport ID 	Unique OpenFlights identifier for source airport (see Airport) 
*4 Destination airport 	3-letter (IATA) or 4-letter (ICAO) code of the destination airport. 
*5 Destination airport ID 	Unique OpenFlights identifier for destination airport (see Airport) 
6 Codeshare 	"Y" if this flight is a codeshare (that is, not operated by Airline, but another carrier), empty otherwise.
*7 Stops 	Number of stops on this flight ("0" for direct)
8 Equipment 	3-letter codes for plane type(s) generally used on this flight, separated by spaces

The data is UTF-8 encoded. The special value \N is used for "NULL" to indicate that no value is available, and is understood automatically by MySQL if imported.
Notes:

    Routes are directional: if an airline operates services from A to B and from B to A, both A-B and B-A are listed separately.
    Routes where one carrier operates both its own and codeshare flights are listed only once. 
*/