#include "pch.h"
#include "Manager.h"

// Ensuring that only one instance is created and creating a new one if not
Manager* Manager::instance = nullptr;

Manager::Manager() {}

Manager::~Manager() {}

Manager* Manager::getInstance()
{
	if (!instance)
	{
		instance = new Manager();
	}
	return instance;
}


// Getters
unordered_map<int, Player> Manager::getPlayers()
{
	return players;
}

map<string, League> Manager::getLeagues()
{
	return leagues;
}

unordered_map<int, Footballer*> Manager::getFootballers()
{
	return footballers;
}

unordered_map<int, FootballTeam*> Manager::getFootballTeams()
{
	return footballTeams;
}

map<int, unordered_map<int, Match>> Manager::getMatches()
{
	return matches;
}

map<string, int> Manager::getCounts()
{
	return counts;
}

int Manager::getCurrentGw()
{
	return currentGw;
}

// Setters
void Manager::setPlayers(const unordered_map<int, Player>& players)
{
	this->players = players;
}

void Manager::setLeagues(const map<string, League>& leagues) {
	this->leagues = leagues;
}

void Manager::setFootballers(const unordered_map<int, Footballer*>& footballers) {
	this->footballers = footballers;
}

void Manager::setFootballTeams(const unordered_map<int, FootballTeam*>& footballTeams) {
	this->footballTeams = footballTeams;
}

void Manager::setMatches(const map<int, unordered_map<int, Match>>& matches) {
	this->matches = matches;
}


// Sign up process
bool Manager::isUsernameDuplicate(const string& username)
{
	unordered_map<int, Player>::iterator it;
	for (it = players.begin(); it != players.end(); it++)
		if (it->second.getUsername() == username)
			return true; // Duplicate username
	return false;
}

void Manager::addPlayer(const string& username, const string& password)
{
	Player newPlayer(username, password);
	players[newPlayer.getId()] = newPlayer;
}


// Login
Player* Manager::login(const string& username, const string& password)
{
	unordered_map<int, Player>::iterator it;
	for (it = players.begin(); it != players.end(); it++)
		if (it->second.getUsername() == username && it->second.getPassword() == password)
			return &it->second; // player found
	return nullptr; // player not found or invalid credentials
}


Match Manager::findNextMatch(const FootballTeam* team)
{
	unordered_map<int, Match> currentGwMatches = matches[currentGw + 1];
	unordered_map<int, Match>::iterator it;
	for (it = currentGwMatches.begin(); it != currentGwMatches.end(); it++)
	{
		if (it->second.getHomeTeam() == team || it->second.getAwayTeam() == team)
		{
			return it->second;
		}
	}
}

vector<Footballer> Manager::searchFootballersByPosition(string position)
{
	vector<Footballer> matchedFootballers;
	unordered_map<int, Footballer*>::iterator it;
	for (it = footballers.begin(); it != footballers.end(); it++)
		it->second->getPosition() == position ? matchedFootballers.push_back(*it->second) : 0;
	return matchedFootballers;
}


void Manager::save()
{
	// Saving to the json files

	// Saving the counts to the counts file
	counts["Player"] = Player::getCount();
	counts["Footballer"] = Footballer::getCount();
	counts["FootballTeam"] = FootballTeam::getCount();
	counts["Match"] = Match::getCount();

	map<string, int>::iterator it;
	ofstream countsFile("counts.txt", ios::trunc);
	for (it = counts.begin(); it != counts.end(); it++)
		countsFile << it->first << ":" << it->second << endl;
	countsFile.close();
}

void Manager::load()
{
	// Loading from the json files

	// Loading football teams
	ifstream footballTeamsFile("C:\\Users\\marya\\OneDrive\\Desktop\\cs\\year 2\\2nd semester\\Data Structures\\ProjectFinal\\Football-Fantasy\\FootballFantasy\\Assets\\FootballTeams.json");
	json jsonFootballTeams;
	footballTeamsFile >> jsonFootballTeams;
	for (json j : jsonFootballTeams) 
	{
		FootballTeam* footballTeam = new FootballTeam();
		footballTeam->fromJson(j);
		footballTeams[footballTeam->getId()] = footballTeam;
	}

	// loading footballers
	ifstream footballersFile("C:\\Users\\marya\\OneDrive\\Desktop\\cs\\year 2\\2nd semester\\Data Structures\\ProjectFinal\\Football-Fantasy\\FootballFantasy\\Assets\\Footballers.json");
	json jsonFootballers;
	footballersFile >> jsonFootballers;
	for (json j : jsonFootballers)
	{
		Footballer* footballer =  new Footballer();
		footballer->fromJson(j);
		footballers[footballer->getId()] = footballer;
	}


	// loading matches
	ifstream matchesFile("C:\\Users\\marya\\OneDrive\\Desktop\\cs\\year 2\\2nd semester\\Data Structures\\ProjectFinal\\Football-Fantasy\\FootballFantasy\\Assets\\Matches.json");
	json jsonMatches;
	matchesFile >> jsonMatches;
	for (json j : jsonMatches)
	{
		Match match;
		match.fromJson(j);
		matches[match.getGw()][match.getId()] = match;
	}

	// loading players
	ifstream playersFile("C:\\Users\\marya\\OneDrive\\Desktop\\cs\\year 2\\2nd semester\\Data Structures\\ProjectFinal\\Football-Fantasy\\FootballFantasy\\Assets\\Players.json");
	json jsonPlayers;
	playersFile >> jsonPlayers;
	for (json j : jsonPlayers)
	{
		Player player;
		player.fromJson(j);
		players[player.getId()] = player;
	}


	// Loading counts from the counts file
	ifstream countsFile("counts.txt");
	string line, className;
	int count;

	while (getline(countsFile, line))
	{
		int delim = line.find(':');
		className = line.substr(0, delim);
		count = stoi(line.substr(delim));
		counts[className] = count;
	}
	countsFile.close();


}

//GameWeekPoints ranking function
void Manager::gwPointsRanking()
{
	map<int,  vector<string>> orderedPlayers;
	unordered_map<int, Player>::iterator it;
	for (it = players.begin(); it != players.end(); it++)
	{
		orderedPlayers[it->second.getTeam()->getPoints()[currentGw]].push_back(it->second.getUsername());
	}
}

//TotalPoints ranking function
void Manager::totalPointsRanking()
{
	map<int, vector<string>> orderedPlayers;
	unordered_map<int, Player>::iterator it;
	for (it = players.begin(); it != players.end(); it++)
	{
		orderedPlayers[it->second.getTotalPoints()].push_back(it->second.getUsername());
	}
}

void Manager::deleteAccount(int accountId)
{
	players.erase(accountId);
}

void Manager:: changePassword(int playerID, string newPassword)
{
	players[playerID].setPassword(newPassword);
}


void Manager::Rating(int playerRate)
{
	totalRate = +playerRate;
	Rate = totalRate / players.size();
}