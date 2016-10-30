#include "stdafx.h"
#include <memory>
#include "Graphic.h"




GraphicPolygon::GraphicPolygon()
{
}


GraphicPolygon::~GraphicPolygon()
{
}


void GraphicPolygon::Serialize(CArchive & ar)
{
	if (ar.IsLoading())
	{
		long long int len;
		ar >> len;
		for (auto i = 0; i < len; i++)
		{
			GraphicPoint pt;
			pt.Serialize(ar);
			points.push_back(pt);
		}

		fillColor.Serialize(ar);
	}
	else if (ar.IsStoring())
	{
		ar << points.size();
		for (auto & i : points)
		{
			i.Serialize(ar);
		}

		fillColor.Serialize(ar);
	}
}

std::vector<GraphicBasicPoint> GraphicPolygon::atFrame(int frame)
{
	auto pts = std::vector<GraphicBasicPoint>();

	for (auto & p : points)
	{
		pts.push_back(p.atFrame(frame));
	}

	return pts;
}

void GraphicPolygon::addPoint(int frame,float x, float y, DWORD color, float width, DWORD shadowColor, float shadowWidth, DWORD glowColor, float glowWidth)
{
	GraphicPoint pt;
	pt.init();
	pt.x.setAttrAtFrame(x, frame);
	pt.y.setAttrAtFrame(y, frame);
	pt.color.setAttrAtFrame(color, frame);
	pt.width.setAttrAtFrame(width, frame);
	pt.shadowColor.setAttrAtFrame(shadowColor, frame);
	pt.shadowWidth.setAttrAtFrame(shadowWidth, frame);
	pt.glowColor.setAttrAtFrame(glowColor, frame);
	pt.glowWidth.setAttrAtFrame(glowWidth, frame);
	points.push_back(pt);
}
