#pragma once

#include <nlohmann/json.hpp>
#include "Manager.h"
#include <queue>

using json = nlohmann::json;

class Footballer;

class Match
{
private:
	static int count;
	int id;
	FootballTeam* homeTeam;
	FootballTeam* awayTeam;
	int gw;
	string league;
	string score;
	queue<Footballer*> scorers;
	bool played;

public:
	// Constructors
	Match(); // Default constructor

	// Getters
	static int getCount();
	int getId() const;
	FootballTeam* getHomeTeam() const;
	FootballTeam* getAwayTeam() const;
	int getGw() const;
	string getScore() const;
	queue<Footballer*> getScorers() const;
	bool getPlayed() const;

	// Handles file serialization to and from JSON
	json toJson();
	void fromJson(json&);
};

