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

	cache = new CUDARenderCache(this);
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
	startPos[0] = 0;

	for (auto & guid : doc->layer)
	{
		if (selected->find(guid) != selected->end())
			continue;

		auto gra = doc->grphics[guid]->atFrame(frame);
		for (int i = 0; i < gra.size(); i++)
		{
			points[curStartPos] = gra.at(i);
			curStartPos++;
		}

		curGraphic++;
		startPos[curGraphic] = curStartPos;
	}

	

	render(output, height, width, camX, camY, scaleX, scaleY, graphicCount, pointCount, points, fillColor, startPos);

	delete[] points;
	delete[] fillColor;
	delete[] startPos;
}

CUDARenderCache * CUDARender::getCache()
{
	return cache;
}

void CUDARenderCache::alloBuffer(int size)
{
	buffer = new DWORD[size];
}

void CUDARenderCache::freeBuffer()
{
	delete[] buffer;
	buffer = nullptr;
}

CUDARenderCache::CUDARenderCache(CUDARender * renderer)
{
	this->renderer = renderer;
}

void CUDARenderCache::change()
{
	cached = false;
	freeBuffer();
}

void CUDARenderCache::change(int frame)
{
	this->frame = frame;
	cached = false;
	freeBuffer();
}

bool CUDARenderCache::isCached(int frame)
{
	return cached&(frame == this->frame);
}

DWORD * CUDARenderCache::getImage(int height, int width, int frame, float camX, float camY, float scaleX, float scaleY, CguiDoc * doc, std::set<GUID_> * selected)
{
	if (!isCached(frame))
	{
		if (buffer == nullptr)
			alloBuffer(height * width);
		renderer->renderScene(buffer, height, width, frame, camX, camY, scaleX, scaleY, doc, selected);

		cached = true;
		this->frame = frame;
	}

	return buffer;
}
