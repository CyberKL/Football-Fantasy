#pragma once

#include <nlohmann/json.hpp>
#include "Manager.h"

using json = nlohmann::json;
using namespace std;

class FootballTeam;

class Footballer
{
private:
	static int count;
	string name;
	int id;
	string leagueName;
	int price;
	map<int, int> gwPoints;
	int totalPoints;
	string position;
	FootballTeam* team;

public:
	// Constructor
	Footballer(); // Default constructor


	// Getters
	static int getCount();
	string getName() const;
	int getId() const;
	string getLeagueName() const;
	int getPrice() const;
	map<int, int> getGwPoints() const;
	int getTotalPoints() const;
	string getPosition() const;
	FootballTeam* getTeam() const;

	// Setters
	void setTeam(FootballTeam&);
	void setLeagueName(string league);


	//functions
	void updatePoints(int goals);
	void updatePrice();
	string priceToString() const;

	// Handles file serialization to and from JSON
	json toJson();
	void fromJson(json&);

};

