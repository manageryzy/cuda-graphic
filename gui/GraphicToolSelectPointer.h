#pragma once
#include "GraphicTool.h"
class GraphicToolSelectPointer :
	public GraphicTool
{
public:
	GraphicToolSelectPointer();
	~GraphicToolSelectPointer();
	virtual void recoverHistory(GraphicHistory);
	virtual void redoHistory(GraphicHistory);
	virtual void reset();
	GRA_TOOL_MSG_MAP_HEAD
};

