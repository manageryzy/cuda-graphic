#pragma once
#include "GraphicTool.h"
class GraphicToolSelectPointer :
	public GraphicTool
{
	float inline GraphicToolSelectPointer::pointToSegDist(float x, float y, float x1, float y1, float x2, float y2);
public:
	GraphicToolSelectPointer();
	~GraphicToolSelectPointer();
	bool onLButtonDown(void *);
	virtual void recoverHistory(GraphicHistory);
	virtual void redoHistory(GraphicHistory);
	virtual void reset();
	GRA_TOOL_MSG_MAP_HEAD
};

