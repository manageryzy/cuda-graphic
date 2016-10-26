#pragma once

class GraphicCircle 
{
public:
	GraphicAttrTimeline<float> x, y, r;
	GraphicColorTimeLine fillColor,color, glowColor, shadowColor;
	GraphicAttrTimeline<float> width, glowWidth, shadowWidth;

	void Serialize(CArchive& ar);
	GraphicPolygon * toPolygon();
	std::vector<GraphicBasicPoint> atFrame(int frame);
	void init();
	GraphicCircle();
	~GraphicCircle();
};

