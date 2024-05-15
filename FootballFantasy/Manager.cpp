#include "pch.h"
#include "Manager.h"
#include <string>
#include "roundrobin.h"

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
unordered_map<int, Player*> Manager::getPlayers()
{
	return players;
}

map<string, League*> Manager::getLeagues()
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

map<int, unordered_map<int, Match*>> Manager::getMatches()
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

unordered_map<int, map<int, vector<string>>> Manager::getGwOrderedPlayers()
{
	return gwOrderedPlayers;
}

map<int, vector<string>> Manager::getOrderedPlayers()
{
	return orderedPlayers;
}

bool Manager::getSeasonStarted()
{
	return seasonStarted;
}


// Setters
void Manager::setPlayers(const unordered_map<int, Player*>& players)
{
	this->players = players;
}

void Manager::setLeagues(const map<string, League*>& leagues) {
	this->leagues = leagues;
}

void Manager::setFootballers(const unordered_map<int, Footballer*>& footballers) {
	this->footballers = footballers;
}

void Manager::setFootballTeams(const unordered_map<int, FootballTeam*>& footballTeams) {
	this->footballTeams = footballTeams;
}

void Manager::setMatches(const map<int, unordered_map<int, Match*>>& matches) {
	this->matches = matches;
}

void Manager::setSeasonStarted(bool seasonStarted)
{
	this->seasonStarted = seasonStarted;
}

// Sign up process
bool Manager::isUsernameDuplicate(const string& username)
{
	unordered_map<int, Player*>::iterator it;
	for (it = players.begin(); it != players.end(); it++)
		if (it->second->getUsername() == username)
			return true; // Duplicate username
	return false;
}

void Manager::addPlayer(const string& username, const string& password)
{
	Player* newPlayer = new Player(username, password);
	players[newPlayer->getId()] = newPlayer;
}


// Login
Player* Manager::login(const string& username, const string& password)
{
	unordered_map<int, Player*>::iterator it;
	for (it = players.begin(); it != players.end(); it++)
		if (it->second->getUsername() == username && it->second->getPassword() == password)
			return it->second; // player found
	return nullptr; // player not found or invalid credentials
}


Match Manager::findNextMatch(const FootballTeam* team)
{
	unordered_map<int, Match*> currentGwMatches = matches[currentGw + 1];
	unordered_map<int, Match*>::iterator it;
	for (it = currentGwMatches.begin(); it != currentGwMatches.end(); it++)
	{
		if (it->second->getHomeTeam() == team || it->second->getAwayTeam() == team)
		{
			return *it->second;
		}
	}
}

vector<Footballer> Manager::searchFootballersByPosition(string position)
{
	vector<Footballer> matchedFootballers;
	unordered_map<int, Footballer*>::iterator it;
	for (it = footballers.begin(); it != footballers.end(); it++)
		if(it->second->getPosition() == position) 
			matchedFootballers.push_back(*it->second);

	return matchedFootballers;
}


void Manager::save()
{
	// Saving to the json files

	// Saving football teams
	json jsonFootballTeamsUpdated = json::array();
	for (const auto& pair : footballTeams) {
		jsonFootballTeamsUpdated.push_back(pair.second->toJson());
	}
	ofstream footballTeamsFileOut("D:\\Uni\\Year 2\\2nd Semester\\Data Structure\\ProjectFinal\\FootballFantasy\\FootballFantasy\\Assets\\FootballTeams.json");
	footballTeamsFileOut << jsonFootballTeamsUpdated.dump(4);
	footballTeamsFileOut.close();

	// Saving footballers
	json jsonFootballersUpdated = json::array();
	for (const auto& pair : footballers) {
		jsonFootballersUpdated.push_back(pair.second->toJson());
	}

	ofstream footballersFileOut("D:\\Uni\\Year 2\\2nd Semester\\Data Structure\\ProjectFinal\\FootballFantasy\\FootballFantasy\\Assets\\Footballers.json");
	footballersFileOut << jsonFootballersUpdated.dump(4);
	footballersFileOut.close();

	// Saving matches
	json jsonMatchesUpdated = json::array();
	for (const auto& gwMatches : matches) {
		for (const auto& pair : gwMatches.second) {
			jsonMatchesUpdated.push_back(pair.second->toJson());
		}
	}

	ofstream matchesFileOut("D:\\Uni\\Year 2\\2nd Semester\\Data Structure\\ProjectFinal\\FootballFantasy\\FootballFantasy\\Assets\\Matches.json");
	matchesFileOut << jsonMatchesUpdated.dump(4);
	matchesFileOut.close();

	// Saving players
	json jsonPlayersUpdated = json::array();
	for (const auto& pair : players) {
		jsonPlayersUpdated.push_back(pair.second->toJson());
	}

	ofstream playersFileOut("D:\\Uni\\Year 2\\2nd Semester\\Data Structure\\ProjectFinal\\FootballFantasy\\FootballFantasy\\Assets\\Players.json");
	playersFileOut << jsonPlayersUpdated.dump(4);
	playersFileOut.close();


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

	// Save values back to file
	std::ofstream outfile("state.txt");

	outfile << "currentGw:" << currentGw << std::endl;
	outfile << "seasonStarted:" << (seasonStarted ? "true" : "false") << std::endl;

	outfile.close();
}

void Manager::load()
{
	// Loading from the json files

	// Loading football teams
	ifstream footballTeamsFile("D:\\Uni\\Year 2\\2nd Semester\\Data Structure\\ProjectFinal\\FootballFantasy\\FootballFantasy\\Assets\\FootballTeams.json");
	json jsonFootballTeams;
	footballTeamsFile >> jsonFootballTeams;
	for (json j : jsonFootballTeams) 
	{
		FootballTeam* footballTeam = new FootballTeam();
		footballTeam->fromJson(j);
		footballTeams[footballTeam->getId()] = footballTeam;
	}

	// loading footballers
	ifstream footballersFile("D:\\Uni\\Year 2\\2nd Semester\\Data Structure\\ProjectFinal\\FootballFantasy\\FootballFantasy\\Assets\\Footballers.json");
	json jsonFootballers;
	footballersFile >> jsonFootballers;
	for (json j : jsonFootballers)
	{
		Footballer* footballer =  new Footballer();
		footballer->fromJson(j);
		footballers[footballer->getId()] = footballer;
	}


	// loading matches
	ifstream matchesFile("D:\\Uni\\Year 2\\2nd Semester\\Data Structure\\ProjectFinal\\FootballFantasy\\FootballFantasy\\Assets\\Matches.json");
	json jsonMatches;
	matchesFile >> jsonMatches;
	for (json j : jsonMatches)
	{
		Match* match = new Match();
		match->fromJson(j);
		matches[match->getGw()][match->getId()] = match;
	}

	// loading players
	ifstream playersFile("D:\\Uni\\Year 2\\2nd Semester\\Data Structure\\ProjectFinal\\FootballFantasy\\FootballFantasy\\Assets\\Players.json");
	json jsonPlayers;
	playersFile >> jsonPlayers;
	for (json j : jsonPlayers)
	{
		Player* player = new Player();
		player->fromJson(j);
		players[player->getId()] = player;
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

	std::ifstream file("state.txt");
	std::string temp;

	while (file >> temp) {
		if (temp == "currentGw:") {
			file >> currentGw;
		}
		else if (temp == "seasonStarted:") {
			std::string status;
			file >> status;
			seasonStarted = (status == "true");
		}
	}

	file.close();


	League* prem = new League("Premier League");
	League* laLiga = new League("La Liga");
	League* seriaA = new League("Seria A");
	leagues.insert(make_pair(prem->getName(), prem));
	leagues.insert(make_pair(laLiga->getName(), laLiga));
	leagues.insert(make_pair(seriaA->getName(), seriaA));
}

//GameWeekPoints ranking function
void Manager::gwPointsRanking()
{
	unordered_map<int, Player*>::iterator it;
	for (it = players.begin(); it != players.end(); it++)
		gwOrderedPlayers[currentGw][it->second->getTeam()->getPoints()[currentGw]].push_back(it->second->getUsername());
}

//TotalPoints ranking function
void Manager::totalPointsRanking()
{
	orderedPlayers.clear();
	unordered_map<int, Player*>::iterator it;
	for (it = players.begin(); it != players.end(); it++)
		orderedPlayers[it->second->getTotalPoints()].push_back(it->second->getUsername());
}

void Manager::deleteAccount(int accountId)
{
	players.erase(accountId);
}

void Manager:: changePassword(int playerID, string newPassword)
{
	players[playerID]->setPassword(newPassword);
}

void Manager::rating(double playerRate)
{
	totalRate += playerRate;
	rate = totalRate / players.size();
}

void Manager::removeFootballer(int footballerId)
{
	footballers.erase(footballerId);
}

void Manager::RemoveFootballTeam(int teamId)
{
	footballTeams.erase(teamId);
}

void Manager::addedFootballer(string newFootballerName, int newFootballerPrice, string newFootballerPosition, int newFootballerTeam)
{
	FootballTeam* team = footballTeams[newFootballerTeam];
	Footballer* newfootballer = new Footballer(newFootballerName,  newFootballerPosition,  newFootballerPrice, team->getLeague(), team);
	footballers.insert(make_pair(newfootballer->getId(), newfootballer));
}

void Manager:: changeTeam(int footballerId, int teamId)
{
	footballers[footballerId]->setTeam(footballTeams[teamId]);
	footballers[footballerId]->setLeagueName(footballTeams[teamId]->getLeague());
}


void Manager::addFootballTeam(string name, string league)
{
	FootballTeam* footballTeam = new FootballTeam(name, league);
	footballTeams.insert(make_pair(footballTeam->getId(), footballTeam));
}


void Manager::makeMatchesList()
{
	map<string, League*>::iterator leagueIt;
	for (leagueIt = leagues.begin(); leagueIt != leagues.end(); leagueIt++)
	{
		unordered_map<int, FootballTeam*>::iterator it;
		vector<string> teams;
		for (it = footballTeams.begin(); it != footballTeams.end(); it++)
			if (it->second->getLeague() == leagueIt->first) teams.push_back(to_string(it->second->getId()));

		vector< vector<STeamPair> > schedule;

		roundrobin_schedule(teams, schedule);
		roundrobin_arrange_home_and_away(schedule);

		int gameweekCounter = 0;
		// leg-1
		for (unsigned i = 0; i < schedule.size(); i++)
		{
			unordered_map<int, Match*> gameweekMatches;
			for (unsigned j = 0; j < schedule[i].size(); j++)
			{
				FootballTeam* homeTeam = footballTeams[stoi(schedule[i][j].iTeam1)];
				FootballTeam* awayTeam = footballTeams[stoi(schedule[i][j].iTeam2)];
				Match* match = new Match(homeTeam, awayTeam, gameweekCounter, leagueIt->first);
				matches[gameweekCounter].insert(make_pair(match->getId(), match));
			}
			gameweekCounter++;
		}

		// leg-2
		roundrobin_swap_home_and_away(schedule);
		for (unsigned i = 0; i < schedule.size(); i++)
		{
			unordered_map<int, Match*> gameweekMatches;
			for (unsigned j = 0; j < schedule[i].size(); j++)
			{
				FootballTeam* homeTeam = footballTeams[stoi(schedule[i][j].iTeam1)];
				FootballTeam* awayTeam = footballTeams[stoi(schedule[i][j].iTeam2)];
				Match* match = new Match(homeTeam, awayTeam, gameweekCounter, leagueIt->first);
				matches[gameweekCounter].insert(make_pair(match->getId(), match));
			}
			gameweekCounter;
		}
	}

	
}

void Manager::updatePlayerPoints()
{
	unordered_map<int, Player*>::iterator it;
	for (it = players.begin(); it != players.end(); it++)
		it->second->getTeam()->updatePoints(currentGw);
}

void Manager::updateLeagueStandings()
{
	map<string, League*>::iterator it;
	for (it = leagues.begin(); it != leagues.end(); it++)
		it->second->updateStandingsPoints();
}

int Manager::getAveragePlayerPoints()
{
	unordered_map<int, Player*>::iterator it;
	int sum = 0;
	for (it = players.begin(); it != players.end(); it++)
		sum += it->second->getTeam()->getPoints()[currentGw];

	if (players.size() > 0)
		return sum / players.size();
	else
		return 0;
}

Player* Manager::getHighestPlayer()
{
	string name = gwOrderedPlayers[currentGw][0][0];
	unordered_map<int, Player*>::iterator it;
	for (it = players.begin(); it != players.end(); it++)
		if (it->second->getUsername() == name) return it->second;
	return nullptr;
}

void Manager::progressGameweek()
{
	currentGw++;
}