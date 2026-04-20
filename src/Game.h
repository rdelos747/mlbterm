#ifndef GAME_H
#define GAME_H

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

enum GMODE {
    MIN
};


class Game : public Window {
public:
    Game(int utm, string id);
    ~Game();
    
    void _update();
    void _draw();

    string id;
    GMODE mode;
};

#endif