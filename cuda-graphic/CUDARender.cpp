#define __USE_CUDA_HEAD__
#include "CUDARender.hpp"
#include <exception>
#include "../gui/stdafx.h"
#include "../gui/guiDoc.h"
#include "head.cu"

using namespace CUDARenderCore;

CUDARender * CUDARender::cudaRender = nullptr;

CUDARender::CUDARender()
{
	if (!init())
	{
		throw std::exception("cuda init fail");
	}
}

CUDARender * CUDARender::getCudaRender()
{
	
	if (cudaRender == nullptr)
		cudaRender = new CUDARender();
	
	
	return cudaRender;
}

void CUDARender::renderScene(DWORD * output, int height, int width, int frame, float camX, float camY, float scaleX, float scaleY, CguiDoc * doc, std::set<GUID_> * selected)
{
	int pointCount = 0;
	int graphicCount = 0;
	for (auto & guid : doc->layer)
	{
		if (selected->find(guid) != selected->end())
			continue;
		pointCount += doc->grphics[guid]->pointCount();
		graphicCount++;
	}

	GraphicBasicPoint * points = new GraphicBasicPoint[pointCount+16];
	DWORD * fillColor = new DWORD[graphicCount+16];
	int * startPos = new int[graphicCount+16];

	int curStartPos = 0;
	int curGraphic = 0;
	for (auto & guid : doc->layer)
	{
		if (selected->find(guid) != selected->end())
			continue;

		auto & gra = doc->grphics[guid]->atFrame(frame);
		for (int i = 0; i < gra.size(); i++)
		{
			points[curStartPos] = gra.at(i);
			curStartPos++;
		}

		startPos[curGraphic] = curStartPos;
		curGraphic++;
	}

	render(output, height, width, camX, camY, scaleX, scaleY, graphicCount, pointCount, points, fillColor, startPos);

	delete points;
	delete fillColor;
	delete startPos;
}


