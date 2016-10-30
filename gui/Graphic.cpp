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

		ar >> label;

		// an silly way to load type
		int t;
		ar >> t;
		type = (GraphicType)t;

		switch (type)
		{
		case GRA_NONE:
			break;
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
		case GRA_NONE:
			break;
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

void Graphic::toPolygon()
{
	switch (this->type)
	{
	case GRA_NONE:
	case GRA_POLYGON:
		break;
	case GRA_CIRCLE:
		this->graphicPolygon.reset(this->graphicCircle->toPolygon());
		this->graphicCircle.reset(nullptr);
		this->type = GRA_POLYGON;
		break;
	case GRA_BEZIER:
		this->graphicPolygon.reset(this->graphicBezier->toPolygon());
		this->graphicBezier.reset(nullptr);
		this->type = GRA_POLYGON;
	}
}

void Graphic::init(GraphicType type,TCHAR * str)
{
	this->guid.Init();
	this->type = GRA_NONE;
	this->label = str;
	this->type = type;
	switch (type)
	{
	case GRA_NONE:
		break;
	case GRA_POLYGON:
		this->graphicPolygon.reset(new GraphicPolygon);
		break;
	case GRA_CIRCLE:
		this->graphicCircle.reset(new GraphicCircle);
		break;
	case GRA_BEZIER:
		this->graphicBezier.reset(new GraphicBezier);
		break;
	default:
		throw "unknown type";
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

void GUID_::Init()
{
	GUID guid;
	CoCreateGuid(&guid);
	(*this) = guid;
}
