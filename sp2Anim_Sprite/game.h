#ifndef _GAME_H
#define _GAME_H

#include <d3d9.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "dxgraphics.h"

//application title
#define APPTITLE "Anim_Sprite"

//screen setup
#define FULLSCREEN 1
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//macros to read the keyboard asynchronously
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//function prototypes
int Game_Init(HWND);
void Game_Run(HWND);
void Game_End(HWND);

//sprite structure
typedef struct {
	int x, y;
	int width, height;
	int movex, movey;
	int curframe, lastframe;
	int animdelay, animcount;
} SPRITE;
#endif