#include "stdafx.h"
#include <memory>
#include "GraphicCircle.h"


GraphicCircle::GraphicCircle()
{
}


GraphicCircle::~GraphicCircle()
{
}

IMPLEMENT_SERIAL(GraphicCircle, CObject, 1)

void GraphicCircle::Serialize(CArchive & ar)
{
	if (ar.IsLoading())
	{
	}
	else if (ar.IsStoring())
	{

	}
}