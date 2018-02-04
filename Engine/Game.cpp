/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"



Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ball(FileNames::blast,250, { 200,200 }, { 1,0 }),
	info(FileNames::SEnemy,250.0f, { 100,100 },3),
	obs("greyCube.bmp", { 100,100 }, Colors::Magenta),
	demoLevel(&player,gfx,&obs,info),
	player(100, { 100,100 },ball)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

Game::~Game()
{
}

void Game::UpdateModel()
{
	if (!demoLevel.IsGameOver())
	{
		Vec2 dir(0.0f, 0.0f);

		if (wnd.kbd.KeyIsPressed('A'))
		{
			dir.x += -1;
		}
		if (wnd.kbd.KeyIsPressed('D'))
		{
			dir.x += 1;
		}
		if (wnd.kbd.KeyIsPressed('W'))
		{
			dir.y += -1;
		}
		if (wnd.kbd.KeyIsPressed('S'))
		{
			dir.y += 1;
		}


		//handles the fire
		Keyboard::Event e = wnd.kbd.ReadKey();
		Vec2 fireDir ( 0.0,0.0 );
		if (e.GetCode() == VK_LEFT && e.IsPress())
		{
			fireDir.x += -1;
		}
		else if (e.GetCode() == VK_RIGHT && e.IsPress())
		{
			fireDir.x += 1;
		}
		else if (e.GetCode() == VK_UP && e.IsPress())
		{
			fireDir.y += -1;
		}
		else if (e.GetCode() == VK_DOWN && e.IsPress())
		{
			fireDir.y += 1;
		}

		
		demoLevel.Update(dir, fireDir);
		
		
	}
}


void Game::ComposeFrame()
{
	demoLevel.Draw();
}

