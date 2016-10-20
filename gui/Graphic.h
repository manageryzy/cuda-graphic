#pragma once

#include "GraphicStyle.h"
#include "GraphicPolygon.h"
#include "GraphicBezier.h"
#include "GraphicCircle.h"


#define GRAPHIC_SETTING_CIRCLE_EDGES 128
#define GRAPHIC_SETTING_BEZIER_EDGES 1024

enum GraphicType 
{
	GRA_POLYGON,
	GRA_CIRCLE,
	GRA_BEZIER
};

class GUID_
{
	long long unsigned int a, b;

public:
	GUID_()	{	}

	GUID_(const GUID_ &o)
	{
		this->a = o.a;
		this->b = o.b;
	}

	bool const operator==(const GUID_ &o) {
		return a == o.a && b == o.b;
	}

	bool operator<(const GUID_ &o)  const {
		if (a < o.a)
			return true;
		if (b < o.b)
			return true;

		return false;
	}

	bool operator=(const GUID &o)
	{
		a = *((long long unsigned int *) (&o));
		b = *((long long unsigned int *) (&o)+8);
	}

	void Serialize(CArchive& ar);
};


class Graphic 
{
public:
	GUID_ guid;
	CString label;
	bool inited;

	GraphicType type;
	
	std::auto_ptr<GraphicBezier> graphicBezier;
	std::auto_ptr<GraphicCircle> graphicCircle;
	std::auto_ptr<GraphicPolygon> graphicPolygon;

	void Serialize(CArchive& ar);
	void toPolygon();
	Graphic();
	~Graphic();
};

