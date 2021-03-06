#pragma once

#include"Surface.h"
#include"Vec2.h"
#include"Graphics.h"

//class to represent a font in the game
class Font
{
public:
	Font(std::string filename, Color chroma = Colors::White);
	void DrawText(std::string& src, Location& pos,Color color, Graphics& gfx);
private:
	RectI MapGleaphRect(char c);
private:
	Surface sprite;

	int gliphHeight;
	int gliphWidth;

	Color chroma;

	static constexpr int nColomns = 32;
	static constexpr int nRows = 3;
	static constexpr char first = ' ';
	static constexpr char last = '~';
};