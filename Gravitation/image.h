#pragma once

#include <vector>

struct Color
{
	float r, g, b;

	Color();
	Color(float r, float g, float b);
	~Color();
};

class image
{
public:
	image(int width, int height);
	~image();

	Color GetColor(int x, int y) const;
	void SetColor(const Color& color, int x, int y);

	void Export(const char* path) const;
private:
	int m_width;
	int m_height;
	std::vector<Color> m_colors;
};

