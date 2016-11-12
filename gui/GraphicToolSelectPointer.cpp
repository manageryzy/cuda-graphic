#include "stdafx.h"
#include "GraphicToolSelectPointer.h"
#include "guiDoc.h"
#include "guiView.h"

GraphicToolSelectPointer::GraphicToolSelectPointer()
{
}


GraphicToolSelectPointer::~GraphicToolSelectPointer()
{
}

bool GraphicToolSelectPointer::onLButtonDown(void * point)
{
	GRA_INIT_DOC;
	GRA_INIT_CAMERA;

	view->selectedGraphic.clear();
	view->selectedPoint.clear();

	if (view->selectMode == GUI_SELECT_MODE_OBJECT)
	{
		for (auto & guid : pDoc->layer)
		{
			auto g = pDoc->graphics[guid].get();
			switch (g->type)
			{
			case GRA_POLYGON:
			{
				auto ptList = g->graphicPolygon->atFrame(view->frame);
				if (ptList.size() < 2)
					continue;
				auto lastPoint = ptList.begin();
				auto range = 20 / camera->scale;
				for (auto i = ptList.begin() + 1; i < ptList.end(); ++i)
				{
					auto dist = pointToSegDist(
						worldPoint.x,
						worldPoint.y,
						lastPoint->x,
						lastPoint->y,
						i->x,
						i->y
					);

					if (dist<range && dist > -range)
					{
						view->selectedGraphic.insert(guid);
						break;
					}
				}
				break;
			}		
			case GRA_CIRCLE:
			{
				auto r = sqrtf((worldPoint.x - g->graphicCircle->x.atFrame(view->frame)) *
					(worldPoint.x - g->graphicCircle->x.atFrame(view->frame)) +
					(worldPoint.y - g->graphicCircle->y.atFrame(view->frame)) *
					(worldPoint.y - g->graphicCircle->y.atFrame(view->frame))
				) - g->graphicCircle->r.atFrame(view->frame);

				r *= camera->scale;

				if (r<20 && r>-20)
				{
					view->selectedGraphic.insert(guid);
				}
				break;
			}
				
			case GRA_BEZIER:
			{
				auto ptList = g->graphicBezier->atFrame(view->frame);
				if (ptList.size() < 2)
					continue;
				auto lastPoint = ptList.begin();
				auto range = 20 / camera->scale;
				for (auto i = ptList.begin() + 1; i < ptList.end(); ++i)
				{
					auto dist = pointToSegDist(
						worldPoint.x,
						worldPoint.y,
						lastPoint->x,
						lastPoint->y,
						i->x,
						i->y
					);

					if (dist<range && dist > -range)
					{
						view->selectedGraphic.insert(guid);
						break;
					}
				}
				break;
			}
				
			default:
				break;
			}
		}

		if(view->selectedGraphic.size()>0)
		{
			if (view->editTool == nullptr)
				view->editTool = (GraphicTool *)view->toolMove;
		}
	}
	else if (view->selectMode == GUI_SELECT_MODE_VERTEX)
	{
		//TODO
	}

	view->flush();

	return false;
}

void GraphicToolSelectPointer::recoverHistory(GraphicHistory)
{
}

void GraphicToolSelectPointer::redoHistory(GraphicHistory)
{
}

void GraphicToolSelectPointer::reset()
{
}

float GraphicToolSelectPointer::pointToSegDist(float x, float y, float x1, float y1, float x2, float y2)
{
	float cross = (x2 - x1) * (x - x1) + (y2 - y1) * (y - y1);
	if (cross <= 0) return sqrtf((x - x1) * (x - x1) + (y - y1) * (y - y1));

	float d2 = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
	if (cross >= d2) return sqrtf((x - x2) * (x - x2) + (y - y2) * (y - y2));

	float r = cross / d2;
	float px = x1 + (x2 - x1) * r;
	float py = y1 + (y2 - y1) * r;

	return sqrtf((x - px) * (x - px) + (y - py) * (y - py));
}

GRA_TOOL_MSG_MAP_START(GraphicToolSelectPointer)
GRA_TOOL_MSG_MAP_ON(WM_LBUTTONDOWN, onLButtonDown)
GRA_TOOL_MSG_MAP_END