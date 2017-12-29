#pragma once
#include"Colors.h"
#include<string>
#include"ChiliWin.h"
#include<fstream>
#include"Rect.h"

//repsresent an image loaded from .bmp file
class Surface
{
public:
	Surface(int w, int h);
	Surface(const Surface& s);
	Surface(const std::string& filename);
	Surface() = default;
	Surface& operator=(const Surface& s);
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	int GetWidth()const;	
	int GetHeight()const;
	RectI GetRect()const;
	~Surface();
private:
	Color* pPixels = nullptr;
	int width;
	int height;
};