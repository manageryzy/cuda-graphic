#include "stdafx.h"
#include "GraphicToolMove.h"
#include "guiDoc.h"
#include "guiView.h"

GraphicToolMove::GraphicToolMove()
{
}


GraphicToolMove::~GraphicToolMove()
{
}

bool GraphicToolMove::onLButtonDown(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	if (!state)
	{
		state = 1;
		lastPos.first = worldPoint.x;
		lastPos.second = worldPoint.y;
	}

	return true;
}

bool GraphicToolMove::onLButtonUp(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	if (state)
	{
		doMove(point);
		state = 0;
	}

	return true;
}

bool GraphicToolMove::onMouseMove(void * point)
{
	doMove(point);

	return true;
}

void GraphicToolMove::recoverHistory(GraphicHistory)
{
}

void GraphicToolMove::redoHistory(GraphicHistory)
{
}

void GraphicToolMove::reset()
{
	state = 0;
}

void GraphicToolMove::doMove(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	if (state)
	{
		auto deltaX = lastPos.first - worldPoint.x;
		auto deltaY = lastPos.second - worldPoint.y;

		if (view->selectMode == GUI_SELECT_MODE_OBJECT)
		{
			for (auto & guid : view->selectedGraphic)
			{
				pDoc->graphics[guid]->move(-deltaX, -deltaY, view->frame);
			}
		}
	}

	lastPos.first = worldPoint.x;
	lastPos.second = worldPoint.y;
}

GRA_TOOL_MSG_MAP_START(GraphicToolMove)
GRA_TOOL_MSG_MAP_ON(WM_MOUSEMOVE, onMouseMove)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONDOWN, onLButtonDown)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONUP, onLButtonUp)
GRA_TOOL_MSG_MAP_END