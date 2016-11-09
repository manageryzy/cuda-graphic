#include "stdafx.h"
#include "GraphicToolScale.h"
#include "guiDoc.h"
#include "guiView.h"


GraphicToolScale::GraphicToolScale()
{
}


GraphicToolScale::~GraphicToolScale()
{
}

bool GraphicToolScale::onLButtonDown(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	if (scaleCamera == nullptr)
	{
		scaleCamera = new GraphicCamera(*camera);
		scaleCamera->x = worldPoint.x;
		scaleCamera->y = worldPoint.y;
	}
	else
	{
		dist1 = sqrtf((worldPoint.x - scaleCamera->x)*(worldPoint.x - scaleCamera->x) + (worldPoint.y - scaleCamera->y)*(worldPoint.y - scaleCamera->y));
		doScale(point);
		state = 1;
	}

	return true;
}

bool GraphicToolScale::onMouseMove(void * point)
{
	if (scaleCamera && state == 1)
		doScale(point);
	return true;
}

bool GraphicToolScale::onLButtonUp(void * point)
{
	if (scaleCamera && state == 1)
	{
		// add history here
		doScale(point);
		state = 0;
		view->editTool = nullptr;
		delete scaleCamera;
		scaleCamera = nullptr;
	}
	return true;
}

void GraphicToolScale::recoverHistory(GraphicHistory)
{
}

void GraphicToolScale::redoHistory(GraphicHistory)
{
}

void GraphicToolScale::reset()
{
	if (scaleCamera)
		delete scaleCamera;

	scaleCamera = nullptr;
	state = 0;
}

void GraphicToolScale::doScale(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	auto dist2 = sqrtf((worldPoint.x - scaleCamera->x)*(worldPoint.x - scaleCamera->x) + (worldPoint.y - scaleCamera->y)*(worldPoint.y - scaleCamera->y));
	auto scale = dist2 / dist1;

	scaleCamera->scale = scale;

	for (auto & guid : view->selectedGraphic)
	{
		auto gra = pDoc->graphics[guid].get();
		if (gra->type == GRA_POLYGON)
		{
			for (auto & pt : gra->graphicPolygon->points)
			{
				auto x = pt.x.atFrame(view->frame) - scaleCamera->x;
				pt.x.setAttrAtFrame(x*scale + scaleCamera->x, view->frame);

				auto y = pt.y.atFrame(view->frame) - scaleCamera->y;
				pt.y.setAttrAtFrame(y*scale + scaleCamera->y, view->frame);
			}
		}
		else if (gra->type == GRA_CIRCLE)
		{
			auto x = gra->graphicCircle->x.atFrame(view->frame) - scaleCamera->x;
			gra->graphicCircle->x.setAttrAtFrame(x*scale + scaleCamera->x, view->frame);

			auto y = gra->graphicCircle->y.atFrame(view->frame) - scaleCamera->y;
			gra->graphicCircle->y.setAttrAtFrame(y*scale + scaleCamera->y, view->frame);

			gra->graphicCircle->r.setAttrAtFrame(gra->graphicCircle->r.atFrame(view->frame)*scale, view->frame);
		}
		else if (gra->type == GRA_BEZIER)
		{
			for (auto & c : gra->graphicBezier->curves)
			{
				c.ct1x.setAttrAtFrame((c.ct1x.atFrame(view->frame) - scaleCamera->x)*scale + scaleCamera->x, view->frame);
				c.ct1y.setAttrAtFrame((c.ct1y.atFrame(view->frame) - scaleCamera->y)*scale + scaleCamera->y, view->frame);
				c.ct2x.setAttrAtFrame((c.ct2x.atFrame(view->frame) - scaleCamera->x)*scale + scaleCamera->x, view->frame);
				c.ct2y.setAttrAtFrame((c.ct2y.atFrame(view->frame) - scaleCamera->y)*scale + scaleCamera->y, view->frame);

				c.pt1.x.setAttrAtFrame((c.pt1.x.atFrame(view->frame) - scaleCamera->x)*scale + scaleCamera->x, view->frame);
				c.pt1.y.setAttrAtFrame((c.pt1.y.atFrame(view->frame) - scaleCamera->y)*scale + scaleCamera->y, view->frame);
				c.pt2.x.setAttrAtFrame((c.pt2.x.atFrame(view->frame) - scaleCamera->x)*scale + scaleCamera->x, view->frame);
				c.pt2.y.setAttrAtFrame((c.pt2.y.atFrame(view->frame) - scaleCamera->y)*scale + scaleCamera->y, view->frame);
			}
		}
	}

	dist1 = sqrtf((worldPoint.x - scaleCamera->x)*(worldPoint.x - scaleCamera->x) + (worldPoint.y - scaleCamera->y)*(worldPoint.y - scaleCamera->y));
}

GRA_TOOL_MSG_MAP_START(GraphicToolScale)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONDOWN, onLButtonDown)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONUP, onLButtonUp)
GRA_TOOL_MSG_MAP_ON(WM_MOUSEMOVE, onMouseMove)
GRA_TOOL_MSG_MAP_END