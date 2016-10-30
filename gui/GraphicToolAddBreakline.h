#pragma once
#include "GraphicTool.h"
class GraphicToolAddBreakline :
	public GraphicTool
{
public:
	GraphicToolAddBreakline();
	~GraphicToolAddBreakline();
	bool onLButtonDown(void *);
	bool onMouseMove(void *);
	bool onLDoubleClick(void *);
	virtual void recoverHistory(GraphicHistory);
	virtual void redoHistory(GraphicHistory);
	virtual void reset();
	GRA_TOOL_MSG_MAP_HEAD
};

