#pragma once
#include <iostream>

struct Airport {
    int id;
    std::string name;
    std::string city;
    std::string country;
    std::string code; //i.e. JFK, note it could be '\N' in which case its null
    double latitude; 
    double longitude;
};

/*
Copied and pasted from website, currently only using ones with stars in begining. Indeces of csv line is number before definition
*0 Airport ID 	Unique OpenFlights identifier for this airport.
*1 Name 	Name of airport. May or may not contain the City name.
*2 City 	Main city served by airport. May be spelled differently from Name.
*3 Country 	Country or territory where airport is located. See Countries to cross-reference to ISO 3166-1 codes.
*4 IATA 	3-letter IATA code. Null if not assigned/unknown.
*5 ICAO 	4-letter ICAO code.Null if not assigned.
*6 Latitude 	Decimal degrees, usually to six significant digits. Negative is South, positive is North.
*7 Longitude 	Decimal degrees, usually to six significant digits. Negative is West, positive is East.
8 Altitude 	In feet.
9 Timezone 	Hours offset from UTC. Fractional hours are expressed as decimals, eg. India is 5.5.
10 DST 	Daylight savings time. One of E (Europe), A (US/Canada), S (South America), O (Australia), Z (New Zealand), N (None) or U (Unknown). See also: Help: Time
11 Tz database time zone 	Timezone in "tz" (Olson) format, eg. "America/Los_Angeles".
12 Type 	Type of the airport. Value "airport" for air terminals, "station" for train stations, "port" for ferry terminals and "unknown" if not known. In airports.csv, only type=airport is included.
13 Source 	Source of this data. "OurAirports" for data sourced from OurAirports, "Legacy" for old data not matched to OurAirports (mostly DAFIF), "User" for unverified user contributions. In airports.csv, only source=OurAirports is included.
14 The data is UTF-8 encoded.

Note: Rules for daylight savings time change from year to year and from country to country. The current data is an approximation for 2009, built on a country level. Most airports in DST-less regions in countries that generally observe DST (eg. AL, HI in the USA, NT, QL in Australia, parts of Canada) are marked incorrectly.
*/