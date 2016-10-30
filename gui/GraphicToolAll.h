#pragma once

#ifdef USE_GRA_TOOL
#include "GraphicToolAddBezier.h"
#include "GraphicToolAddBreakline.h"
#include "GraphicToolAddCircle.h"
#include "GraphicToolAddLine.h"
#include "GraphicToolAddRect.h"
#include "GraphicToolAddTrangle.h"
#include "GraphicToolAddWacom.h"
#include "GraphicToolCameraPan.h"
#include "GraphicToolCameraZoomIn.h"
#include "GraphicToolCameraZoomOut.h"
#include "GraphicToolMove.h"
#include "GraphicToolRotate.h"
#include "GraphicToolScale.h"
#include "GraphicToolSelecRect.h"
#include "GraphicToolSelectPointer.h"
#else
class GraphicTool;
class GraphicToolAddBezier;
class GraphicToolAddBreakline;
class GraphicToolAddCircle;
class GraphicToolAddLine;
class GraphicToolAddRect;
class GraphicToolAddTrangle;
class GraphicToolAddWacom;
class GraphicToolCameraPan;
class GraphicToolCameraZoomIn;
class GraphicToolCameraZoomOut;
class GraphicToolMove;
class GraphicToolRotate;
class GraphicToolScale;
class GraphicToolSelecRect;
class GraphicToolSelectPointer;
#endif // USE_GRA_TOOL

