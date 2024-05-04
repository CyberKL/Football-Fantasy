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

string Presenter::getLoggedInPlayerBudget()
{
    int budget = loggedInPlayer->getTeam()->getBudget();
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

void Presenter::createPlayerTeam(unordered_set<int> footballersIds)
{
    for (const auto& id : footballersIds)
    {
        Footballer* footballer = Manager::getInstance()->getFootballers()[id];
    }
}

vector<Footballer> Presenter::searchFootballersByPosition(string position)
{
    return Manager::getInstance()->searchFootballersByPosition(position);
}

vector<struct UiFootballer> Presenter::loadPickTeamPage()
{
    unordered_map<int, pair<Footballer*, bool>> squad = loggedInPlayer->getTeam()->getSquad();
    unordered_map<int, pair<Footballer*, bool>>::iterator it;
    vector<struct UiFootballer> footballers;
    for (it = squad.begin(); it != squad.end(); it++)
    {
        struct UiFootballer uiFootballer;
        Footballer footballer = *it->second.first;
        uiFootballer.name = footballer.getName();
        uiFootballer.isStarting = it->second.second;
        uiFootballer.position = footballer.getPosition();
        FootballTeam* footballerTeam = footballer.getTeam();
        Match nextMatch = Manager::getInstance()->findNextMatch(footballerTeam);
        nextMatch.getHomeTeam() == footballerTeam ? uiFootballer.info = nextMatch.getAwayTeam()->getName() : uiFootballer.info = nextMatch.getHomeTeam()->getName();
        footballers.push_back(uiFootballer);
    }
    return footballers;
}

void Presenter::loadData()
{
    Manager::getInstance()->load();
}