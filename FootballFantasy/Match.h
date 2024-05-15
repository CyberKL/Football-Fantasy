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
	vector<Footballer*> scorers;
	bool played;

public:
	// Constructors
	Match(); // Default constructor
	Match(FootballTeam*, FootballTeam*, int, string);

	// Getters
	static int getCount();
	int getId() const;
	FootballTeam* getHomeTeam() const;
	FootballTeam* getAwayTeam() const;
	int getGw() const;
	string getScore() const;
	vector<Footballer*> getScorers() const;
	bool getPlayed() const;

	// Setters
	void setScore(string);
	void setScorers(vector<Footballer*>);
	void setPlayed(bool);

	// Handles file serialization to and from JSON
	json toJson();
	void fromJson(json&);
};

