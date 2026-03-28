#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <cpr/cpr.h>
#include <ncurses.h>
#include <nlohmann/json.hpp>
#include <panel.h>
#include <string>
#include <vector>

#include "log.h"

using namespace std;
using Json = nlohmann::json;

class Schedule {
public:
    Schedule(int nw, int utm);
    ~Schedule();
    
    void update();
    void draw();
    void setPos(int ny);
    
    int x, y;
    int w, h;
    Json data;
    bool redraw;
    int upt;
    int upt_m;
    
private:
    WINDOW* win;
};

#endif