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
	this->y = o.y;
	this->color = o.color;
	this->width = o.width;
	this->glowColor = o.glowColor;
	this->glowWidth = o.glowWidth;
	this->shadowColor = o.shadowColor;
	this->shadowWidth = o.shadowWidth;
}

void GraphicPoint::init()
{
	color.setAttrAtFrame(0xFFFFFFFF, 0);
	width.setAttrAtFrame(1.0f, 0);
	glowColor.setAttrAtFrame(0, 0);
	glowWidth.setAttrAtFrame(0, 0);
	shadowColor.setAttrAtFrame(0, 0);
	shadowWidth.setAttrAtFrame(0, 0);
}

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

GraphicColorTimeLine::GraphicColorTimeLine()
{
	setAttrAtFrame(0, 0);
}

GraphicColorTimeLine::~GraphicColorTimeLine()
{
}

DWORD GraphicColorTimeLine::atFrame(int frame)
{
	if (attr.size() == 0)
	{
		return 0;
	}

	DWORD attr1, attr2;
	int frame1 = -1, frame2 = -1;

	for (auto it = attr.begin(); it != attr.end(); ++it)
	{
		if (frame == (*it).first)
		{
			return (*it).second;
		}
		else if (frame < (*it).first)
		{
			frame2 = (*it).first;
			attr2 = (*it).second;
		}
	}
	for (auto it = attr.end()-1; it != attr.begin(); --it)
	{
		if (frame >(*it).first)
		{
			frame1 = (*it).first;
			attr1 = (*it).second;
		}
	}

	if (frame1 == -1 && frame2 == -1)
	{
		return 0;
	}

	if (frame1 == -1)
		return attr2;

	if (frame2 == -1)
		return attr1;

	return blendColor(attr1, attr2, ((double)frame - frame1) / (frame2 - frame1));
}
