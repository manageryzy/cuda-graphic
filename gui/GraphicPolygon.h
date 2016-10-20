#pragma once
#include <vector>

class GraphicPolygon 
{
public:

	std::vector<GraphicPoint> points;
	GraphicColorTimeLine fillColor;

	void Serialize(CArchive& ar);
	GraphicPolygon();
	~GraphicPolygon();
};

