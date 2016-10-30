#pragma once
#include "GraphicTool.h"
class GraphicToolAddWacom :
	public GraphicTool
{
public:
	GraphicToolAddWacom();
	~GraphicToolAddWacom();
	virtual void recoverHistory(GraphicHistory);
	virtual void redoHistory(GraphicHistory);
	virtual void reset();
	GRA_TOOL_MSG_MAP_HEAD
};

