#include "stdafx.h"
#include <memory>
#include "GraphicBezier.h"


GraphicBezier::GraphicBezier()
{
}


GraphicBezier::~GraphicBezier()
{
}

IMPLEMENT_SERIAL(GraphicBezier, CObject, 1)

void GraphicBezier::Serialize(CArchive & ar)
{
	if (ar.IsLoading())
	{
	}
	else if (ar.IsStoring())
	{

	}
}