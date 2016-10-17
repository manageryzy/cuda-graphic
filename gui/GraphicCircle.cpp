#include "stdafx.h"
#include <memory>
#include "GraphicCircle.h"


GraphicCircle::GraphicCircle()
{
}


GraphicCircle::~GraphicCircle()
{
}


void GraphicCircle::Serialize(CArchive & ar)
{
	if (ar.IsLoading())
	{
	}
	else if (ar.IsStoring())
	{

	}
}