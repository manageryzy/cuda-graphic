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
	bool onRButtonUp(void *);
	bool onESC(void *);
	virtual void recoverHistory(GraphicHistory);
	virtual void redoHistory(GraphicHistory);
	virtual void reset();
	GRA_TOOL_MSG_MAP_HEAD
protected:
	int state = 0;
	void cancel();
};

