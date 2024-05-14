#include "pch.h"
#include "Presenter.h"
#include <sstream>
#include <iomanip>
#include <random>

// Ensuring that only one instance is created and creating a new one if not
Presenter* Presenter::instance = nullptr;

Presenter::Presenter()
    : loggedInPlayer(nullptr) {}

Presenter* Presenter::getInstance()
{
    if (!instance)
    {
        instance = new Presenter();
    }
    return instance;
}


int Presenter::getPressedFootballerControlId()
{
    return pressedFootballerControlId;
}


int Presenter::getTempCaptainId()
{
    return tempCaptainId;
}


int Presenter::getTempViceCaptainId()
{
    return tempViceCaptainId;
}


bool Presenter::getSquadEdited()
{
    return squadEdited;
}


bool Presenter::getCaptaincyEdited()
{
    return captaincyEdited;
}

Match Presenter::getPressedMatch()
{
    return pressedMatch;
}

bool Presenter::getSeasonStarted()
{
    return Manager::getInstance()->getSeasonStarted();
}


void Presenter::setPressedFootballerControlId(int pressedFootballerControlId)
{
    this->pressedFootballerControlId = pressedFootballerControlId;
}

void Presenter::setTempSquad(unordered_map<int, bool> tempSquad)
{
    this->tempSquad = tempSquad;
}


void Presenter::setTempCaptainId(int id)
{
    tempCaptainId = id;
}


void Presenter::setTempViceCaptainId(int id)
{
    tempViceCaptainId = id;
}


void Presenter::setSquadEdited(bool squadEdited)
{
    this->squadEdited = squadEdited;
}


void Presenter::setCaptaincyEdited(bool captaincyEdited)
{
    this->captaincyEdited = captaincyEdited;
}

void Presenter::setPressedMatch(Match pressedMatch)
{
    this->pressedMatch = pressedMatch;
}

void Presenter::setSeasonStarted(bool seasonStarted)
{
    Manager::getInstance()->setSeasonStarted(seasonStarted);
}

bool Presenter::isUsernameDuplicate(const string& username)
{
    // Check for duplicate username
    return Manager::getInstance()->isUsernameDuplicate(username);
}

void Presenter::signUp(const string& username, const string& password)
{
    // Add the new player to the list of players (unordered_map)
    Manager::getInstance()->addPlayer(username, password);
}

bool Presenter::login(const string& username, const string& password)
{
    loggedInPlayer = Manager::getInstance()->login(username, password);
    if (loggedInPlayer == nullptr)
        return false;
    else
        return true;

}

string Presenter::budgetToString(int budget)
{
    ostringstream oss;
    oss << fixed << setprecision(1) << ((float)budget / 1000);
    string budgetString = oss.str() + 'K';
    return budgetString;
}

PlayerTeam* Presenter::getPlayerTeam()
{
    return loggedInPlayer->getTeam();
}


int Presenter::getLoggedInPlayerBudget()
{
    return loggedInPlayer->getTeam()->getBudget();
}


Footballer Presenter::getFootballer(int id)
{
    return *Manager::getInstance()->getFootballers()[id];
}

string Presenter::getFootballerNextMatch(int id)
{
    string nextMatchTeam;
    Footballer footballer = *Manager::getInstance()->getFootballers()[id];
    Match nextMatch = Manager::getInstance()->findNextMatch(footballer.getTeam());
    nextMatch.getHomeTeam() == footballer.getTeam() ? nextMatchTeam = nextMatch.getAwayTeam()->getName() : nextMatchTeam = nextMatch.getHomeTeam()->getName();
    return nextMatchTeam;
}

void Presenter::createPlayerTeam(unordered_set<int> footballersIds, int budget)
{
    unordered_map<int, pair<Footballer*, bool>>  squad;
    Footballer* captain = nullptr;
    Footballer* viceCaptain = nullptr;
    int gkCount = 0;
    int defCount = 0;
    int midCount = 0;
    int fwdCount = 0;
    for (const auto& id : footballersIds)
    {
        Footballer* footballer = Manager::getInstance()->getFootballers()[id];
        string position = footballer->getPosition();
        if (position == "Goalkeeper")
        {
            if (gkCount >= 1)
                squad.insert(make_pair(footballer->getId(), make_pair(footballer, false)));
            else
            {
                squad.insert(make_pair(footballer->getId(), make_pair(footballer, true)));
                captain = footballer;
                gkCount++;
            }
        }
        else if (position == "Defender")
        {
            if (defCount >= 4)
                squad.insert(make_pair(footballer->getId(), make_pair(footballer, false)));
            else
            {
                squad.insert(make_pair(footballer->getId(), make_pair(footballer, true)));
                defCount == 0 ? viceCaptain = footballer : 0;
                defCount++;
            }
        }
        else if (position == "Midfielder")
        {
            if (midCount >= 3)
                squad.insert(make_pair(footballer->getId(), make_pair(footballer, false)));
            else
            {
                squad.insert(make_pair(footballer->getId(), make_pair(footballer, true)));
                midCount++;
            }
        }
        else if (position == "Forward")
        {
            if (fwdCount >= 3)
                squad.insert(make_pair(footballer->getId(), make_pair(footballer, false)));
            else
            {
                squad.insert(make_pair(footballer->getId(), make_pair(footballer, true)));
                fwdCount++;
            }
        }
    }
    PlayerTeam* team = new PlayerTeam(squad, captain, viceCaptain, budget);
    loggedInPlayer->setTeam(team);
}

vector<Footballer> Presenter::searchFootballersByPosition(string position)
{
    return Manager::getInstance()->searchFootballersByPosition(position);
}

unordered_map<int, struct UiFootballer> Presenter::loadPickTeamPage()
{
    unordered_map<int, pair<Footballer*, bool>> squad = loggedInPlayer->getTeam()->getSquad();
    unordered_map<int, pair<Footballer*, bool>>::iterator it;
    unordered_map<int, struct UiFootballer> footballers;
    for (it = squad.begin(); it != squad.end(); it++)
    {
        struct UiFootballer uiFootballer;
        Footballer footballer = *it->second.first;
        uiFootballer.id = footballer.getId();
        uiFootballer.name = footballer.getName();
        uiFootballer.isStarting = it->second.second;
        uiFootballer.position = footballer.getPosition();
        FootballTeam* footballerTeam = footballer.getTeam();
        Match nextMatch = Manager::getInstance()->findNextMatch(footballerTeam);
        nextMatch.getHomeTeam() == footballerTeam ? uiFootballer.info = nextMatch.getAwayTeam()->getName() : uiFootballer.info = nextMatch.getHomeTeam()->getName();
        footballers[uiFootballer.id] = uiFootballer;
    }
    return footballers;
}


unordered_map<int, struct UiFootballer> Presenter::loadTeamPointsPage()
{
    unordered_map<int, pair<Footballer*, bool>> squad = loggedInPlayer->getTeam()->getSquad();
    unordered_map<int, pair<Footballer*, bool>>::iterator it;
    unordered_map<int, struct UiFootballer> footballers;
    for (it = squad.begin(); it != squad.end(); it++)
    {
        struct UiFootballer uiFootballer;
        Footballer footballer = *it->second.first;
        uiFootballer.id = footballer.getId();
        uiFootballer.name = footballer.getName();
        uiFootballer.isStarting = it->second.second;
        uiFootballer.position = footballer.getPosition();
        uiFootballer.info = to_string(footballer.getGwPoints()[Manager::getInstance()->getCurrentGw()]);
        footballers[uiFootballer.id] = uiFootballer;
    }
    return footballers;
}


unordered_map<int, struct UiFootballer> Presenter::loadTeamTransfersPage()
{
    unordered_map<int, pair<Footballer*, bool>> squad = loggedInPlayer->getTeam()->getSquad();
    unordered_map<int, pair<Footballer*, bool>>::iterator it;
    unordered_map<int, struct UiFootballer> footballers;
    for (it = squad.begin(); it != squad.end(); it++)
    {
        struct UiFootballer uiFootballer;
        Footballer footballer = *it->second.first;
        uiFootballer.id = footballer.getId();
        uiFootballer.name = footballer.getName();
        uiFootballer.isStarting = it->second.second;
        uiFootballer.position = footballer.getPosition();
        uiFootballer.info = to_string(footballer.getPrice());
        footballers[uiFootballer.id] = uiFootballer;
    }
    return footballers;
}


unordered_map<int, struct UiFootballer> Presenter::loadTempSquad()
{
    unordered_map<int, pair<Footballer*, bool>> squad = loggedInPlayer->getTeam()->getSquad();
    unordered_map<int, bool>::iterator it;
    unordered_map<int, struct UiFootballer> footballers;
    for (it = tempSquad.begin(); it != tempSquad.end(); it++)
    {
        Footballer footballer = *squad[it->first].first;
        struct UiFootballer uiFootballer;
        uiFootballer.id = footballer.getId();
        uiFootballer.name = footballer.getName();
        uiFootballer.isStarting = it->second;
        uiFootballer.position = footballer.getPosition();
        FootballTeam* footballerTeam = footballer.getTeam();
        Match nextMatch = Manager::getInstance()->findNextMatch(footballerTeam);
        nextMatch.getHomeTeam() == footballerTeam ? uiFootballer.info = nextMatch.getAwayTeam()->getName() : uiFootballer.info = nextMatch.getHomeTeam()->getName();
        footballers[uiFootballer.id] = uiFootballer;
    }
    return footballers;
}

void Presenter::getCaptainsIds(int& captain, int& viceCaptain)
{
    captain = loggedInPlayer->getTeam()->getCaptain()->getId();
    viceCaptain = loggedInPlayer->getTeam()->getViceCaptain()->getId();
}

void Presenter::confirmChangesInPickTeam()
{

    if (squadEdited)
    {
        unordered_map<int, pair<Footballer*, bool>> squad;
        unordered_map<int, bool>::iterator it;

        for (it = tempSquad.begin(); it != tempSquad.end(); it++)
            squad[it->first] = make_pair(loggedInPlayer->getTeam()->getSquad()[it->first].first, it->second);

        loggedInPlayer->getTeam()->setSquad(squad);
        squadEdited = false;
    }
    
    if (captaincyEdited)
    {
        loggedInPlayer->getTeam()->setCaptain(loggedInPlayer->getTeam()->getSquad()[tempCaptainId].first);
        loggedInPlayer->getTeam()->setViceCaptain(loggedInPlayer->getTeam()->getSquad()[tempViceCaptainId].first);

        captaincyEdited = false;
    }
    
}

void Presenter::confirmTransfersPage(stack<pair<int, int>> transfersStack)
{
    while (!transfersStack.empty())
    {
        int out = transfersStack.top().first;
        int inId = transfersStack.top().second;

        Footballer* in = Manager::getInstance()->getFootballers()[inId];
        loggedInPlayer->getTeam()->transfer(out, in);

        transfersStack.pop();
    }
}

void Presenter::loadData()
{
    Manager::getInstance()->load();
}
string Presenter:: getLoggedInPlayerPassword()
{
    return loggedInPlayer->getPassword();
}

void Presenter::changePassword(string password)
{
    Manager::getInstance()->changePassword(loggedInPlayer->getId(), password);
}

string Presenter::getLoggedInPlayerUsername()
{
    return loggedInPlayer->getUsername();
}

int Presenter::getLoggedInPlayerID()
{
    return loggedInPlayer->getId();
}

void Presenter::deleteAccount(int accountId)
{
    Manager::getInstance()->deleteAccount(accountId);
}


map<int, vector<string>> Presenter::getCurrentGwRankings()
{
    return Manager::getInstance()->getGwOrderedPlayers()[Manager::getInstance()->getCurrentGw()];
}

map<int, vector<string>> Presenter::getTotalRankings()
{
    return Manager::getInstance()->getOrderedPlayers();
}

map<int, unordered_map<int, Match>> Presenter::getMatches()
{
    return Manager::getInstance()->getMatches();
}

int Presenter::getCurrentGw()
{
    return Manager::getInstance()->getCurrentGw();
}

void Presenter::logOut()
{
    loggedInPlayer = nullptr;
}

void Presenter::updateRate(double rate)
{
    Manager::getInstance()->rating(rate);
}

unordered_map<int, Footballer*> Presenter::getFootballersList()
{
    return Manager::getInstance()->getFootballers();
}

void Presenter:: removeFootballer(int footballerId)
{
    Manager::getInstance()->removeFootballer(footballerId);
}

unordered_map<int, FootballTeam*> Presenter::getFootballTeamList()
{
    return Manager::getInstance()->getFootballTeams();
}

void Presenter::removeFootballTeam(int teamId)
{
    Manager::getInstance()->RemoveFootballTeam(teamId);
}

pair<int, string> Presenter::luckyWheelGenerator()
{
    // Generate a random index
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, Presenter::getInstance()->getFootballersList().size() - 1);
    int randomIndex = dist(gen);

    string name = Presenter::getInstance()->getFootballersList()[randomIndex]->getName();

    pair<int, string> generatedFootballer = make_pair(randomIndex, name);
    return generatedFootballer;
}

void Presenter::addedFootballer(string newFootballerName, int newFootballerPrice, string newFootballerPosition, int newFootballerTeam)
{
    Manager::getInstance()->addedFootballer( newFootballerName,  newFootballerPrice,  newFootballerPosition,  newFootballerTeam);
}


unordered_map<int, FootballTeam*> Presenter::getFootballTeams()
{
    return Manager::getInstance()->getFootballTeams();
}

void Presenter::changeTeam(int footballerId, int changedFootballerTeam)
{
   Manager::getInstance()->changeTeam(footballerId, changedFootballerTeam);
}

void Presenter::updateFootballerPoints(int id, int goals, int assists, int penaltiesMissed, int yellowCards, bool redCard, int ownGoals, int penaltiesSaved, int shotsSaved, int timePlayed, int goalsConceded, bool cleanSheet)
{
    Manager::getInstance()->getFootballers()[id]->updatePoints(goals, assists, penaltiesMissed, yellowCards, redCard, ownGoals, penaltiesSaved, shotsSaved, timePlayed, goalsConceded, cleanSheet);
}