#include <chrono>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <ncurses.h>
#include <panel.h>
#include <unistd.h>
#include <vector>

#include "Game.h"
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

vector<Window*> WINDOWS;

void draw() {
    loga("DRAW");
    for (Window* w : WINDOWS) {
        w->draw();
    }
    
    /*
    Draw bottom bar
    */
    wclear(STAT_WIN);
    string rTime = to_string(R_TIME);
    string mid (XMAX - rTime.length(), ' ');
    string bot = rTime + mid;
    wattron(STAT_WIN, WA_STANDOUT);
    mvwaddnstr(STAT_WIN, 0, 0, bot.c_str(), XMAX);
    wattroff(STAT_WIN, WA_STANDOUT);
    wrefresh(STAT_WIN);
}

void update() {
    Window* prev;
    for (Window* w : WINDOWS) {
        w->update();
        if (prev != nullptr) {
            w->setY(prev->y + prev->h);
        }
        prev = w;
    }
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
    STANDINGS = new Standings(10);
    STANDINGS->setW(XMAX);
    STANDINGS->setX(0);
    WINDOWS.push_back(STANDINGS);
    
    SCHEDULE = new Schedule(10);
    SCHEDULE->setW(XMAX);
    SCHEDULE->setX(0);
    WINDOWS.push_back(SCHEDULE);
    
    Game* g = new Game(10, to_string(823475));
    g->setW(XMAX);
    g->setX(0);
    WINDOWS.push_back(g);
    
    chrono::time_point now = chrono::high_resolution_clock::now();
    double updateT = 0;
    
    bool running = true;
    
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
            update();
            draw();
            if (R_TIME <= 0) {
                R_TIME = R_TIME_MAX;
                //update();
                //draw();
            }
        }
        
        napms(50);
    }
    
    log("===== CLOSING MLB TERM =====");
    //delete STANDINGS;
    //delete SCHEDULE;
    for (Window* w : WINDOWS) {
        delete w;
    }
    
    delwin(STAT_WIN);
    endwin();
}