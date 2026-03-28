#include "utils.h"

#include "Schedule.h"

Schedule::Schedule(int nw, int utm) {
    w = nw;
    win = newwin(1, w, 0, 0);
    redraw = false;
    upt = 0;
    upt_m = utm;
}

Schedule::~Schedule() {
    log("Deleting Schedule");
    delwin(win);
}

void Schedule::draw() {
    if (!redraw) {
        return;
    }
    redraw = false;
    
    wclear(win);
    
    /*
    Title
    */
    string titleT = "SCHEDULE";
    string tPad (w - titleT.length(), ' ');
    string title = titleT + tPad;
    wattron(win, WA_STANDOUT);
    mvwaddnstr(win, 0, 0, title.c_str(), w);
    wattroff(win, WA_STANDOUT);
    
    if (data["dates"].size() == 0) {
        return;
    }
    
    for (size_t j = 0; j < data["dates"][0]["games"].size(); j++) {
        const auto& g = data["dates"][0]["games"][j];
        
        string stat = g["status"]["codedGameState"];
        string time = dateToTime(g["gameDate"]);
        
        const auto& ta = g["teams"]["away"];
        const auto& th = g["teams"]["home"];
        
        string aName = ta["team"]["name"];
        string aScr = to_string(ta["score"]);
        string hName = th["team"]["name"];
        string hScr = to_string(th["score"]);
        
        string row =    rpad(6, time)+
                        rpad(2, stat) +
                        lpad(21, aName) +
                        lpad(3, aScr) + 
                        " @ " +
                        rpad(3, hScr) + 
                        hName;
        
        mvwaddnstr(
            win,
            j + 1,
            0,
            row.c_str(),
            w
        );
    }
    
    wrefresh(win);
}

void Schedule::update() {
    if (upt > 0) {
        upt--;
        return;
    }
    upt = upt_m;
    redraw = true;
    
    log("Fetching Schedule");
    cpr::Url url = "https://statsapi.mlb.com/api/v1/schedule?sportId=1";
    cpr::Response resp = cpr::Get(url);
    loga("Schedule Status", to_string(resp.status_code));
    loga(resp.text);
    if (resp.status_code == 200) {
        data = Json::parse(resp.text);
    }
    
    h = 1;
    if (data["dates"].size() > 0) {
        h += data["dates"][0]["games"].size();
    }
    wresize(win, h, w);
}

void Schedule::setPos(int ny) {
    y = ny;
    mvwin(win, y, x);
}