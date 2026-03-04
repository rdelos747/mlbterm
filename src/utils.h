#ifndef UTILS_H
#define UTILS_H

#include <map>
#include <string>

using namespace std;

struct TeamD {
    string abv;
    string col;
};

inline map<string, TeamD> TEAM_DATA = {
    {"Arizona Dimondbacks", {"ARI", ""}},
    {"Dimondbacks", {"ARI", ""}},
    {"Atlanta Braves", {"ATL", ""}},
    {"Braves", {"ATL", ""}}
};

string divName(int dID);
string divAbv(int dID);
string teamAbv(string name);
string lpad(int n, string s);
string rpad(int n, string s);

#endif