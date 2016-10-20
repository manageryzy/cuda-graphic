#include "stdafx.h"
#include <memory>
#include "Graphic.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <set>


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
		x.Serialize(ar);
		y.Serialize(ar);
		r.Serialize(ar);
		fillColor.Serialize(ar);
		color.Serialize(ar);
		glowColor.Serialize(ar);
		shadowColor.Serialize(ar);
		width.Serialize(ar);
		glowWidth.Serialize(ar);
		shadowWidth.Serialize(ar);
	}
	else if (ar.IsStoring())
	{
		x.Serialize(ar);
		y.Serialize(ar);
		r.Serialize(ar);
		fillColor.Serialize(ar);
		color.Serialize(ar);
		glowColor.Serialize(ar);
		shadowColor.Serialize(ar);
		width.Serialize(ar);
		glowWidth.Serialize(ar);
		shadowWidth.Serialize(ar);
	}
}

GraphicPolygon * GraphicCircle::toPolygon()
{
	GraphicPolygon * polygon = new GraphicPolygon;
	polygon->fillColor = this->fillColor;

	//calc the new key frame list
	std::set<int> keyFrame;
	for (auto &p : x.attr)
	{
		keyFrame.insert(p.first);
	}
	for (auto &p : y.attr)
	{
		keyFrame.insert(p.first);
	}
	for (auto &p : r.attr)
	{
		keyFrame.insert(p.first);
	}
	

	for (auto i = 0; i < GRAPHIC_SETTING_CIRCLE_EDGES; i++)
	{
		GraphicPoint pt;
		float phi = (float)(2 * M_PI) / GRAPHIC_SETTING_CIRCLE_EDGES*i;
		pt.color = this->color;
		pt.width = this->width;
		pt.glowColor = this->glowColor;
		pt.glowWidth = this->glowWidth;
		pt.shadowColor = this->shadowColor;
		pt.shadowWidth = this->shadowWidth;
		for (auto f : keyFrame)
		{
			pt.x.setAttrAtFrame(x.atFrame(f) + r.atFrame(f)*sinf(phi), f);
			pt.x.setAttrAtFrame(y.atFrame(f) + r.atFrame(f)*cosf(phi), f);
		}
		polygon->points.push_back(pt);
	}
	return polygon;
}

std::vector<GraphicBasicPoint> GraphicCircle::atFrame(int frame)
{
	std::vector<GraphicBasicPoint> pts;
	for (auto i = 0; i < GRAPHIC_SETTING_CIRCLE_EDGES; i++)
	{
		GraphicBasicPoint pt;
		float phi = (float)(2 * M_PI) / GRAPHIC_SETTING_CIRCLE_EDGES*i;
		pt.color = this->color.atFrame(frame);
		pt.width = this->width.atFrame(frame);
		pt.glowColor = this->glowColor.atFrame(frame);
		pt.glowWidth = this->glowWidth.atFrame(frame);
		pt.shadowColor = this->shadowColor.atFrame(frame);
		pt.shadowWidth = this->shadowWidth.atFrame(frame);
		pt.x = x.atFrame(frame) + r.atFrame(frame)*sinf(phi);
		pt.y = y.atFrame(frame) + r.atFrame(frame)*cosf(phi);
		pts.push_back(pt);
	}
	return pts;
}
