#include "stdafx.h"
#include "GraphicToolCameraPan.h"
#include "guiDoc.h"
#include "guiView.h"


GraphicToolCameraPan::GraphicToolCameraPan()
{
}


GraphicToolCameraPan::~GraphicToolCameraPan()
{
}

bool GraphicToolCameraPan::onLButtonDown(void * point)
{
	startMove(point);
	return true;
}

bool GraphicToolCameraPan::onLButtonUp(void *)
{
	endMove();
	return true;
}

bool GraphicToolCameraPan::onMouseMove(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	if (startCamera != nullptr)
	{
		worldPoint = startCamera->toWorld(pt->x, pt->y);
		auto deltaX = worldPoint.x - startX;
		auto deltaY = worldPoint.y - startY;

		camera->x = startCamera->x - deltaX;
		camera->y = startCamera->y - deltaY;
	}

	view->d2dRender->flush();

	return true;
}

void GraphicToolCameraPan::recoverHistory(GraphicHistory)
{
}

void GraphicToolCameraPan::redoHistory(GraphicHistory)
{
}

void GraphicToolCameraPan::reset()
{
	endMove();
}

void GraphicToolCameraPan::startMove(void * point)
{
	if (!startCamera)
	{
		GRA_INIT_DOC;
		GRA_INIT_CAMERA;

		startX = worldPoint.x;
		startY = worldPoint.y;
		startCamera = new GraphicCamera(*camera);
	}
	
}

void GraphicToolCameraPan::endMove()
{
	if(startCamera)
		delete startCamera;
	startCamera = nullptr;
}

GRA_TOOL_MSG_MAP_START(GraphicToolCameraPan)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONDOWN, onLButtonDown)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONUP, onLButtonUp)
GRA_TOOL_MSG_MAP_ON(WM_MOUSEMOVE, onMouseMove)
GRA_TOOL_MSG_MAP_END