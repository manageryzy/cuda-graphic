#pragma once
#include "GraphicTool.h"

class GraphicCamera;

class GraphicToolCameraPan :
	public GraphicTool
{
public:
	GraphicToolCameraPan();
	~GraphicToolCameraPan();
	bool onLButtonDown(void *);
	bool onLButtonUp(void *);
	bool onMouseMove(void *);
	virtual void recoverHistory(GraphicHistory);
	virtual void redoHistory(GraphicHistory);
	virtual void reset();
	void startMove(void *);
	void endMove();
	GRA_TOOL_MSG_MAP_HEAD
protected:
	GraphicCamera * startCamera = nullptr;
	int startX = 0,startY = 0;
};

