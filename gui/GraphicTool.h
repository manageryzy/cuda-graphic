#pragma once

#include "GraphicHistory.h"
#include <memory>
#include <map>
#include <vector>



#define GRA_TOOL_MSG_MAP_HEAD bool on(int msg, void * data);

#define GRA_TOOL_MSG_MAP_START(x) \
bool  x ## ::on(int msg, void * data) { switch (msg) {

#define GRA_TOOL_MSG_MAP_ON(msg,deal) \
case msg : return deal ## (data); break;


#define GRA_TOOL_MSG_MAP_END default:return false;}}

#define GRA_INIT_DOC \
CguiDoc* pDoc = view->GetDocument();\
ASSERT_VALID(pDoc);\
ASSERT(pDoc->cameras.find(pDoc->currentCamera) != pDoc->cameras.end());\
GraphicCamera * camera = pDoc->cameras[pDoc->currentCamera].get();

#define GRA_INIT_CAMERA \
CPoint * pt = (CPoint*)point;\
auto worldPoint = camera->toWorld((float)pt->x, (float)pt->y);

typedef struct GraphicToolMsgMouseStruct{
	CPoint pt;

	GraphicToolMsgMouseStruct(CPoint p){pt = p;}
} GraphicToolMsgMouse;

typedef struct GraphicToolMsgTabletStruct {
	CPoint pt;
	int button;
	int press;

	GraphicToolMsgTabletStruct(int x, int y, int button, int press) { pt.x = x; pt.y = y; this->button = button; this->press = press; }
} GraphicToolMsgTablet;

class CguiView;

class GraphicTool
{
public:
	GraphicTool();
	virtual ~GraphicTool();
	virtual void recoverHistory(GraphicHistory) = 0;
	virtual void redoHistory(GraphicHistory) = 0;
	virtual bool on(int msg, void * data) = 0;
	virtual void reset() = 0;

	void bind(CguiView * v);
protected:
	CguiView * view = nullptr;
};

