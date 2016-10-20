#pragma once
#include <vector>

class GraphicPolygon 
{
public:

	std::vector<GraphicPoint> points;
	GraphicColorTimeLine fillColor;

	void Serialize(CArchive& ar);
	std::vector<GraphicBasicPoint> atFrame(int frame);
	GraphicPolygon();
	~GraphicPolygon();
};

