#include "stdafx.h"
#include "GraphicToolCameraZoomOut.h"
#include "guiDoc.h"
#include "guiView.h"


GraphicToolCameraZoomOut::GraphicToolCameraZoomOut()
{
}


GraphicToolCameraZoomOut::~GraphicToolCameraZoomOut()
{
}

void GraphicToolCameraZoomOut::recoverHistory(GraphicHistory)
{
}

void GraphicToolCameraZoomOut::redoHistory(GraphicHistory)
{
}

void GraphicToolCameraZoomOut::reset()
{
}

void GraphicToolCameraZoomOut::zoomOut()
{
	GRA_INIT_DOC;
	camera->scale /= 2;
	view->d2dRender->flush();
}

GRA_TOOL_MSG_MAP_START(GraphicToolCameraZoomOut)
GRA_TOOL_MSG_MAP_END