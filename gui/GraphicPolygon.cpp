#include "stdafx.h"
#include <memory>
#include "Graphic.h"


GraphicPolygon::GraphicPolygon()
{
}


GraphicPolygon::~GraphicPolygon()
{
}

IMPLEMENT_SERIAL(GraphicPolygon, CObject, 1)

void GraphicPolygon::Serialize(CArchive & ar)
{
	if (ar.IsLoading())
	{
	}
	else if (ar.IsStoring())
	{

	}
}