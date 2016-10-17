#pragma once
#include <vector>

class GraphicPolygon 
{
public:

	std::vector<GraphicPoint> points;

	void Serialize(CArchive& ar);
	GraphicPolygon();
	~GraphicPolygon();
};

