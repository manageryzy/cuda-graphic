#include "stdafx.h"
#include "GraphicStyle.h"


GraphicBasicPoint GraphicPoint::atFrame(int frame)
{
	GraphicBasicPoint pt;
	pt.x = x.atFrame(frame);
	pt.y = y.atFrame(frame);
	pt.color = color.atFrame(frame);
	pt.width = width.atFrame(frame);
	pt.glowColor = glowColor.atFrame(frame);
	pt.glowWidth = glowWidth.atFrame(frame);
	pt.shadowColor = shadowColor.atFrame(frame);
	pt.shadowWidth = shadowWidth.atFrame(frame);
	return pt;
}

GraphicPoint::GraphicPoint()
{
}

GraphicPoint::GraphicPoint(const GraphicPoint & o)
{
	this->x = o.x;
	this->y = o.x;
	this->color = o.color;
	this->width = o.width;
	this->glowColor = o.glowColor;
	this->glowWidth = o.glowWidth;
	this->shadowColor = o.shadowColor;
	this->shadowWidth = o.shadowWidth;
}

IMPLEMENT_SERIAL(GraphicPoint, CObject, 1)
void GraphicPoint::Serialize(CArchive & ar)
{
	if (ar.IsLoading())
	{
		x.Serialize(ar);
		y.Serialize(ar);
		color.Serialize(ar);
		width.Serialize(ar);
		glowColor.Serialize(ar);
		glowWidth.Serialize(ar);
		shadowColor.Serialize(ar);
		shadowWidth.Serialize(ar);
	}
	else if (ar.IsStoring())
	{
		x.Serialize(ar);
		y.Serialize(ar);
		color.Serialize(ar);
		width.Serialize(ar);
		glowColor.Serialize(ar);
		glowWidth.Serialize(ar);
		shadowColor.Serialize(ar);
		shadowWidth.Serialize(ar);
	}
}

