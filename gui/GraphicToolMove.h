#pragma once
#include "GraphicTool.h"
class GraphicToolMove :
	public GraphicTool
{
public:
	GraphicToolMove();
	~GraphicToolMove();
	bool onLButtonDown(void *);
	bool onLButtonUp(void *);
	bool onMouseMove(void *);
	virtual void recoverHistory(GraphicHistory);
	virtual void redoHistory(GraphicHistory);
	virtual void reset();
	void doMove(void *);
	inline bool busy() { return state!=0; };
	GRA_TOOL_MSG_MAP_HEAD
protected:
	int state = 0;
	std::pair<int, int> lastPos;
};

