#pragma once
#include "GraphicTool.h"

class GraphicCamera;

class GraphicToolScale :
	public GraphicTool
{
public:
	GraphicToolScale();
	~GraphicToolScale();
	bool onLButtonDown(void *);
	bool onMouseMove(void *);
	bool onLButtonUp(void *);
	virtual void recoverHistory(GraphicHistory);
	virtual void redoHistory(GraphicHistory);
	virtual void reset();
	void doScale(void *);
	inline bool isBusy() { return scaleCamera != nullptr; }
	GRA_TOOL_MSG_MAP_HEAD
protected:
	GraphicCamera * scaleCamera = nullptr;
	float dist1;
	int state = 0;
};

