#include "utils.h"

#include "Game.h"

Game::Game(int utm, string nid) : Window(utm) {
    id = nid;
    mode = MIN;
}

Game::~Game() {
    log("Deleting Game");
}

void Game::_draw() {
    wclear(win);
    
    /*
    Containers
    */
    auto& gd = data["gameData"];
    auto& line = data["liveData"]["linescore"];
    auto& play = data["liveData"]["plays"]["currentPlay"];
    auto& match = play["matchup"];
    
    /*
    Title
    */
    string aname = gd["teams"]["away"]["name"];
    string hname = gd["teams"]["home"]["name"];
    string inh = formatHalf(line["inningHalf"]);
    string ord = line["currentInningOrdinal"];
    
    string titleT = inh + " " + ord + " " + aname + " @ " + hname;
    string tPad (w - titleT.length(), ' ');
    string title = titleT + tPad;
    wattron(win, WA_STANDOUT);
    mvwaddnstr(win, 0, 0, title.c_str(), w);
    wattroff(win, WA_STANDOUT);
    
    
    /*
    Linescore rows
    */
    string r1 = "  [ ]  ";
    string r2 = "[ ] [ ]";
    
    auto& inns = line["innings"];
    for (size_t i = 0; i < max(9, (int)inns.size()); i++) {
        string ar = "-";
        string hr = "-";
        
        if (i < inns.size()) {
            auto& inn = inns[i];
        
            ar = to_string(inn["away"]["runs"]);
            hr = to_string(inn["home"]["runs"]);
        
            if (ar == "null") ar = "0";
            if (hr == "null") hr = "0";
        }
        
        r1 += lpad(2, ar);
        r2 += lpad(2, hr);
    }
    
    /*
    Totals
    */
    string ar = to_string(line["teams"]["away"]["runs"]);
    string ah = to_string(line["teams"]["away"]["hits"]);
    string ae = to_string(line["teams"]["away"]["errors"]);
    
    string hr = to_string(line["teams"]["home"]["runs"]);
    string hh = to_string(line["teams"]["home"]["hits"]);
    string he = to_string(line["teams"]["home"]["errors"]);
    
    r1 += " |";
    r1 += lpad(2, ar) + lpad(2, ah) + lpad(2, ae);
    
    r2 += " |";
    r2 += lpad(2, hr) + lpad(2, hh) + lpad(2, he);
    
        
    /*
    Pitcher v Batter
    */    
    string pitr = match["pitcher"]["fullName"];
    string pith = match["pitchHand"]["code"];
    
    string batr = match["batter"]["fullName"];
    string bats = match["batSide"]["code"];
    
    if (inh == "Top") {
        r1 += " " + bats + "HP " + batr;
        r2 += " " + pith + " " + pitr;
    }
    else {
        r2 += " " + bats + " " + batr; 
        r1 += " " + pith + "HP " + pitr;
    }
    
    
    
    /*
    BSO
    */
    string bals = to_string(line["balls"]);
    string strk = to_string(line["strikes"]);
    string outs = to_string(line["outs"]);
    
    /*
    Row 3
    */
    string r3 = bals + "-" + strk + " " + outs + " ";
    
    /*
    Pitch
    */
    string pits = "";
    string pitn = "";
    string pit_re = "";
    if (play["playEvents"].size() > 0) {
        auto& ev = play["playEvents"][play["playEvents"].size() - 1];
        pits = to_string(ev["pitchData"]["endSpeed"]);
        pitn = ev["details"]["type"]["description"];
        pit_re = ev["details"]["call"]["description"];
    }
    
    r3 += pits + "mph " + pitn + " > ";
    
    /*
    Result
    */
    string res = play["result"]["event"];
    r3 += res + " > " + pit_re;
    
    mvwaddnstr(win, 1, 0, r1.c_str(), w);
    mvwaddnstr(win, 2, 0, r2.c_str(), w);
    mvwaddnstr(win, 3, 0, r3.c_str(), w);
    
    wrefresh(win);
}

void Game::_update() {
    log("Fetching Game");
    
    cpr::Url url = "https://statsapi.mlb.com/api/v1.1/game/" + id + "/feed/live";
    cpr::Response resp = cpr::Get(url);
    loga("Game", id, "Status", to_string(resp.status_code));
    //log(resp.text);
    data = Json::parse(resp.text);
    
    for(auto& item : data["liveData"].items()) {
        loga(item.key());
    }
    
    loga(data["liveData"]["linescore"].dump());
    
    if (mode == MIN) {
        h = 4;
    }
    setH(h);
}