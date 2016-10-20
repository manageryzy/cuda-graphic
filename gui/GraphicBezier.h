#pragma once


class GraphicBasicBezier
{
public:
	GraphicPoint pt1, pt2;
	GraphicAttrTimeline<float> ct1x, ct1y, ct2x, ct2y;

	void Serialize(CArchive& ar);
	std::vector<GraphicPoint> toPolygon();
	std::vector<GraphicBasicPoint> atFrame(int frame);
protected:
	inline DWORD blendColor(DWORD color1, DWORD color2, double t);
};


class GraphicBezier 
{
public:
	std::vector<GraphicBasicBezier> curves;
	GraphicColorTimeLine fillColor;


	void Serialize(CArchive& ar);
	GraphicPolygon * toPolygon();
	std::vector<GraphicBasicPoint> atFrame(int frame);
	GraphicBezier();
	~GraphicBezier();
};

