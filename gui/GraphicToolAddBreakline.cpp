#include "stdafx.h"
#include "GraphicToolAddBreakline.h"
#include "guiDoc.h"
#include "guiView.h"
#include "resource.h"

#define STATE_NONE 0
#define STATE_PT 1

GraphicToolAddBreakline::GraphicToolAddBreakline()
{
}


GraphicToolAddBreakline::~GraphicToolAddBreakline()
{
}

bool GraphicToolAddBreakline::onLButtonDown(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	if (state == STATE_NONE)
	{
		view->creating = new Graphic();
		view->creating->init(GRA_POLYGON, L"unnamed breakline");
		view->creating->graphicPolygon->addPoint(view->frame, worldPoint.x, worldPoint.y);
		view->creating->graphicPolygon->addPoint(view->frame, worldPoint.x, worldPoint.y);
		view->creating->graphicPolygon->addPoint(view->frame, worldPoint.x, worldPoint.y);
		view->creating->graphicPolygon->addPoint(view->frame, worldPoint.x, worldPoint.y);
		view->beginCreating();
		state = STATE_PT;
	}
	else if (state == STATE_PT)
	{
		view->creating->graphicPolygon->points.back().x.setAttrAtFrame(worldPoint.x, view->frame);
		view->creating->graphicPolygon->points.back().y.setAttrAtFrame(worldPoint.y, view->frame);
		view->creating->graphicPolygon->addPoint(view->frame, worldPoint.x, worldPoint.y);
	}

	return true;
}

bool GraphicToolAddBreakline::onMouseMove(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	if (state == STATE_PT)
	{
		view->creating->graphicPolygon->points.back().x.setAttrAtFrame(worldPoint.x, view->frame);
		view->creating->graphicPolygon->points.back().y.setAttrAtFrame(worldPoint.y, view->frame);
	}

	return true;
}

bool GraphicToolAddBreakline::onLDoubleClick(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	if (state == STATE_PT)
	{
		view->creating->graphicPolygon->points.back().x.setAttrAtFrame(worldPoint.x, view->frame);
		view->creating->graphicPolygon->points.back().y.setAttrAtFrame(worldPoint.y, view->frame);
		auto res = MessageBox(view->GetSafeHwnd(), L"close polygon?", L"", MB_YESNO);
		if (res == IDYES)
		{
			auto x = view->creating->graphicPolygon->points[0].x.atFrame(view->frame);
			auto y = view->creating->graphicPolygon->points[0].y.atFrame(view->frame);
			view->creating->graphicPolygon->addPoint(view->frame, x, y);
		}

		view->endCreating();
		state = STATE_NONE;

		return true;
	}
	return false;
}

bool GraphicToolAddBreakline::onRButtonUp(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	if (state == STATE_PT)
	{
		if (view->creating->graphicPolygon->points.size() == 2)
		{
			cancel();
		}
		else
		{
			view->creating->graphicPolygon->points.pop_back();
			view->creating->graphicPolygon->points.back().x.setAttrAtFrame(worldPoint.x, view->frame);
			view->creating->graphicPolygon->points.back().y.setAttrAtFrame(worldPoint.y, view->frame);
		}
		return true;
	}
	return false;
}

bool GraphicToolAddBreakline::onESC(void *)
{
	if (state == STATE_PT)
	{
		cancel();
		return true;
	}
	return false;
}

void GraphicToolAddBreakline::recoverHistory(GraphicHistory)
{
}

void GraphicToolAddBreakline::redoHistory(GraphicHistory)
{
}

void GraphicToolAddBreakline::reset()
{
	state = STATE_NONE;
}

void GraphicToolAddBreakline::cancel()
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


GRA_TOOL_MSG_MAP_START(GraphicToolAddBreakline)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONDOWN, onLButtonDown)
GRA_TOOL_MSG_MAP_ON(WM_MOUSEMOVE, onMouseMove)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONDBLCLK,onLDoubleClick)
GRA_TOOL_MSG_MAP_ON(WM_RBUTTONUP, onRButtonUp)
GRA_TOOL_MSG_MAP_ON(ID_ESC, onESC)
GRA_TOOL_MSG_MAP_END
