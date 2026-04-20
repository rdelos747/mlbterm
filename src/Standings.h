#ifndef STANDINGS_H
#define STANDINGS_H

#include <cpr/cpr.h>
#include <ncurses.h>
#include <nlohmann/json.hpp>
#include <panel.h>
#include <string>
#include <vector>

#include "log.h"
#include "Window.h"

using namespace std;
using Json = nlohmann::json;

class Standings : public Window {
public:
    Standings(int utm);
    ~Standings();
    
    void _update();
    void _draw();
};

#endif