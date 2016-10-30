#pragma once
#include "GraphicTool.h"
class GraphicToolCameraZoomOut :
	public GraphicTool
{
public:
	GraphicToolCameraZoomOut();
	~GraphicToolCameraZoomOut();
	virtual void recoverHistory(GraphicHistory);
	virtual void redoHistory(GraphicHistory);
	virtual void reset();
	GRA_TOOL_MSG_MAP_HEAD
};

