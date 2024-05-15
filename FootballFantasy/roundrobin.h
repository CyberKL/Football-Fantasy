#ifndef __ROUNDROBIN_H__
#define __ROUNDROBIN_H__

#include <string>
#include <vector>

using namespace std;

typedef struct
{
	string iTeam1, iTeam2;
} STeamPair;

extern int roundrobin_schedule(vector<string> aTeamNames, vector< vector<STeamPair> >& aSchedule);
static int roundrobin_shift_right(string* aTeamArray, unsigned aSize);
static int roundrobin_assign_weekly_schedule(string* aTeamArray, unsigned aSize, vector<STeamPair>& aResult);
extern int roundrobin_arrange_home_and_away(vector< vector<STeamPair> >& aSchedule);
extern void roundrobin_swap_home_and_away(vector< vector<STeamPair> >& aSchedule);

#endif // __ROUNDROBIN_H__