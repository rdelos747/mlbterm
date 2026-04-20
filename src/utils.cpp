#include <sstream>

#include "log.h"

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

string dateToTime(string date, int tz) {
    string t = split(date, 'T')[1];
    
    vector<string> sp = split(t, ':');
    int hour = (stoi(sp[0]) + tz);
    if (hour < 0) {
        hour = 24 + hour;
    }
    
    string minute = to_string(stoi(sp[1]));
    if (minute.length() < 2) {
        minute = "0" + minute;
    }
    
    return to_string(hour) + ":" + minute;
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

vector<string> split(string input, char delim) {
    vector<string> out;
    string line;
    stringstream stream(input);
    while(getline(stream, line, delim)) {
        out.push_back(line);
    }
    return out;
}

string formatHalf(string h) {
    if (h == "Bottom") return "Bot";
    return h;
}