#include "stdafx.h"
#include "GraphicToolAddWacom.h"
#include "guiDoc.h"
#include "guiView.h"


GraphicToolAddWacom::GraphicToolAddWacom()
{
}


GraphicToolAddWacom::~GraphicToolAddWacom()
{
}

bool GraphicToolAddWacom::onWtPacket(void * stru)
{
	GraphicToolMsgTablet * msg = (GraphicToolMsgTablet *) stru;

	GRA_INIT_DOC;
	auto worldPoint = camera->toWorld((float)msg->pt.x, (float)msg->pt.y);

	if (msg->button)
	{
		if (view->createing)
		{
			ASSERT(view->createing->type == GRA_POLYGON);
			view->createing->graphicPolygon->addPoint(view->frame, worldPoint.x, worldPoint.y, 0xFFFFFFFF, msg->press / 128.0f);
		}
		else
		{
			view->createing = new Graphic();
			view->createing->init(GRA_POLYGON, L"new ink");
			view->createing->graphicPolygon->addPoint(view->frame, worldPoint.x, worldPoint.y, 0xFFFFFFFF, msg->press / 128.0f);
			view->beginCreating();
		}
	}
	else
	{
		if (view->createing)
		{
			view->endCreating(false);
		}
	}


	return true;
}

void GraphicToolAddWacom::recoverHistory(GraphicHistory)
{
}

void GraphicToolAddWacom::redoHistory(GraphicHistory)
{
}

void GraphicToolAddWacom::reset()
{
}

GRA_TOOL_MSG_MAP_START(GraphicToolAddWacom)
GRA_TOOL_MSG_MAP_ON(WT_PACKET,onWtPacket)
GRA_TOOL_MSG_MAP_END