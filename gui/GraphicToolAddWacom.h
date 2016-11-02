#pragma once
#include "GraphicTool.h"
class GraphicToolAddWacom :
	public GraphicTool
{
public:
	GraphicToolAddWacom();
	~GraphicToolAddWacom();
	bool onWtPacket(void *);
	virtual void recoverHistory(GraphicHistory);
	virtual void redoHistory(GraphicHistory);
	virtual void reset();
	GRA_TOOL_MSG_MAP_HEAD
};

