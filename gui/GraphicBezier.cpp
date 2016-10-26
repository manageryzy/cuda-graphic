#include "stdafx.h"
#include <memory>
#include "Graphic.h"
#include <set>


GraphicBezier::GraphicBezier()
{
}


GraphicBezier::~GraphicBezier()
{
}


void GraphicBezier::Serialize(CArchive & ar)
{
	if (ar.IsLoading())
	{
		long long int len;
		ar >> len;
		for (auto i = 0; i < len; i++)
		{
			GraphicBasicBezier g;
			g.Serialize(ar);
			curves.push_back(g);
		}
		fillColor.Serialize(ar);
	}
	else if (ar.IsStoring())
	{
		ar << curves.size();
		for (auto & g : curves)
		{
			g.Serialize(ar);
		}
		fillColor.Serialize(ar);
	}
}

GraphicPolygon * GraphicBezier::toPolygon()
{
	GraphicPolygon * polygons = new GraphicPolygon();
	polygons->fillColor = this->fillColor;
	polygons->points.reserve(curves.size()*GRAPHIC_SETTING_BEZIER_EDGES);

	for (auto & curve : curves)
	{
		auto polygon = curve.toPolygon();
		polygons->points.insert(polygons->points.end(), polygon.begin(), polygon.end());
	}

	return polygons;
}

std::vector<GraphicBasicPoint> GraphicBezier::atFrame(int frame)
{
	std::vector<GraphicBasicPoint> points;
	points.reserve(curves.size()*GRAPHIC_SETTING_BEZIER_EDGES);

	for (auto & curve : curves)
	{
		auto point = curve.atFrame(frame);
		points.insert(points.end(), point.begin(), point.end());
	}

	return points;
}

void GraphicBasicBezier::Serialize(CArchive & ar)
{
	if (ar.IsLoading())
	{
		pt1.Serialize(ar);
		pt2.Serialize(ar);
		ct1x.Serialize(ar);
		ct1y.Serialize(ar);
		ct2x.Serialize(ar);
		ct2y.Serialize(ar);
	}
	else if (ar.IsStoring())
	{
		pt1.Serialize(ar);
		pt2.Serialize(ar);
		ct1x.Serialize(ar);
		ct1y.Serialize(ar);
		ct2x.Serialize(ar);
		ct2y.Serialize(ar);
	}
}

std::vector<GraphicPoint> GraphicBasicBezier::toPolygon()
{
	std::vector<GraphicPoint> pts;

	//calc the new key frame list
	std::set<int> keyFrame;
	for (auto &p : ct1x.attr)
	{
		keyFrame.insert(p.first);
	}
	for (auto &p : ct1y.attr)
	{
		keyFrame.insert(p.first);
	}
	for (auto &p : ct2x.attr)
	{
		keyFrame.insert(p.first);
	}
	for (auto &p : ct2y.attr)
	{
		keyFrame.insert(p.first);
	}
	for (auto &p : pt1.color.attr)
	{
		keyFrame.insert(p.first);
	}
	for (auto &p : pt1.glowColor.attr)
	{
		keyFrame.insert(p.first);
	}
	for (auto &p : pt1.glowWidth.attr)
	{
		keyFrame.insert(p.first);
	}
	for (auto &p : pt1.shadowColor.attr)
	{
		keyFrame.insert(p.first);
	}
	for (auto &p : pt1.shadowWidth.attr)
	{
		keyFrame.insert(p.first);
	}
	for (auto &p : pt1.width.attr)
	{
		keyFrame.insert(p.first);
	}
	for (auto &p : pt1.x.attr)
	{
		keyFrame.insert(p.first);
	}
	for (auto &p : pt1.y.attr)
	{
		keyFrame.insert(p.first);
	}
	for (auto &p : pt2.color.attr)
	{
		keyFrame.insert(p.first);
	}
	for (auto &p : pt2.glowColor.attr)
	{
		keyFrame.insert(p.first);
	}
	for (auto &p : pt2.glowWidth.attr)
	{
		keyFrame.insert(p.first);
	}
	for (auto &p : pt2.shadowColor.attr)
	{
		keyFrame.insert(p.first);
	}
	for (auto &p : pt2.shadowWidth.attr)
	{
		keyFrame.insert(p.first);
	}
	for (auto &p : pt2.width.attr)
	{
		keyFrame.insert(p.first);
	}
	for (auto &p : pt2.x.attr)
	{
		keyFrame.insert(p.first);
	}
	for (auto &p : pt2.y.attr)
	{
		keyFrame.insert(p.first);
	}
	
	for (auto i = 0; i < GRAPHIC_SETTING_BEZIER_EDGES; i++)
	{
		float t = 1.0f * i / GRAPHIC_SETTING_BEZIER_EDGES;
		GraphicPoint pt;
		for (auto f : keyFrame)
		{
			pt.x.setAttrAtFrame(pt1.x.atFrame(f) * (1 - t) * (1 - t) * (1 - t) +
				ct1x.atFrame(f) * (1 - t) *(1 - t) * t +
				ct2x.atFrame(f) * (1 - t) * t * t +
				pt2.x.atFrame(f) * t * t * t,f);
			pt.y.setAttrAtFrame(pt1.y.atFrame(f) * (1 - t) * (1 - t) * (1 - t) +
				ct1y.atFrame(f) * (1 - t) *(1 - t) * t +
				ct2y.atFrame(f) * (1 - t) * t * t +
				pt2.y.atFrame(f) * t * t * t, f);

			pt.color.setAttrAtFrame(blendColor(pt1.color.atFrame(f), pt2.color.atFrame(f), t), f);
			pt.glowColor.setAttrAtFrame(blendColor(pt1.glowColor.atFrame(f), pt2.glowColor.atFrame(f), t), f);
			pt.shadowColor.setAttrAtFrame(blendColor(pt1.shadowColor.atFrame(f), pt2.shadowColor.atFrame(f), t), f);

			pt.width.setAttrAtFrame(pt1.width.atFrame(f) * t + pt2.width.atFrame(f) * (1 - t), f);
			pt.glowWidth.setAttrAtFrame(pt1.glowWidth.atFrame(f) * t + pt2.glowWidth.atFrame(f) * (1 - t), f);
			pt.shadowWidth.setAttrAtFrame(pt1.shadowWidth.atFrame(f) * t + pt2.shadowWidth.atFrame(f) * (1 - t), f);
		}
	}


	return pts;
}

std::vector<GraphicBasicPoint> GraphicBasicBezier::atFrame(int frame)
{
	std::vector<GraphicBasicPoint> pts;
	for (auto i = 0; i < GRAPHIC_SETTING_BEZIER_EDGES; i++)
	{
		float t = 1.0f * i / GRAPHIC_SETTING_BEZIER_EDGES;
		GraphicBasicPoint pt;
		
		pt.x = pt1.x.atFrame(frame) * (1 - t) * (1 - t) * (1 - t) +
			ct1x.atFrame(frame) * (1 - t) *(1 - t) * t +
			ct2x.atFrame(frame) * (1 - t) * t * t +
			pt2.x.atFrame(frame) * t * t * t;

		pt.y = pt1.y.atFrame(frame) * (1 - t) * (1 - t) * (1 - t) +
			ct1y.atFrame(frame) * (1 - t) *(1 - t) * t +
			ct2y.atFrame(frame) * (1 - t) * t * t +
			pt2.y.atFrame(frame) * t * t * t;


		pt.color = blendColor(pt1.color.atFrame(frame), pt2.color.atFrame(frame), t);
		pt.glowColor = blendColor(pt1.glowColor.atFrame(frame), pt2.glowColor.atFrame(frame), t);
		pt.shadowColor = blendColor(pt1.shadowColor.atFrame(frame), pt2.shadowColor.atFrame(frame), t);
		
		pt.width = pt1.width.atFrame(frame) * t + pt2.width.atFrame(frame) * (1 - t);
		pt.glowWidth = pt1.glowWidth.atFrame(frame) * t + pt2.glowWidth.atFrame(frame) * (1 - t);
		pt.shadowWidth = pt1.shadowWidth.atFrame(frame) * t + pt2.shadowWidth.atFrame(frame) * (1 - t);

		
	}
	return pts;
}

inline DWORD GraphicBasicBezier::blendColor(DWORD color1, DWORD color2, double t)
{
	BYTE r1, g1, b1, a1;
	BYTE r2, g2, b2, a2;
	BYTE r, g, b, a;

	r1 = GetRValue(color1);
	g1 = GetGValue(color1);
	b1 = GetBValue(color1);
	a1 = LOBYTE(color1 >> 24);

	r2 = GetRValue(color2);
	g2 = GetGValue(color2);
	b2 = GetBValue(color2);
	a2 = LOBYTE(color2 >> 24);

	r = (BYTE)(t*r1 + (1 - t)*r2);
	g = (BYTE)(t*g1 + (1 - t)*g2);
	b = (BYTE)(t*b1 + (1 - t)*b2);
	a = (BYTE)(t*a1 + (1 - t)*a2);
	
	DWORD color = RGB(r, g, b) | (DWORD)a << 24;

	return color;
}
