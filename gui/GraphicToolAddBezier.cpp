#include "stdafx.h"
#include "GraphicToolAddBezier.h"
#include "guiDoc.h"
#include "guiView.h"
#include "resource.h"

#define STATE_NONE 0
#define STATE_PT1 1
#define STATE_PT2 2
#define STATE_PT3 3


GraphicToolAddBezier::GraphicToolAddBezier()
{
}


GraphicToolAddBezier::~GraphicToolAddBezier()
{
}

bool GraphicToolAddBezier::onLButtonDown(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	if (state == STATE_NONE)
	{
		view->createing = new Graphic();
		view->createing->init(GRA_BEZIER, L"unnamed bezier");
		view->createing->graphicBezier->init(view->frame);

		GraphicBasicBezier bezier;
		bezier.pt1.init();
		bezier.pt1.x.setAttrAtFrame(worldPoint.x, view->frame);
		bezier.pt1.y.setAttrAtFrame(worldPoint.y, view->frame);
		bezier.pt2.init();
		bezier.pt2.x.setAttrAtFrame(worldPoint.x, view->frame);
		bezier.pt2.y.setAttrAtFrame(worldPoint.y, view->frame);
		bezier.ct1x.setAttrAtFrame(worldPoint.x, view->frame);
		bezier.ct1y.setAttrAtFrame(worldPoint.y, view->frame);
		bezier.ct2x.setAttrAtFrame(worldPoint.x, view->frame);
		bezier.ct2y.setAttrAtFrame(worldPoint.y, view->frame);
		view->createing->graphicBezier->curves.push_back(bezier);

		view->beginCreating();
		state = STATE_PT1;
	}
	else if (state == STATE_PT2)
	{
		auto & bezier = view->createing->graphicBezier->curves.back();
		bezier.pt2.x.setAttrAtFrame(worldPoint.x, view->frame);
		bezier.pt2.y.setAttrAtFrame(worldPoint.y, view->frame);
		bezier.ct2x.setAttrAtFrame(worldPoint.x, view->frame);
		bezier.ct2y.setAttrAtFrame(worldPoint.y, view->frame);
		state = STATE_PT3;
	}

	return true;
}

bool GraphicToolAddBezier::onLButtonUp(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	if (state == STATE_PT1)
	{
		auto & bezier = view->createing->graphicBezier->curves.back();
		bezier.ct1x.setAttrAtFrame(worldPoint.x, view->frame);
		bezier.ct1y.setAttrAtFrame(worldPoint.y, view->frame);
		state = STATE_PT2;
	}
	else if (state == STATE_PT3)
	{
		auto & lastBezier = view->createing->graphicBezier->curves.back();
		lastBezier.ct2x.setAttrAtFrame(lastBezier.pt2.x.atFrame(view->frame) * 2 - worldPoint.x, view->frame);
		lastBezier.ct2y.setAttrAtFrame(lastBezier.pt2.y.atFrame(view->frame) * 2 - worldPoint.y, view->frame);
		auto x = lastBezier.pt2.x.atFrame(view->frame);
		auto y = lastBezier.pt2.y.atFrame(view->frame);

		GraphicBasicBezier bezier;
		bezier.pt1.init();
		bezier.pt1.x.setAttrAtFrame(x, view->frame);
		bezier.pt1.y.setAttrAtFrame(y, view->frame);
		bezier.pt2.init();
		bezier.pt2.x.setAttrAtFrame(x, view->frame);
		bezier.pt2.y.setAttrAtFrame(y, view->frame);
		bezier.ct1x.setAttrAtFrame(worldPoint.x, view->frame);
		bezier.ct1y.setAttrAtFrame(worldPoint.y, view->frame);
		bezier.ct2x.setAttrAtFrame(x, view->frame);
		bezier.ct2y.setAttrAtFrame(y, view->frame);
		view->createing->graphicBezier->curves.push_back(bezier);
		state = STATE_PT2;
	}

	return false;
}

bool GraphicToolAddBezier::onMouseMove(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	if (state == STATE_PT1)
	{
		auto & bezier = view->createing->graphicBezier->curves.back();
		bezier.ct1x.setAttrAtFrame(worldPoint.x, view->frame);
		bezier.ct1y.setAttrAtFrame(worldPoint.y, view->frame);
		bezier.pt2.x.setAttrAtFrame(worldPoint.x, view->frame);
		bezier.pt2.y.setAttrAtFrame(worldPoint.y, view->frame);
		bezier.ct2x.setAttrAtFrame(worldPoint.x, view->frame);
		bezier.ct2y.setAttrAtFrame(worldPoint.y, view->frame);
	}
	else if (state == STATE_PT2)
	{
		auto & bezier = view->createing->graphicBezier->curves.back();
		bezier.pt2.x.setAttrAtFrame(worldPoint.x, view->frame);
		bezier.pt2.y.setAttrAtFrame(worldPoint.y, view->frame);
		bezier.ct2x.setAttrAtFrame(worldPoint.x, view->frame);
		bezier.ct2y.setAttrAtFrame(worldPoint.y, view->frame);
	}
	else if (state == STATE_PT3)
	{
		auto & bezier = view->createing->graphicBezier->curves.back();
		bezier.ct2x.setAttrAtFrame(bezier.pt2.x.atFrame(view->frame) * 2 - worldPoint.x, view->frame);
		bezier.ct2y.setAttrAtFrame(bezier.pt2.y.atFrame(view->frame) * 2 - worldPoint.y, view->frame);
	}

	return true;
}

bool GraphicToolAddBezier::onLDoubleClick(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	if (state != STATE_NONE)
	{
		auto res = MessageBox(view->GetSafeHwnd(), L"close?", L"", MB_YESNO);
		if (res == IDYES)
		{
			auto & first = view->createing->graphicBezier->curves.front();
			auto & last = view->createing->graphicBezier->curves.back();

			last.pt2.x.setAttrAtFrame(first.pt1.x.atFrame(view->frame), view->frame);
			last.pt2.y.setAttrAtFrame(first.pt1.y.atFrame(view->frame), view->frame);
			last.ct2x.setAttrAtFrame(first.pt1.x.atFrame(view->frame) * 2 - first.ct1x.atFrame(view->frame), view->frame);
			last.ct2y.setAttrAtFrame(first.pt1.y.atFrame(view->frame) * 2 - first.ct1y.atFrame(view->frame), view->frame);
		}

		view->endCreating();
		state = STATE_NONE;

		return true;
	}

	return false;
}

bool GraphicToolAddBezier::onRButtonUp(void *)
{
	if (state == STATE_PT2)
	{
		if (view->createing->graphicBezier->curves.size() >= 2)
		{
			view->createing->graphicBezier->curves.pop_back();
			return true;
		}
		else
		{
			cancel();
			return true;
		}
	}
	return false;
}

bool GraphicToolAddBezier::onESC(void *)
{
	if (state == STATE_PT1 || state == STATE_PT2 || state == STATE_PT3)
	{
		cancel();
		return true;
	}

	return false;
}

void GraphicToolAddBezier::recoverHistory(GraphicHistory)
{
}

void GraphicToolAddBezier::redoHistory(GraphicHistory)
{
}

void GraphicToolAddBezier::reset()
{
	state = STATE_NONE;
}

void GraphicToolAddBezier::cancel()
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


GRA_TOOL_MSG_MAP_START(GraphicToolAddBezier)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONDOWN, onLButtonDown)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONUP, onLButtonUp)
GRA_TOOL_MSG_MAP_ON(WM_MOUSEMOVE, onMouseMove)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONDBLCLK, onLDoubleClick)
GRA_TOOL_MSG_MAP_ON(WM_RBUTTONUP, onRButtonUp)
GRA_TOOL_MSG_MAP_ON(ID_ESC, onESC)
GRA_TOOL_MSG_MAP_END