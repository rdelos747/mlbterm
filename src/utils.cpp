#include "utils.h"

string divName(int id) {
    if (id == 200) return "American League West";
    if (id == 201) return "American League East";
    if (id == 202) return "American League Central";
    if (id == 203) return "National League West";
    if (id == 204) return "National League East";
    if (id == 205) return "National League Central";
    return "NO LEAGUE FOUND";
}

string divAbv(int id) {
    if (id == 200) return "ALW";
    if (id == 201) return "ALE";
    if (id == 202) return "ALC";
    if (id == 203) return "NLW";
    if (id == 204) return "NLE";
    if (id == 205) return "NLC";
    return "???";
}

string teamAbv(string name) {
    if (TEAM_DATA.count(name) > 0) {
        return TEAM_DATA[name].abv;
    }
    
    return "???";
}

string lpad(int n, string s) {
    if (s.length() < n) {
        string p (n - s.length(), ' ');
        return p + s;
    }
    return s;
}

string rpad(int n, string s) {
     if (s.length() < n) {
        string p (n - s.length(), ' ');
        return s + p;
    }
    return s;
}