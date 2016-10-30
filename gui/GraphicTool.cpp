#include "stdafx.h"
#define USE_GRA_TOOL
#include "GraphicToolAll.h"
#include "guiDoc.h"
#include "guiView.h"

GraphicTool::GraphicTool()
{
}


GraphicTool::~GraphicTool()
{
}

void GraphicTool::bind(CguiView * v)
{
	view = v;
	this->reset();
}

