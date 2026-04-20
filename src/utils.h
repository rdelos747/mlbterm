#ifndef UTILS_H
#define UTILS_H

#include <map>
#include <string>
#include <vector>

using namespace std;

struct TeamD {
    string abv;
    string col;
};

inline map<string, TeamD> TEAM_DATA = {
    {"Arizona Dimondbacks", {"ARI", ""}},
    {"Dimondbacks", {"ARI", ""}},
    {"D-backs", {"ARI", ""}},
    
    {"Atlanta Braves", {"ATL", ""}},
    {"Braves", {"ATL", ""}},
    
    {"Athletics", {"ATH", ""}},
    
    {"Baltamore Orioles", {"BAL", ""}},
    {"Orioles", {"BAL", ""}},
    
    
    {"Boston Red Sox", {"BOS", ""}},
    {"Red Sox", {"BOS", ""}},
    
    {"Chicago Cubs", {"CHC", ""}},
    {"Cubs", {"CHC", ""}},
    
    {"Chicago White Sox", {"CWS", ""}},
    {"White Sox", {"CWS", ""}},
    
    {"Cincinnati Reds", {"CIN", ""}},
    {"Reds", {"CIN", ""}},
    
    {"Cleveland Guardians", {"CLE", ""}},
    {"Guardians", {"CLE", ""}},
    
    {"Colorado Rockies", {"COL", ""}},
    {"Rockies", {"COL", ""}},
    
    {"Detroit Tigers", {"DET", ""}},
    {"Tigers", {"DET", ""}},
    
    {"Houston Astros", {"HOU", ""}},
    {"Astros", {"HOU", ""}},
    
    {"Kansas City Royals", {"KC ", ""}},
    {"Royals", {"KC ", ""}},
    
    {"Los Angeles Angels", {"LAA", ""}},
    {"Angels", {"LAA", ""}},
    
    {"Los Angeles Dodgers", {"LAD", ""}},
    {"Dodgers", {"LAD", ""}},
    
    {"Miami Marlins", {"MIA", ""}},
    {"Marlins", {"MIA", ""}},
        
    {"Milwaukee Brewers", {"MIL", ""}},
    {"Brewers", {"MIL", ""}},
    
    {"Minnesota Twins", {"MIN", ""}},
    {"Twins", {"MIN", ""}},
    
    {"New York Mets", {"NYM", ""}},
    {"Mets", {"NYM", ""}},
    
    {"New York Yankees", {"NYY", ""}},
    {"Yankees", {"NYY", ""}},
    
    {"Philadelphia Phillies", {"PHI", ""}},
    {"Phillies", {"PHI", ""}},
    
    {"Pittsburgh Pirates", {"PIT", ""}},
    {"Pirates", {"PIT", ""}},
    
    {"San Diego Padres", {"SD ", ""}},
    {"Padres", {"SD ", ""}},
    
    {"San Fransisco Giants", {"SF ", ""}},
    {"Giants", {"SF ", ""}},

    {"Seattle Mariners", {"SEA", ""}},
    {"Mariners", {"SEA", ""}},

    {"St. Louis Cardinals", {"STL", ""}},
    {"Cardinals", {"STL", ""}},

    {"Tampa Bay Rays", {"TB ", ""}},
    {"Rays", {"TB ", ""}},

    {"Texas Rangers", {"TX ", ""}},
    {"Rangers", {"TX", ""}},

        
    {"Toronto Blue Jays", {"TOR", ""}},
    {"Blue Jays", {"TOR", ""}},

    {"Washington Nationals", {"WSH", ""}},
    {"Nationals", {"WSH", ""}}
};

string divName(int dID);
string divAbv(int dID);
string teamAbv(string name);
string dateToTime(string date, int tz = -4);
string lpad(int n, string s);
string rpad(int n, string s);
vector<string> split(string input, char delim);
string formatHalf(string h);

#endif