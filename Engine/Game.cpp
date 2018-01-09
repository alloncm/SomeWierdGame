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
	cha(100.0f, { 400,400 }, 32, 48, { 0,0 }, 3, 0.1f, ball),
	ball(250, { 200,200 }, { 1,0 }),
	info(25.0f, 32, 48, Vec2_<int>{ 0,0 }, 3, 0.1f),
	obs("rock1.bmp", { 100,100 }, Colors::Magenta, 48, 48),
	demoLevel(&cha,gfx,&obs,info)


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
	Vec2 dir(0.0f, 0.0f);
	
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		dir.x += -1;
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		dir.x += 1;
	}
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		dir.y += -1;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		dir.y += 1;
	}
	bool fire = false;
	Keyboard::Event e = wnd.kbd.ReadKey();
	if ( e.GetCode() == 'X' && e.IsPress() )
	{
		fire = true;
	}
	demoLevel.Update(dir, fire);
}


void Game::ComposeFrame()
{
	demoLevel.Draw();
}

