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
		if (view->creating)
		{
			ASSERT(view->creating->type == GRA_POLYGON);
			view->creating->graphicPolygon->addPoint(view->frame, worldPoint.x, worldPoint.y, 0xFFFFFFFF, msg->press / 128.0f);
		}
		else
		{
			view->creating = new Graphic();
			view->creating->init(GRA_POLYGON, L"new ink");
			view->creating->graphicPolygon->addPoint(view->frame, worldPoint.x, worldPoint.y, 0xFFFFFFFF, msg->press / 128.0f);
			view->beginCreating();
		}
	}
	else
	{
		if (view->creating)
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