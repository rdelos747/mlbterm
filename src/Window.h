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
    Window(int utm);
    ~Window();
    
    
    void draw();
    void update();
    virtual void _draw() = 0;
    virtual void _update() = 0;
    
    void setX(int nx);
    void setY(int ny);
    void setW(int nw);
    void setH(int nh);
    
    int x, y;
    int w, h;
    
    int upt;
    int upt_m;
    Json data;
    bool redraw;
    

protected:
    WINDOW* win;
};

#endif