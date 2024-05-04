#pragma once

#include <nlohmann/json.hpp>
#include "Manager.h"
#include <string>

using json = nlohmann::json;
using namespace std;

class FootballTeam
{
private:
	static int count;
	string name;
	int points;
	int id;
	string league;

public:
	// Constructors
	FootballTeam(); // Default constructor

	// Getters
	static int getCount();
	string getName() const;
	int getPoints();
	int getId();
	string getLeague() const;

	// Handles file serialization to and from JSON
	json toJson();
	void fromJson(json&);

	//update points of team 
	void updatePoints(char );

};

