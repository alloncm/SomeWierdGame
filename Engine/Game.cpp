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
	link({ 100,100 }, 170, 90, 90),
	f("Consolas13x24.bmp"),
	cha("knightTest32x48.bmp", 50.0f, { 400,400 }, 32, 48, { 0,0 }, 3, 0.1f),
	ball("Energy.bmp", 5, { 200,200 }, { 1,0 }),
	countB(0)
{
	balls = new EnergyBall [countB];
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	
	Vec2 dir(0.0f,0.0f);
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
	if (wnd.kbd.ReadChar() == ' ')
	{
		MakeFireBall();
	}
	cha.SetDirections(dir);
	cha.Update(ft.Mark());
	for (int i = 0; i < countB; i++)
	{
		balls[i].Update();
	}
}

void Game::ComposeFrame()
{
	cha.Draw(gfx);
	for (int i = 0; i < countB; i++)
	{
		balls[i].Draw(gfx);
	}
}

void Game::MakeFireBall()
{
	Vec2 v = cha.GetDirection();
	if (v.x > 1)
	{
		v.x = 1;
	}
	if (v.y > 1)
	{
		v.y = 1;
	}
	if (v.x < -1)
	{
		v.x = -1;
	}
	if (v.y < -1)
	{
		v.y = -1;
	}
	if (countB == 0)
	{
		delete[] balls;
		
		balls = new EnergyBall[countB + 1];
		balls[countB] = ball;
		balls[countB].SetDirection(v);
		countB++;
	}
	else
	{
		EnergyBall* temp = new EnergyBall[countB + 1];
		for (int i = 0; i < countB; i++)
		{
			temp[i] = balls[i];
		}
		delete[] balls;
		balls = temp;
		temp = nullptr;
		balls[countB] = ball;
		
		balls[countB].SetDirection(v);
		countB++;
	}
}
