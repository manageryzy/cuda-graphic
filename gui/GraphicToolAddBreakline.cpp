#include "stdafx.h"
#include "GraphicToolAddBreakline.h"
#include "guiDoc.h"
#include "guiView.h"

GraphicToolAddBreakline::GraphicToolAddBreakline()
{
}


GraphicToolAddBreakline::~GraphicToolAddBreakline()
{
}

bool GraphicToolAddBreakline::onLButtonDown(void *)
{
	return false;
}

bool GraphicToolAddBreakline::onMouseMove(void *)
{
	return false;
}

bool GraphicToolAddBreakline::onLDoubleClick(void *)
{
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
}


GRA_TOOL_MSG_MAP_START(GraphicToolAddBreakline)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONDOWN, onLButtonDown)
GRA_TOOL_MSG_MAP_ON(WM_MOUSEMOVE, onMouseMove)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONDBLCLK,onLDoubleClick)
GRA_TOOL_MSG_MAP_END
