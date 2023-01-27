#ifndef __EVENTS_H__
#define __EVENTS_H__

int OnHover(int x, int y, int w, int h);
int OnClick(int x, int y, int w, int h);
int CloseWin(void *param);
int KeyPress(int key, void *param);
int KeyOnRelease(int key, void *param);
int MouseOnClick(int button, int x, int y, void *param);
int MouseOnRelease(int button, int x, int y, void *param);
int MouseMove(int x, int y, void *param);
int rendering(void *param);

#endif