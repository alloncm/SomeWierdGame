#pragma once
#include"Colors.h"
#include"Graphics.h"
#include<vector>
#include"Rect.h"
#include"Surface.h"
#include"Vec2.h"

//a class to handle all the animations int the game

class Animation
{
public:
	Animation(int x, int y, int width, int height, int count, const Surface& s,float ht, Color chroma = Colors::Magenta);
	void Update(float dt);								//updates the animation based on the time between every frame 
	void Draw(const Location& l, Graphics& gfx);		//Draws the object to the screen
	void Draw(const Location& l, Graphics& gfx, RectI& clip);		//Draws the object in the boundry of the rect
private:
	void Advance();					//inner function to move between frame to frame
private:
	Color chroma;					//the background
	const Surface& sprite;			//the sprite for the animation
	std::vector<RectI> frames;		//vector to hold all the frames
	int iCurFrame = 0;				//int to hold the current frame
	float holdTime;					//time between every frame
	float curFrameTime = 0.0f;		//stores the time between every frame to count the time to hold
};