//#include "log.h"
//#include "utils.h"

#include "Window.h"

Window::Window(int nw, int utm) {
    w = nw;
    win = newwin(1, w, 0, 0);
    redraw = false;
    upt = 0;
    upt_m = utm;
}

Window::~Window() {
    log("Deleting Window");
    delwin(win);
}

void Window::draw() {}

void Window::update() {}

void Window::setX(int nx) {
}

void Window::setY(int ny) {
    y = ny;
    mvwin(win, y, x);
}