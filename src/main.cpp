#include <chrono>
#include <cpr/cpr.h>
#include <format>
#include <nlohmann/json.hpp>
#include <ncurses.h>
#include <panel.h>
#include <stdexcept>
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

//set<string> AUTO_LINES;
//set<string> AUTO_BUGS;


map<string, GMODE> WATCHING;
string ON_FIN = "NONE"; // how to handle game on finish
bool SCH_CLEAR = true;  // remove active game from sch
bool HIDE_SCR = false;  // hide score

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

bool parseArgs(int argc, char* argv[]) {
    loga("PARSING ARGS");
    if (argc == 1) {
        return true;
    }
    
    string error = "";
    
    for(int i = 1; i < argc; i++) {
        vector<string> s = split(argv[i], '=');
        
        if (s[0] == "hidescore" || s[0] == "-hs") {
            HIDE_SCR = true;
        }
        else if (   s[0] == "scheduleautoclear" || 
                    s[0] == "-sac") {
            SCH_CLEAR = true;
        }
        else if (   s[0] == "onfinish" || 
                    s[0] == "-of") {
            if (s[1] == "close") {
                ON_FIN = "CLOSE";
            }
            else if (s[1] == "line") {
                ON_FIN = "LINE";
            }
            else if (s[1] == "none") {
                ON_FIN = "NONE";
            }
            else {
                error = format(
                    "COMMAND {} INVALID ARGUMENT {}", 
                    s[0], 
                    s[1]
                );
            }
        }
        else if (   s[0] == "line" ||
                    s[0] == "-l") {
            vector<string> lines = split(s[1], ',');
        }
        else if (   s[0] == "bug" ||
                    s[0] == "-b") {
            
        } 
        else {
            error = format(
                "UNKNOWN COMMAND: {}",
                s[0]
            );
        }
    }
    
    if (error != "") {
        cout << error << '\n';
        return false;
    }
    
    return true;   
}


int main(int argc, char* argv[]) {
    clearLog();
    log("===== STARTING MLB TERM =====");
    
    if (!parseArgs(argc, argv)) {
        return 0;
    }
    
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
    
    /*
    Game* g = new Game(10, to_string(823475));
    g->setW(XMAX);
    g->setX(0);
    WINDOWS.push_back(g);
    */
    
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