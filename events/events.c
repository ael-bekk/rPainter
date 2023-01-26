#include "../Editor.h"

int OnHover(int x, int y, int w, int h) {

    return (mouse.x >= x && mouse.x <= w && mouse.y >= y && mouse.y <= h);
}

int OnClick(int x, int y, int w, int h) {

    return (mouse_OnClick.x >= x && mouse_OnClick.x <= w && mouse_OnClick.y >= y && mouse_OnClick.y <= h && mouse_OnClick.event);
}