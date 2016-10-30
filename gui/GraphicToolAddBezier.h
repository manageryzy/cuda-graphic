#pragma once
#include "GraphicTool.h"
class GraphicToolAddBezier :
	public GraphicTool
{
public:
	GraphicToolAddBezier();
	~GraphicToolAddBezier();
	virtual void recoverHistory(GraphicHistory);
	virtual void redoHistory(GraphicHistory);
	virtual void reset();
	GRA_TOOL_MSG_MAP_HEAD
};

