#pragma once

#include <nlohmann/json.hpp>
#include "Manager.h"
#include <string>

using json = nlohmann::json;
using namespace std;

class Footballer;

class FootballTeam
{
private:
	static int count;
	string name;
	int points;
	int id;
	string league;
	vector<Footballer*> footballers;

public:
	// Constructors
	FootballTeam(); // Default constructor
	FootballTeam(string, string); //parameterized constructor


	// Getters
	static int getCount();
	string getName() const;
	int getPoints();
	int getId();
	string getLeague() const;
	vector<Footballer*> getFootballers();

	// Handles file serialization to and from JSON
	json toJson();
	void fromJson(json&);
	void loadFootballer(Footballer*);

	//update points of team 
	void updatePoints(char );

};

