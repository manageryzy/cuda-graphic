#pragma once
#include "GraphicTool.h"

class GraphicCamera;

class GraphicToolRotate :
	public GraphicTool
{
public:
	GraphicToolRotate();
	~GraphicToolRotate();
	bool onLButtonDown(void *);
	bool onMouseMove(void *);
	bool onLButtonUp(void *);
	virtual void recoverHistory(GraphicHistory);
	virtual void redoHistory(GraphicHistory);
	virtual void reset();
	void doRotate(void *);
	inline bool isBusy() { return rotateCamera != nullptr; }
	float getAngle(D2D1_POINT_2F);
	float getAngle(float x, float y);
	GRA_TOOL_MSG_MAP_HEAD
protected:
	GraphicCamera * rotateCamera = nullptr;
	float angle1;
	int state = 0;
};

