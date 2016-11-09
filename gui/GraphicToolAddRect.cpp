#include "stdafx.h"
#include "GraphicToolAddRect.h"
#include "guiDoc.h"
#include "guiView.h"
#include "resource.h"

#define STATE_NONE 0
#define STATE_PT1 1


GraphicToolAddRect::GraphicToolAddRect()
{
}


GraphicToolAddRect::~GraphicToolAddRect()
{
}

bool GraphicToolAddRect::onLButtonDown(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	if (state == STATE_NONE)
	{
		view->creating = new Graphic();
		view->creating->init(GRA_POLYGON, L"unnamed rect");
		view->creating->graphicPolygon->addPoint(view->frame, worldPoint.x, worldPoint.y);
		view->creating->graphicPolygon->addPoint(view->frame, worldPoint.x, worldPoint.y);
		view->creating->graphicPolygon->addPoint(view->frame, worldPoint.x, worldPoint.y);
		view->creating->graphicPolygon->addPoint(view->frame, worldPoint.x, worldPoint.y);
		view->creating->graphicPolygon->addPoint(view->frame, worldPoint.x, worldPoint.y);
		view->beginCreating();
		state = STATE_PT1;
	}
	else if (state == STATE_PT1)
	{
		view->creating->graphicPolygon->points[1].x.setAttrAtFrame(worldPoint.x, view->frame);
		view->creating->graphicPolygon->points[2].x.setAttrAtFrame(worldPoint.x, view->frame);
		view->creating->graphicPolygon->points[2].y.setAttrAtFrame(worldPoint.y, view->frame);
		view->creating->graphicPolygon->points[3].y.setAttrAtFrame(worldPoint.y, view->frame);
		view->endCreating();
		state = STATE_NONE;

		//TODO: add history here
	}
	else
	{
		throw "unknown state";
	}
	return true;
}

bool GraphicToolAddRect::onMouseMove(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	if (state == STATE_PT1)
	{
		view->creating->graphicPolygon->points[1].x.setAttrAtFrame(worldPoint.x, view->frame);
		view->creating->graphicPolygon->points[2].x.setAttrAtFrame(worldPoint.x, view->frame);
		view->creating->graphicPolygon->points[2].y.setAttrAtFrame(worldPoint.y, view->frame);
		view->creating->graphicPolygon->points[3].y.setAttrAtFrame(worldPoint.y, view->frame);
	}

	return true;
}

bool GraphicToolAddRect::onRButtonUp(void *)
{
	if (state == STATE_PT1)
	{
		cancel();
		return true;
	}
	return false;
}

bool GraphicToolAddRect::onESC(void *)
{
	if (state == STATE_PT1)
	{
		cancel();
		return true;
	}
	return false;
}

void GraphicToolAddRect::recoverHistory(GraphicHistory)
{
}

void GraphicToolAddRect::redoHistory(GraphicHistory)
{
}

void GraphicToolAddRect::reset()
{
	state = STATE_NONE;
}

void GraphicToolAddRect::cancel()
{
	auto res = MessageBox(view->GetSafeHwnd(), L"cancel?", L"", MB_YESNO);
	if (res == IDYES)
	{
		delete view->creating;
		view->creating = nullptr;
		view->editTool = nullptr;
		state = STATE_NONE;
	}
}


GRA_TOOL_MSG_MAP_START(GraphicToolAddRect)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONDOWN, onLButtonDown)
GRA_TOOL_MSG_MAP_ON(WM_MOUSEMOVE, onMouseMove)
GRA_TOOL_MSG_MAP_ON(WM_RBUTTONUP, onRButtonUp)
GRA_TOOL_MSG_MAP_ON(ID_ESC, onESC)
GRA_TOOL_MSG_MAP_END
