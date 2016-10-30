#pragma once
#include "GraphicTool.h"
class GraphicToolAddCircle :
	public GraphicTool
{
public:
	GraphicToolAddCircle();
	~GraphicToolAddCircle();
	bool onLButtonDown(void *);
	bool onMouseMove(void *);
	virtual void recoverHistory(GraphicHistory);
	virtual void redoHistory(GraphicHistory);
	virtual void reset();
	GRA_TOOL_MSG_MAP_HEAD
};

