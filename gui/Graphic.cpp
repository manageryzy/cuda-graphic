#include "stdafx.h"
#include <memory>
#include "Graphic.h"


Graphic::Graphic()
{
	inited = false;
}


Graphic::~Graphic()
{
}


void Graphic::Serialize(CArchive & ar)
{
	if (ar.IsLoading())
	{
		inited = true;
		
		// load guid
		guid.Serialize(ar);

		// an silly way to load type
		int t;
		ar >> t;
		type = (GraphicType)t;

		switch (type)
		{
		case GRA_POLYGON:
			graphicPolygon.reset(new GraphicPolygon);
			graphicPolygon->Serialize(ar);
			break;
		case GRA_CIRCLE:
			graphicCircle.reset(new GraphicCircle);
			graphicCircle->Serialize(ar);
			break;
		case GRA_BEZIER:
			graphicBezier.reset(new GraphicBezier);
			graphicBezier->Serialize(ar);
			break;
		default:
			throw "error grapgic type";
			break;
		}

	}
	else if (ar.IsStoring())
	{
		guid.Serialize(ar);

		ar << label;

		ar << (int)type;

		switch (type)
		{
		case GRA_POLYGON:
			graphicPolygon->Serialize(ar);
			break;
		case GRA_CIRCLE:
			graphicCircle->Serialize(ar);
			break;
		case GRA_BEZIER:
			graphicBezier->Serialize(ar);
			break;
		default:
			break;
		}
	}
}

void GUID_::Serialize(CArchive & ar)
{
	if (ar.IsLoading())
	{
		ar >> a;
		ar >> b;
	}
	else if (ar.IsStoring())
	{
		ar << a;
		ar << b;
	}
}