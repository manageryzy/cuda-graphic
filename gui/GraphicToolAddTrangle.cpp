#include "stdafx.h"
#include "GraphicToolAddTrangle.h"
#include "guiDoc.h"
#include "guiView.h"
#include "resource.h"

#define STATE_NONE 0
#define STATE_PT1 1
#define STATE_PT2 2

GraphicToolAddTrangle::GraphicToolAddTrangle()
{
}


GraphicToolAddTrangle::~GraphicToolAddTrangle()
{
}

bool GraphicToolAddTrangle::onLButtonDown(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	if (state == STATE_NONE)
	{
		view->creating = new Graphic();
		view->creating->init(GRA_POLYGON, L"unnamed trangle");
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
		view->creating->graphicPolygon->points[1].y.setAttrAtFrame(worldPoint.y, view->frame);
		state = STATE_PT2;
	}
	else if (state == STATE_PT2)
	{
		view->creating->graphicPolygon->points[2].x.setAttrAtFrame(worldPoint.x, view->frame);
		view->creating->graphicPolygon->points[2].y.setAttrAtFrame(worldPoint.y, view->frame);
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

bool GraphicToolAddTrangle::onMouseMove(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	if (state == STATE_PT1)
	{
		view->creating->graphicPolygon->points[1].x.setAttrAtFrame(worldPoint.x, view->frame);
		view->creating->graphicPolygon->points[1].y.setAttrAtFrame(worldPoint.y, view->frame);
	}
	else if (state == STATE_PT2)
	{
		view->creating->graphicPolygon->points[2].x.setAttrAtFrame(worldPoint.x, view->frame);
		view->creating->graphicPolygon->points[2].y.setAttrAtFrame(worldPoint.y, view->frame);
	}
	return true;
}

bool GraphicToolAddTrangle::onRButtonUp(void *)
{
	if (state == STATE_PT1)
	{
		cancel();
		return true;
	}
	else if (state == STATE_PT2)
	{
		auto x = view->creating->graphicPolygon->points[0].x.atFrame(view->frame);
		auto y = view->creating->graphicPolygon->points[0].y.atFrame(view->frame);
		view->creating->graphicPolygon->points[2].x.setAttrAtFrame(x, view->frame);
		view->creating->graphicPolygon->points[2].y.setAttrAtFrame(y, view->frame);
		state = STATE_PT1;
		return true;
	}
	return false;
}

bool GraphicToolAddTrangle::onESC(void *)
{
	if (state == STATE_PT1 || state == STATE_PT2)
	{
		cancel();
		return true;
	}
	return false;
}

void GraphicToolAddTrangle::recoverHistory(GraphicHistory)
{
}

void GraphicToolAddTrangle::redoHistory(GraphicHistory)
{
	
}

void GraphicToolAddTrangle::reset()
{
	state = STATE_NONE;
}

void GraphicToolAddTrangle::cancel()
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




GRA_TOOL_MSG_MAP_START(GraphicToolAddTrangle)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONDOWN, onLButtonDown)
GRA_TOOL_MSG_MAP_ON(WM_MOUSEMOVE, onMouseMove)
GRA_TOOL_MSG_MAP_ON(WM_RBUTTONUP, onRButtonUp)
GRA_TOOL_MSG_MAP_ON(ID_ESC, onESC)
GRA_TOOL_MSG_MAP_END
