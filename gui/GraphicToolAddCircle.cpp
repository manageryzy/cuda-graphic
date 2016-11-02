#include "stdafx.h"
#include "GraphicToolAddCircle.h"
#include "guiDoc.h"
#include "guiView.h"
#include "resource.h"

#define STATE_NONE 0
#define STATE_PT1 1

GraphicToolAddCircle::GraphicToolAddCircle()
{
}


GraphicToolAddCircle::~GraphicToolAddCircle()
{
}

bool GraphicToolAddCircle::onLButtonDown(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	if (state == STATE_NONE)
	{
		view->createing = new Graphic();
		view->createing->init(GRA_CIRCLE, L"unnamed circle");
		view->createing->graphicCircle->init();
		view->createing->graphicCircle->x.setAttrAtFrame(worldPoint.x, view->frame);
		view->createing->graphicCircle->y.setAttrAtFrame(worldPoint.y, view->frame);
		view->selectedGraphic.clear();
		state = STATE_PT1;
	}
	else if (state == STATE_PT1)
	{
		auto centerX = view->createing->graphicCircle->x.atFrame(view->frame);
		auto centerY = view->createing->graphicCircle->y.atFrame(view->frame);
		auto r = sqrtf((centerX - worldPoint.x)*(centerX - worldPoint.x) + (centerY - worldPoint.y)*(centerY - worldPoint.y));
		view->createing->graphicCircle->r.setAttrAtFrame(r, view->frame);
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

bool GraphicToolAddCircle::onMouseMove(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	if (state == STATE_PT1)
	{
		auto centerX = view->createing->graphicCircle->x.atFrame(view->frame);
		auto centerY = view->createing->graphicCircle->y.atFrame(view->frame);
		auto r = sqrtf((centerX - worldPoint.x)*(centerX - worldPoint.x) + (centerY - worldPoint.y)*(centerY - worldPoint.y));
		view->createing->graphicCircle->r.setAttrAtFrame(r, view->frame);
	}

	return true;
}

bool GraphicToolAddCircle::onRButtonUp(void *)
{
	if (state == STATE_PT1)
	{
		cancel();
		return true;
	}

	return false;
}

bool GraphicToolAddCircle::onESC(void *)
{
	if (state == STATE_PT1)
	{
		cancel();
		return true;
	}

	return false;
}

void GraphicToolAddCircle::recoverHistory(GraphicHistory)
{
}

void GraphicToolAddCircle::redoHistory(GraphicHistory)
{
}

void GraphicToolAddCircle::reset()
{
	state = STATE_NONE;
}

void GraphicToolAddCircle::cancel()
{
	auto res = MessageBox(view->GetSafeHwnd(), L"cancel?", L"", MB_YESNO);
	if (res == IDYES)
	{
		delete view->createing;
		view->createing = nullptr;
		view->editTool = nullptr;
		state = STATE_NONE;
	}
}


GRA_TOOL_MSG_MAP_START(GraphicToolAddCircle)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONDOWN, onLButtonDown)
GRA_TOOL_MSG_MAP_ON(WM_MOUSEMOVE, onMouseMove)
GRA_TOOL_MSG_MAP_END

