#include "stdafx.h"
#include "GraphicToolAddTrangle.h"
#include "guiDoc.h"
#include "guiView.h"


GraphicToolAddTrangle::GraphicToolAddTrangle()
{
}


GraphicToolAddTrangle::~GraphicToolAddTrangle()
{
}

bool GraphicToolAddTrangle::onLButtonDown(void *)
{
	return false;
}

bool GraphicToolAddTrangle::onMouseMove(void *)
{
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
}




GRA_TOOL_MSG_MAP_START(GraphicToolAddTrangle)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONDOWN, onLButtonDown)
GRA_TOOL_MSG_MAP_ON(WM_MOUSEMOVE, onMouseMove)
GRA_TOOL_MSG_MAP_END
