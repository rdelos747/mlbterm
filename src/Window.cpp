//#include "log.h"
//#include "utils.h"

#include "Window.h"

Window::Window(int utm) {
    win = newwin(1, 1, 0, 0);
    redraw = false;
    upt = 0;
    upt_m = utm;
}

Window::~Window() {
    log("Deleting Window");
    delwin(win);
}


// void Window::_draw() {}
void Window::draw() {
    if (!redraw) {
        return;
    }
    
    redraw = false;
    _draw();
}

// void Window::_update() {}
void Window::update() {
    if (upt > 0) {
        upt--;
        return;
    }
    upt = upt_m;
    redraw = true;
    
    _update();
}

void Window::setX(int nx) {
    x = nx;
    mvwin(win, y, x);
}

void Window::setY(int ny) {
    y = ny;
    mvwin(win, y, x);
}

void Window::setW(int nw) {
    w = nw;
    wresize(win, h, w);
}

void Window::setH(int nh) {
    h = nh;
    wresize(win, h, w);
}