#include "stdafx.h"
#include "GraphicToolAddCircle.h"
#include "guiDoc.h"
#include "guiView.h"

GraphicToolAddCircle::GraphicToolAddCircle()
{
}


GraphicToolAddCircle::~GraphicToolAddCircle()
{
}

bool GraphicToolAddCircle::onLButtonDown(void *)
{
	return false;
}

bool GraphicToolAddCircle::onMouseMove(void *)
{
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
}


GRA_TOOL_MSG_MAP_START(GraphicToolAddCircle)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONDOWN, onLButtonDown)
GRA_TOOL_MSG_MAP_ON(WM_MOUSEMOVE, onMouseMove)
GRA_TOOL_MSG_MAP_END

