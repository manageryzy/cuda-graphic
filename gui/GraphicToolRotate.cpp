#include "stdafx.h"
#include "GraphicToolRotate.h"
#include "guiDoc.h"
#include "guiView.h"

GraphicToolRotate::GraphicToolRotate()
{
}


GraphicToolRotate::~GraphicToolRotate()
{
}

bool GraphicToolRotate::onLButtonDown(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	if (rotateCamera == nullptr)
	{
		rotateCamera = new GraphicCamera(*camera);
		rotateCamera->x = worldPoint.x;
		rotateCamera->y = worldPoint.y;
	}
	else
	{
		angle1 = getAngle(worldPoint.x - rotateCamera->x, worldPoint.y - rotateCamera->y);
		doRotate(point);
		state = 1;
	}

	return true;
}

bool GraphicToolRotate::onMouseMove(void * point)
{
	if (rotateCamera && state == 1)
		doRotate(point);
	return true;
}

bool GraphicToolRotate::onLButtonUp(void * point)
{
	if (rotateCamera && state == 1)
	{
		// add history here
		doRotate(point);
		state = 0;
		view->editTool = nullptr;
		delete rotateCamera;
		rotateCamera = nullptr;
	}
	return true;
}

void GraphicToolRotate::recoverHistory(GraphicHistory)
{
}

void GraphicToolRotate::redoHistory(GraphicHistory)
{
}

void GraphicToolRotate::reset()
{
	if (rotateCamera)
		delete rotateCamera;

	rotateCamera = nullptr;
	state = 0;
}

void GraphicToolRotate::doRotate(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	auto angle2 = getAngle(worldPoint.x - rotateCamera->x,worldPoint.y - rotateCamera->y);
	auto delta = angle2 - angle1;

	for (auto & guid : view->selectedGraphic)
	{
		auto gra = pDoc->graphics[guid].get();
		if (gra->type == GRA_POLYGON)
		{
			for (auto & pt : gra->graphicPolygon->points)
			{
				auto x = pt.x.atFrame(view->frame) - rotateCamera->x;
				auto y = pt.y.atFrame(view->frame) - rotateCamera->y;

				auto rotatePoint = rotateCamera->_rotate(D2D1::Point2F(x, y), delta);

				pt.x.setAttrAtFrame(rotatePoint.x + rotateCamera->x, view->frame);
				pt.y.setAttrAtFrame(rotatePoint.y + rotateCamera->y, view->frame);
			}
		}
		else if (gra->type == GRA_CIRCLE)
		{
			auto x = gra->graphicCircle->x.atFrame(view->frame) - rotateCamera->x;
			auto y = gra->graphicCircle->y.atFrame(view->frame) - rotateCamera->y;

			auto rotatePoint = rotateCamera->_rotate(D2D1::Point2F(x, y), delta);

			gra->graphicCircle->x.setAttrAtFrame(rotatePoint.x + rotateCamera->x, view->frame);
			gra->graphicCircle->y.setAttrAtFrame(rotatePoint.y + rotateCamera->y, view->frame);

		}
		else if (gra->type == GRA_BEZIER)
		{
			for (auto & c : gra->graphicBezier->curves)
			{
				auto x = c.ct1x.atFrame(view->frame) - rotateCamera->x;
				auto y = c.ct1y.atFrame(view->frame) - rotateCamera->y;
				auto rotatePoint = rotateCamera->_rotate(D2D1::Point2F(x, y), delta);
				c.ct1x.setAttrAtFrame(rotatePoint.x + rotateCamera->x, view->frame);
				c.ct1y.setAttrAtFrame(rotatePoint.y + rotateCamera->y, view->frame);


				x = c.ct2x.atFrame(view->frame) - rotateCamera->x;
				y = c.ct2y.atFrame(view->frame) - rotateCamera->y;
				rotatePoint = rotateCamera->_rotate(D2D1::Point2F(x, y), delta);
				c.ct2x.setAttrAtFrame(rotatePoint.x + rotateCamera->x, view->frame);
				c.ct2y.setAttrAtFrame(rotatePoint.y + rotateCamera->y, view->frame);

				x = c.pt1.x.atFrame(view->frame) - rotateCamera->x;
				y = c.pt1.y.atFrame(view->frame) - rotateCamera->y;
				rotatePoint = rotateCamera->_rotate(D2D1::Point2F(x, y), delta);
				c.pt1.x.setAttrAtFrame(rotatePoint.x + rotateCamera->x, view->frame);
				c.pt1.y.setAttrAtFrame(rotatePoint.y + rotateCamera->y, view->frame);

				x = c.pt2.x.atFrame(view->frame) - rotateCamera->x;
				y = c.pt2.y.atFrame(view->frame) - rotateCamera->y;
				rotatePoint = rotateCamera->_rotate(D2D1::Point2F(x, y), delta);
				c.pt2.x.setAttrAtFrame(rotatePoint.x + rotateCamera->x, view->frame);
				c.pt2.y.setAttrAtFrame(rotatePoint.y + rotateCamera->y, view->frame);
			}
		}
	}

	angle1 = angle2;
}

float GraphicToolRotate::getAngle(D2D1_POINT_2F pt)
{
	if (pt.y == 0 && pt.x == 0)
	{
		return 0.0f;
	}

	return atan2f(pt.y,pt.x);
}

float GraphicToolRotate::getAngle(float x, float y)
{
	if (x == 0 && y == 0)
	{
		return 0.0f;
	}

	return atan2f(y, x);
}

GRA_TOOL_MSG_MAP_START(GraphicToolRotate)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONDOWN, onLButtonDown)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONUP, onLButtonUp)
GRA_TOOL_MSG_MAP_ON(WM_MOUSEMOVE, onMouseMove)
GRA_TOOL_MSG_MAP_END
