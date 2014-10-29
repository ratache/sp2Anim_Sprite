#include "game.h"

LPDIRECT3DSURFACE9 kitty_image[7];
LPDIRECT3DSURFACE9 background;
SPRITE kitty;

//timing variable
long start = GetTickCount();

//initializes the game
int Game_Init(HWND hwnd)
{
	char s[20];
	int n;

	//set random number seed
	srand(time(NULL));

	//load the sprite animation
	for (n = 0; n<6; n++)
	{
		sprintf(s, "cat%d.bmp", n + 1);
		kitty_image[n] = LoadSurface(s, D3DCOLOR_XRGB(255, 0, 255));
		if (kitty_image[n] == NULL)
			return 0;
	}

	background = LoadSurface("background.bmp", D3DCOLOR_XRGB(255,0,255));

	//initialize the sprite’s properties
	kitty.x = 100;
	kitty.y = 150;
	kitty.width = 96;
	kitty.height = 96;
	kitty.curframe = 0;
	kitty.lastframe = 5;
	kitty.animdelay = 2;
	kitty.animcount = 0;
	kitty.movex = 8;
	kitty.movey = 0;

	//return okay
	return 1;
}

//the main game loop
void Game_Run(HWND hwnd)
{
	RECT rect;

	//make sure the Direct3D device is valid
	if (d3ddev == NULL)
		return;

	//after short delay, ready for next frame?
	//this keeps the game running at a steady frame rate
	if (GetTickCount() - start >= 30)
	{
		//reset timing
		start = GetTickCount();
		
		//move the sprite
		kitty.x += kitty.movex;
		kitty.y += kitty.movey;
		
		//"warp" the sprite at screen edges
		if (kitty.x > SCREEN_WIDTH - kitty.width)
			kitty.x = 0;
		if (kitty.x < 0)
			kitty.x = SCREEN_WIDTH - kitty.width;
		
		//has animation delay reached threshold?
		if (++kitty.animcount > kitty.animdelay)
		{
			//reset counter
			kitty.animcount = 0;
			//animate the sprite
			if (++kitty.curframe > kitty.lastframe)
				kitty.curframe = 0;
		}
	}
	
	//start rendering
	if (d3ddev->BeginScene())
	{
		//erase the entire background
		//d3ddev->ColorFill(backbuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
		d3ddev->StretchRect(background, NULL, backbuffer, NULL, D3DTEXF_NONE);
		//set the sprite’s rect for drawing
		rect.left = kitty.x;
		rect.top = kitty.y;
		rect.right = kitty.x + kitty.width;
		rect.bottom = kitty.y + kitty.height;

		//draw the sprite
		d3ddev->StretchRect(kitty_image[kitty.curframe], NULL,
			backbuffer, &rect, D3DTEXF_NONE);

		//stop rendering
		d3ddev->EndScene();
	}

	//display the back buffer on the screen
	d3ddev->Present(NULL, NULL, NULL, NULL);

	//check for escape key (to exit program)
	if (KEY_DOWN(VK_ESCAPE))
		PostMessage(hwnd, WM_DESTROY, 0, 0);
}

//frees memory and cleans up before the game ends
void Game_End(HWND hwnd)
{
	int n;
	//free the surface
	for (n = 0; n<6; n++)
		kitty_image[n]->Release();

	background->Release();
}