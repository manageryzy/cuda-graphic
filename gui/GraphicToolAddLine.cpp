#include "stdafx.h"
#include "GraphicToolAddLine.h"
#include "guiDoc.h"
#include "guiView.h"

#define STATE_NONE 0
#define STATE_PT1 1

GraphicToolAddLine::GraphicToolAddLine()
{
}


GraphicToolAddLine::~GraphicToolAddLine()
{
}

bool GraphicToolAddLine::onLButtonDown(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;
	
	if (state == STATE_NONE)
	{
		view->createing = new Graphic();
		view->createing->init(GRA_POLYGON,L"unnamed line");
		view->createing->graphicPolygon->addPoint(view->frame,worldPoint.x, worldPoint.y);
		view->createing->graphicPolygon->addPoint(view->frame, worldPoint.x, worldPoint.y);
		view->selectedGraphic.clear();
		state = STATE_PT1;
	}
	else if (state == STATE_PT1)
	{
		view->createing->graphicPolygon->points[1].x.setAttrAtFrame(worldPoint.x, view->frame);
		view->createing->graphicPolygon->points[1].y.setAttrAtFrame(worldPoint.y, view->frame);
		pDoc->grphics[view->createing->guid] = std::auto_ptr<Graphic>(view->createing);
		pDoc->layer.push_back(view->createing->guid);
		view->selectedGraphic.push_back(view->createing->guid);
		view->createing = nullptr;
		view->editTool = nullptr;
		state = STATE_NONE;

		//TODO: add history here
	}
	else
	{
		throw "unknown state";
	}
	return true;
}

bool GraphicToolAddLine::onMouseMove(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	if (state == STATE_PT1)
	{
		view->createing->graphicPolygon->points[1].x.setAttrAtFrame(worldPoint.x, view->frame);
		view->createing->graphicPolygon->points[1].y.setAttrAtFrame(worldPoint.y, view->frame);
	}

	return true;
}

bool GraphicToolAddLine::onRButtonDown(void *)
{
	if (state == STATE_PT1)
	{
		auto res = MessageBox(view->GetSafeHwnd(), L"cancel?", L"", MB_YESNO);
		if (res == IDYES)
		{
			delete view->createing;
			view->createing = nullptr;
			view->editTool = nullptr;
		}
		return true;
	}
	return false;
}

void GraphicToolAddLine::recoverHistory(GraphicHistory)
{
}

void GraphicToolAddLine::redoHistory(GraphicHistory)
{
}

void GraphicToolAddLine::reset()
{
	state = STATE_NONE;
}



GRA_TOOL_MSG_MAP_START(GraphicToolAddLine)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONDOWN, onLButtonDown)
GRA_TOOL_MSG_MAP_ON(WM_MOUSEMOVE, onMouseMove)
GRA_TOOL_MSG_MAP_ON(WM_RBUTTONDOWN, onRButtonDown)
GRA_TOOL_MSG_MAP_END

