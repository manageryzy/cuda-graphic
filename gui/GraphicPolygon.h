#pragma once
#include <vector>

class GraphicPolygon 
{
public:

	std::vector<GraphicPoint> points;
	GraphicColorTimeLine fillColor;

	void Serialize(CArchive& ar);
	std::vector<GraphicBasicPoint> atFrame(int frame);
	void addPoint(int frame,float x, float y, DWORD color = 0xFFFFFF,float width = 1.0f,DWORD shadowColor = 0,float shadowWidth = 0,DWORD glowColor = 0,float glowWidth = 0);
	GraphicPolygon();
	~GraphicPolygon();
};

