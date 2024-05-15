#include "pch.h"

#include <stdio.h> // perror
#include <iostream>
#include "roundrobin.h"

int roundrobin_schedule(vector<string> aTeamNames, vector< vector<STeamPair> >& aSchedule)
{
	if (aTeamNames.size() < 2) { return -1; }
	unsigned teamCount = aTeamNames.size();
	bool isEven = teamCount % 2 == 0;

	string* teamArray = new string[teamCount + 1];
	if (teamArray == NULL) { perror("malloc"); }
	for (unsigned i = 0; i < teamCount; i++)
	{
		teamArray[i] = aTeamNames[i];
	}

	aSchedule.clear();
	// check if numbers of team participating is even or odd
	if (!isEven)
	{
		// if odd add dummy team so the number of teams is even
		string dummy = "0";
		while (1)
		{
			bool dummyNameModified = false;
			for (unsigned i = 0; i < teamCount; i++)
			{
				if (teamArray[i] == dummy) { dummy += "0"; dummyNameModified = true; break; }
			}
			if (!dummyNameModified) { break; }
		}
		teamArray[teamCount] = dummy;
		teamCount++;
	}

	// assign teams to schedule
	for (unsigned i = 0; i < teamCount - 1; i++)
	{
		vector<STeamPair> matchSchedule;
		// shift starts from second iteration
		if (i > 0)
		{
			// -1 means keeping position of last item
			roundrobin_shift_right(teamArray, teamCount - 1);
		}
		roundrobin_assign_weekly_schedule(teamArray, teamCount, matchSchedule);
		aSchedule.push_back(matchSchedule);
	}

	// erase matches including dummy team
	if (!isEven)
	{
		for (unsigned i = 0; i < aSchedule.size(); i++)
		{
			for (unsigned j = 0; j < aSchedule[i].size(); j++)
			{
				if (aSchedule[i][j].iTeam1 == teamArray[teamCount - 1] ||
					aSchedule[i][j].iTeam2 == teamArray[teamCount - 1])
				{
					aSchedule[i].erase(aSchedule[i].begin() + j);
					j--;
				}
			}
		}
	}

	if (teamArray) { delete[] teamArray; teamArray = NULL; }
	return 0;
}

int roundrobin_shift_right(string* aTeamArray, unsigned aSize)
{
	if (aTeamArray == NULL || aSize < 2) { return -1; }
	string temp = aTeamArray[aSize - 1];
	for (unsigned i = aSize - 1; i > 0; i--)
	{
		aTeamArray[i] = aTeamArray[i - 1];
	}
	aTeamArray[0] = temp;
	return 0;
}

int roundrobin_assign_weekly_schedule(string* aTeamArray, unsigned aSize, vector<STeamPair>& aResult)
{
	if (aTeamArray == NULL || aSize < 2) { return -1; }
	aResult.clear();
	for (unsigned i = 0; i < aSize >> 1; i++)
	{
		STeamPair match = { aTeamArray[0 + i], aTeamArray[aSize - 1 - i] };
		aResult.push_back(match);
	}
	return 0;
}

int roundrobin_arrange_home_and_away(vector< vector<STeamPair> >& aSchedule)
{
	if (aSchedule.size() < 2) { return -1; }
	// list of matchdays starts from index-1
	for (unsigned i = 1; i < aSchedule.size(); i++)
	{
		// list of match within certain matchday
		for (unsigned j = 0; j < aSchedule[i].size(); j++)
		{
			unsigned team1AsHome = 0;
			unsigned team2AsHome = 0;
			// list of matchdays run before tested matchday
			for (unsigned k = 0; k < i; k++)
			{
				// list of match within certain matchday
				for (unsigned l = 0; l < aSchedule[k].size(); l++)
				{
					if (aSchedule[k][l].iTeam1 == aSchedule[i][j].iTeam1) { team1AsHome++; }
					if (aSchedule[k][l].iTeam1 == aSchedule[i][j].iTeam2) { team2AsHome++; }
				}
			}

			// if home team has already played more at home, switch
			if (team1AsHome > team2AsHome)
			{
				string temp = aSchedule[i][j].iTeam1.c_str();
				aSchedule[i][j].iTeam1 = aSchedule[i][j].iTeam2;
				aSchedule[i][j].iTeam2 = temp;
			}
		}
	}
	return 0;
}

void roundrobin_swap_home_and_away(vector< vector<STeamPair> >& aSchedule)
{
	for (unsigned i = 0; i < aSchedule.size(); i++)
	{
		for (unsigned j = 0; j < aSchedule[i].size(); j++)
		{
			string temp = aSchedule[i][j].iTeam1.c_str();
			aSchedule[i][j].iTeam1 = aSchedule[i][j].iTeam2;
			aSchedule[i][j].iTeam2 = temp;
		}
	}
}