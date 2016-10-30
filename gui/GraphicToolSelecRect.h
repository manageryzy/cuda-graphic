#pragma once
#include "GraphicTool.h"
class GraphicToolSelecRect :
	public GraphicTool
{
public:
	GraphicToolSelecRect();
	~GraphicToolSelecRect();
	virtual void recoverHistory(GraphicHistory);
	virtual void redoHistory(GraphicHistory);
	virtual void reset();
	GRA_TOOL_MSG_MAP_HEAD
};

