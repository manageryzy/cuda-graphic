#pragma once

#define GRAPHIC_SETTING_CIRCLE_EDGES 128
#define GRAPHIC_SETTING_BEZIER_EDGES 1024

enum GraphicType 
{
	GRA_NONE,
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

	bool operator<(const GUID_ &o)  const {
		if (a < o.a)
			return true;
		if (a == o.a && b < o.b)
			return true;

		return false;
	}

	bool operator>(const GUID_ &o)  const {
		if (a > o.a)
			return true;
		if (a==o.a &&b > o.b)
			return true;

		return false;
	}

	bool operator==(const GUID_ &o)  const {
		return a == o.a && b == o.b;
	}

	bool operator=(const GUID &o)
	{
		a = *((long long unsigned int *) (&o));
		b = *((long long unsigned int *) (&o)+1);

		return true;
	}

	void Serialize(CArchive& ar);
	void Init();
};

#include "GraphicStyle.h"
#include "GraphicPolygon.h"
#include "GraphicBezier.h"
#include "GraphicCircle.h"
#include "GraphicCamera.h"

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
	void init();
	Graphic();
	~Graphic();
};

