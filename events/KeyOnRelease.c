#include "../inc/Editor.h"

int     KeyOnRelease(int key, void *param)
{
    (void)param;

    switch(key) {

        case KEY_CNTRL:
            keys.cntrl = 0;
            break;
        
        default:
            break;
    }
    return (0);
}