#pragma once
#include "GraphicTool.h"
class GraphicToolRotate :
	public GraphicTool
{
public:
	GraphicToolRotate();
	~GraphicToolRotate();
	virtual void recoverHistory(GraphicHistory);
	virtual void redoHistory(GraphicHistory);
	virtual void reset();
	GRA_TOOL_MSG_MAP_HEAD
};

