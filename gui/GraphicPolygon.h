#pragma once
#include <vector>

class GraphicPolygon :
	public CObject
{
	DECLARE_SERIAL(GraphicPolygon)
public:

	std::vector<GraphicPoint> points;

	virtual void Serialize(CArchive& ar);
	GraphicPolygon();
	~GraphicPolygon();
};

