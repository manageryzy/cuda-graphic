#pragma once
#include "GraphicTool.h"
class GraphicToolAddTrangle :
	public GraphicTool
{
public:
	GraphicToolAddTrangle();
	~GraphicToolAddTrangle();
	bool onLButtonDown(void *);
	bool onMouseMove(void *);
	virtual void recoverHistory(GraphicHistory);
	virtual void redoHistory(GraphicHistory);
	virtual void reset();
	GRA_TOOL_MSG_MAP_HEAD
};

