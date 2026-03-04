#include <chrono>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <ncurses.h>
#include <panel.h>
#include <unistd.h>

#include "log.h"
#include "Schedule.h"
#include "Standings.h"

using namespace std;
using Json = nlohmann::json;

int XMAX;
int YMAX;
WINDOW* STAT_WIN;

int R_TIME = 0;
int R_TIME_MAX = 10;

Standings* STANDINGS;
Schedule* SCHEDULE;

void draw() {
    STANDINGS->draw();
    SCHEDULE->draw();
    
    /*
    Draw bottom bar
    */
    wclear(STAT_WIN);
    string rTime = to_string(R_TIME);
    string mid (XMAX - rTime.length(), ' ');
    string bot = rTime + mid;
    wattron(STAT_WIN, WA_STANDOUT);
    mvwaddnstr(STAT_WIN, YMAX - 1, 0, bot.c_str(), XMAX);
    wattroff(STAT_WIN, WA_STANDOUT);
    wrefresh(STAT_WIN);
}

void update() {
    /*
    Update all active windows
    */
    STANDINGS->update();
    SCHEDULE->update();
    
    /*
    Position all active windows
    */
    STANDINGS->setPos(0);
    SCHEDULE->setPos(STANDINGS->y);
}


int main(int argc, char* argv[]) {
    clearLog();
    log("===== STARTING MLB TERM =====");
    
    initscr();
    curs_set(0);
    keypad(stdscr, true);
    nonl();
    noecho();
    nodelay(stdscr, true);
    raw();
    set_escdelay(1);
    getmaxyx(stdscr, YMAX, XMAX);
    loga(to_string(XMAX), to_string(YMAX));
    
    STAT_WIN = newwin(1, XMAX, YMAX - 1, 0);
    STANDINGS = new Standings(XMAX);
    
    chrono::time_point now = chrono::high_resolution_clock::now();
    double updateT = 0;
    
    bool running = true;
    
    update();
    
    while(running) {
        chrono::time_point old = now;
        now = chrono::high_resolution_clock::now();
        chrono::duration<double> delta = now - old;
        
        int ch = getch();
        string input(keyname(ch));
        
        if (input == "^Q") {
            running = false;
        }
        
        updateT -= delta.count();
        if (updateT <= 0) {
            updateT = 1;
            
            R_TIME -= 1;
            draw();
            if (R_TIME <= 0) {
                R_TIME = R_TIME_MAX;
                //update();
            }
        }
    }
    
    log("===== CLOSING MLB TERM =====");
    delete STANDINGS;
    delete SCHEDULE;
    delwin(STAT_WIN);
    endwin();
}