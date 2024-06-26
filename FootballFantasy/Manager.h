#pragma once

#include <unordered_map>
#include <map>
#include <string>
#include <fstream>
#include "Player.h"
#include "League.h"

using namespace std;

// This class follows the singleton design pattern
// Only one instance of the class can be created

class Player;
class Footballer;
class FootballTeam;
class League;
class Match;

class Manager
{
private:
	static Manager* instance;

	unordered_map<int, Player*> players;
	map<string, League*> leagues;
	unordered_map<int, Footballer*> footballers;
	unordered_map<int, FootballTeam*> footballTeams;
	map<int, unordered_map<int, Match*>> matches;
	map<string, int> counts;
	int currentGw; // should not be intialized here
	unordered_map<int, map<int, vector<string>>> gwOrderedPlayers;
	map<int, vector<string>> orderedPlayers;
	double totalRate;
	double rate;
	bool seasonStarted;

	Manager(); //Private constructor to prevent instantiation

	// Delete copy constructor and assignment operator to prevent copying
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;
	
public:
	// Destructor
	~Manager();

	// Method to get the singleton instance
	static Manager* getInstance();

	// Getters
	unordered_map<int, Player*> getPlayers();
	map<string, League*> getLeagues();
	unordered_map<int, Footballer*> getFootballers();
	unordered_map<int, FootballTeam*> getFootballTeams();
	map<int, unordered_map<int, Match*>> getMatches();
	map<string, int> getCounts();
	int getCurrentGw();
	unordered_map<int, map<int, vector<string>>> getGwOrderedPlayers();
	map<int, vector<string>> getOrderedPlayers();
	bool getSeasonStarted();

	// Setters
	void setPlayers(const unordered_map<int, Player*>&);
	void setLeagues(const std::map<std::string, League*>&);
	void setFootballers(const std::unordered_map<int, Footballer*>&);
	void setFootballTeams(const std::unordered_map<int, FootballTeam*>&);
	void setMatches(const std::map<int, std::unordered_map<int, Match*>>&);
	void setSeasonStarted(bool);

	bool isUsernameDuplicate(const string&);
	void addPlayer(const string&, const string&);

	Player* login(const string&, const string&);
	Match findNextMatch(const FootballTeam*);
	vector<Footballer> searchFootballersByPosition(string);
	void save();
	void load();


	//GameWeekPoints ranking function
	void gwPointsRanking();

	//TotalPoints ranking function
	void totalPointsRanking();

	//delete account 
	void deleteAccount(int accountId);
	

	void changePassword(int playerID, string newPassword);

	void rating(double playerRate);
	
	void removeFootballer(int footballerId);

	void changeTeam(int footballerId, int teamId);

	void RemoveFootballTeam(int teamId);

	void addedFootballer(string newFootballerName, int newFootballerPrice, string newFootballerPosition, int newFootballerTeam);

	void addFootballTeam(string, string);

	void makeMatchesList();
	void updatePlayerPoints();
	void updateLeagueStandings();
	int getAveragePlayerPoints();
	Player* getHighestPlayer();
	void progressGameweek();
};

