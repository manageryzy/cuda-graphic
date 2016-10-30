#pragma once
#include "GraphicTool.h"
class GraphicToolMove :
	public GraphicTool
{
public:
	GraphicToolMove();
	~GraphicToolMove();
	virtual void recoverHistory(GraphicHistory);
	virtual void redoHistory(GraphicHistory);
	virtual void reset();
	GRA_TOOL_MSG_MAP_HEAD
};

