#include "stdafx.h"
#include <memory>
#include "GraphicBezier.h"


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
	}
	else if (ar.IsStoring())
	{

	}
}