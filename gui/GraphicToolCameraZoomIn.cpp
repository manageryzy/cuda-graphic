#include "stdafx.h"
#include "GraphicToolCameraZoomIn.h"
#include "guiDoc.h"
#include "guiView.h"

GraphicToolCameraZoomIn::GraphicToolCameraZoomIn()
{
}


GraphicToolCameraZoomIn::~GraphicToolCameraZoomIn()
{
}

void GraphicToolCameraZoomIn::recoverHistory(GraphicHistory)
{
}

void GraphicToolCameraZoomIn::redoHistory(GraphicHistory)
{
}

void GraphicToolCameraZoomIn::reset()
{
}

void GraphicToolCameraZoomIn::zoomIn()
{
	GRA_INIT_DOC;
	camera->scale *= 2;
}

GRA_TOOL_MSG_MAP_START(GraphicToolCameraZoomIn)
GRA_TOOL_MSG_MAP_END