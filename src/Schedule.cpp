#include "utils.h"

#include "Schedule.h"

Schedule::Schedule(int nw) {
    w = nw;
    win = newwin(0, w, 0, 0);
}

Schedule::~Schedule() {
    log("Deleting Schedule");
    delwin(win);
}

void Schedule::draw() {
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
    
    wrefresh(win);
}

void Schedule::update() {
    log("Fetching Schedule");
    cpr::Url url = "https://statsapi.mlb.com/api/v1/schedule?sportsId=1&date=05/05/2025";
    cpr::Response resp = cpr::Get(url);
    loga("Schedule Status", to_string(resp.status_code));
    if (resp.status_code == 200) {
        data = Json::parse(resp.text);
    }
}

void Schedule::setPos(int ny) {
    y = ny;
    mvwin(win, y, x);
}