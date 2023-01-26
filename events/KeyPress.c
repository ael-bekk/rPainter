#include "../Editor.h"

int     KeyPress(int key, void *param)
{
    (void)param;
    if (key == 53)
        exit(0);
    // press on the keyboard on 'g'
    if (key == 5)
        g = !g;
    // press on the keyboard on 'b'
    if (key == 11)
        f = 0,
        b = 1;
    // press on the keyboard on 'f'
    if (key == 3)
        b = 0,
        f = 1;
    return (0);
}