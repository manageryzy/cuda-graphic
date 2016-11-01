#include "stdafx.h"
#include "Graphic.h"

void GraphicCamera::Serialize(CArchive & ar)
{
	if (ar.IsLoading())
	{
		guid.Serialize(ar);
		ar >> label;
		ar >> x;
		ar >> y;
		ar >> scale;
	}
	else if(ar.IsStoring())
	{
		guid.Serialize(ar);
		ar << label;
		ar << x;
		ar << y;
		ar << scale;
	}
}

GraphicCamera::GraphicCamera()
{
	x = 0;
	y = 0;
	scale = 1;
	guid.Init();
	label = L"new Camera";
}

