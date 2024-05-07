#include "pch.h"
#include "Presenter.h"
#include <sstream>
#include <iomanip>

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


bool Presenter::getSquadEdited()
{
    return squadEdited;
}


void Presenter::setPressedFootballerControlId(int pressedFootballerControlId)
{
    this->pressedFootballerControlId = pressedFootballerControlId;
}

void Presenter::setTempSquad(unordered_map<int, bool> tempSquad)
{
    this->tempSquad = tempSquad;
}

void Presenter::setSquadEdited(bool squadEdited)
{
    this->squadEdited = squadEdited;
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

void Presenter::confirmChangesInPickTeam()
{
    unordered_map<int, pair<Footballer*, bool>> squad;
    unordered_map<int, bool>::iterator it;

    for (it = tempSquad.begin(); it != tempSquad.end(); it++)
        squad[it->first] = make_pair(Manager::getInstance()->getFootballers()[it->first], it->second);

    loggedInPlayer->getTeam()->setSquad(squad);
    squadEdited = false;
}

void Presenter::loadData()
{
    Manager::getInstance()->load();
}