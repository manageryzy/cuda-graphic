#pragma once
#include <vector>

typedef struct GraphicBasicPoint_ 
{
	//store value for one frame
public:
	float x;
	float y;
	DWORD color;
	float width;
	DWORD glowColor;
	float glowWidth;
	DWORD shadowColor;
	float shadowWidth;
} GraphicBasicPoint;

class GraphicPoint :
CObject
{
public :
	//frame value pair of attr
	std::vector<std::pair<int,float>> x;
	std::vector<std::pair<int,float>> y;
	std::vector<std::pair<int,DWORD>> color;
	std::vector<std::pair<int,float>> width;
	std::vector<std::pair<int,DWORD>> glowColor;
	std::vector<std::pair<int,float>> glowWidth;
	std::vector<std::pair<int,DWORD>> shadowColor;
	std::vector<std::pair<int,float>> shadowWidth;

	GraphicBasicPoint atFrame(int frame);
	void setxAtFrame(float x, int frame);
	void setyAtFrame(float y, int frame);
	void setcolorAtFrame(int color, int frame);
	void setwidthAtFrame(float width, int frame);
	void setglowColorAtFrame(int glowColor, int frame);
	void setglowWidthAtFrame(float glowWidth, int frame);
	void setshadowColorAtFrame(int shadowColor, int frame);
	void setshadowWidthAtFrame(float shadowWidth, int frame);

	DECLARE_SERIAL(GraphicPoint)
	virtual void Serialize(CArchive& ar);
};