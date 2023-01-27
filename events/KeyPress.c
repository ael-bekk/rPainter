#include "../inc/Editor.h"

int     KeyPress(int key, void *param)
{
    (void)param;

    switch(key) {

        case KEY_ESC:
            exit(0);
            break;

        case KEY_G:
            keys.g = !keys.g;
            break;

        case KEY_B:
            keys.f = 0;
            keys.b = 1;
            break;

        case KEY_F:
            keys.b = 0;
            keys.f = 1;
            break;

        case KEY_CNTRL:
            keys.cntrl = 1;
            break;

        default:
            break;
    }
    return (0);
}