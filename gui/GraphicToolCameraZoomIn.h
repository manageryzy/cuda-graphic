#pragma once
#include "GraphicTool.h"
class GraphicToolCameraZoomIn :
	public GraphicTool
{
public:
	GraphicToolCameraZoomIn();
	~GraphicToolCameraZoomIn();
	virtual void recoverHistory(GraphicHistory);
	virtual void redoHistory(GraphicHistory);
	virtual void reset();
	GRA_TOOL_MSG_MAP_HEAD
};

