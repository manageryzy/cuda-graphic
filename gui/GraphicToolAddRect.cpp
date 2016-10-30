#include "stdafx.h"
#include "GraphicToolAddRect.h"
#include "guiDoc.h"
#include "guiView.h"


GraphicToolAddRect::GraphicToolAddRect()
{
}


GraphicToolAddRect::~GraphicToolAddRect()
{
}

bool GraphicToolAddRect::onLButtonDown(void *)
{
	return false;
}

bool GraphicToolAddRect::onMouseMove(void *)
{
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
}


GRA_TOOL_MSG_MAP_START(GraphicToolAddRect)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONDOWN, onLButtonDown)
GRA_TOOL_MSG_MAP_ON(WM_MOUSEMOVE, onMouseMove)
GRA_TOOL_MSG_MAP_END
