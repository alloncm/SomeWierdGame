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
	cha("knightTest32x48.bmp", 100.0f, { 400,400 }, 32, 48, { 0,0 }, 3, 0.1f),
	ball("energy18x18.bmp", 250, { 200,200 }, { 1,0 }),
	bGuy("badGuy32x48.bmp", 100.0f, { 400,400 }, 32, 48, { 0,0 }, 3, 0.1f),
	countB(0)
{
	balls = nullptr;
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
	DestroyFireBalls({ { 100,100 },{ gfx.ScreenWidth - 100,gfx.ScreenHeight - 100 } });
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
	
	Keyboard::Event e = wnd.kbd.ReadKey();
	if ( e.GetCode() == VK_SPACE && e.IsPress() )
	{
		MakeFireBall();
	}
	cha.SetDirection(dir);
	cha.Update(ft.Mark());
	float dt = ftB.Mark();
	for (int i = 0; i < countB; i++)
	{
		if (balls[i] != nullptr)
		{
			balls[i]->Update(dt);
		}
	}
	
}

void Game::ComposeFrame()
{
	cha.Draw(gfx);
	bGuy.Draw(gfx);
	for (int i = 0; i < countB; i++)
	{
		if (balls[i] != nullptr)
		{
			balls[i]->Draw(gfx);
		}
	}
}

void Game::MakeFireBall()
{
	Vec2 v = cha.GetDirection();		//sets the position of the ball to match the character
	
	ball.SetLocation(GetBallMatchingPos());
	//updates the directoio of the ball based on the velocity of the caracter
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
	ball.SetDirection(v);
	if (countB == 0)		//the first ball
	{
		balls = new EnergyBall*[countB + 1];
		balls[countB] = new EnergyBall;
		*balls[countB] = ball;			
		countB++;
	}
	else
	{
		int j = 0;								//counts the number of elements in balls
		EnergyBall** temp = new EnergyBall* [countB + 1];		//temporary place to copy only the valid elemets 
		for (int i = 0; i < countB; i++)
		{
			if (balls[i] != nullptr)		//copies only if not nullptr
			{
				temp[j] = balls[i];
				balls[i] = nullptr;
				j++;						//keep track of how many copied
			}
		}                
		delete[] balls;
		balls = new EnergyBall* [j+1];		//realocate the memory 
		for (int i = 0; i < j; i++)			//copies the loctions of the values to the new alocated memory
		{
			balls[i] = temp[i];
			temp[i] = nullptr;
		}
		delete[] temp;
		temp = nullptr;
		countB = j;
		balls[countB] = new EnergyBall;			//alocate memory for another element
		*balls[countB] = ball;					
		countB++;
	}
}

void Game::DestroyFireBalls(Rect<int> border)
{
	for (int i = 0; i < countB; i++)
	{
		if (balls[i] != nullptr)
		{
			bool col = balls[i]->GetRect().IsColliding(border);		//checks if the ball is in bounds 
			if (!col)
			{
				//delete the ball
				delete balls[i];
				balls[i] = nullptr;
				balls[i] = balls[countB-1];			//move the deleted 
				countB--;							
			}
		}
	}
}



Vec2 Game::GetBallMatchingPos()
{
	Vec2 vtr = cha.GetPosition();
	
	Vec2 v = cha.GetDirection();
	//make sure v values are 1 or 0
	if (v.x > 0 && v.x < 1)
	{
		v.x = 1;
	}
	else if (v.x < 0 && v.x > -1)
	{
		v.x = -1;
	}
	if (v.y > 0 && v.y < 1)
	{
		v.y = 1;
	}
	else if (v.y < 0 && v.y > -1)
	{
		v.y = -1;
	}
	Vec2_<int> p ((int)v.x,(int)v.y);
	if (p.x == 1)	//looking right
	{
		vtr.x += cha.GetWidth();
	}
	if (p.x == -1)	//looking left
	{
		vtr.x -= ball.GetWidth();
	}
	if (p.x == 0 && p.y == -1)	//looking up
	{
		vtr.x += ((cha.GetWidth() / 2) - (ball.GetWidth() / 2));
		vtr.y -= ball.GetHeight();
	}
	if (p.x == 0 && p.y == 1)	//looking down
	{
		vtr.x += ((cha.GetWidth() / 2) - (ball.GetWidth() / 2));
		vtr.y += cha.GetHeight();
	}
	
	return vtr;
}