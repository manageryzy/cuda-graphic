#pragma once
#include "GraphicTool.h"
class GraphicToolCameraPan :
	public GraphicTool
{
public:
	GraphicToolCameraPan();
	~GraphicToolCameraPan();
	virtual void recoverHistory(GraphicHistory);
	virtual void redoHistory(GraphicHistory);
	virtual void reset();
	GRA_TOOL_MSG_MAP_HEAD
};

