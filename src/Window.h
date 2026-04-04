#ifndef WINDOW_H
#define WINDOW_H

#include <cpr/cpr.h>
#include <ncurses.h>
#include <nlohmann/json.hpp>
#include <panel.h>
#include <string>
#include <vector>

#include "log.h"
#include "utils.h"

using namespace std;
using Json = nlohmann::json;

class Window {
public:
    Window(int nw, int utm);
    ~Window();
    
    
    void draw();
    void update();
    void setX(int nx);
    void setY(int ny);
    
    int x, y;
    int w, h;
    
    int upt;
    int upt_m;
    Json data;
    bool redraw;
    

private:
    WINDOW* win;
};

#endif