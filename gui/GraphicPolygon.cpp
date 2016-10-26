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
