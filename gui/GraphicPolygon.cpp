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
		int len;
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