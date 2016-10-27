// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// guiView.cpp : implementation of the CguiView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "gui.h"
#endif

#include <memory>

#include "guiDoc.h"
#include "guiView.h"
char * gpszProgramName = "CUDAX";

#include <d2d1.h>
#include <d3d11_1.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CguiView

IMPLEMENT_DYNCREATE(CguiView, CView)

BEGIN_MESSAGE_MAP(CguiView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BTN_ADD_LINE, &CguiView::OnBtnAddLine)
	ON_COMMAND(ID_BTN_ADD_BREAK_LINE, &CguiView::OnBtnAddBreakLine)
	ON_COMMAND(ID_BTN_ADD_TRIANGLE, &CguiView::OnBtnAddTriangle)
	ON_COMMAND(ID_BTN_ADD_RECTANGLE, &CguiView::OnBtnAddRectangle)
	ON_COMMAND(ID_BTN_ADD_CIRCLE, &CguiView::OnBtnAddCircle)
	ON_COMMAND(ID_BTN_ADD_BEZIER, &CguiView::OnBtnAddBezier)
	ON_COMMAND(ID_BTN_ADD_CAMERA, &CguiView::OnBtnAddCamera)
	ON_COMMAND(ID_BTN_MOVE, &CguiView::OnBtnMove)
	ON_COMMAND(ID_BTN_SCALE, &CguiView::OnBtnScale)
	ON_COMMAND(ID_BTN_ROTATE, &CguiView::OnBtnRotate)
	ON_COMMAND(ID_BTN_TO_POLYGON, &CguiView::OnBtnToPolygon)
	ON_COMMAND(ID_BTN_REMOVE, &CguiView::OnBtnRemove)
	ON_COMMAND(ID_BTN_CHOOSE_CAMERA, &CguiView::OnBtnChooseCamera)
	ON_COMMAND(ID_BTN_ZOOM_IN, &CguiView::OnBtnZoomIn)
	ON_COMMAND(ID_BTN_ZOOM_OUT, &CguiView::OnBtnZoomOut)
	ON_COMMAND(ID_PAN, &CguiView::OnPan)
	ON_COMMAND(ID_FRAME_NEXT, &CguiView::OnFrameNext)
	ON_COMMAND(ID_FRAME_PREV, &CguiView::OnFramePrev)
	ON_COMMAND(ID_BTN_RENDER_IMG, &CguiView::OnBtnRenderImg)
	ON_COMMAND(ID_BTN_RENDER_SEQUENCE, &CguiView::OnBtnRenderSequence)
	ON_COMMAND(ID_BTN_SEL_OBJ, &CguiView::OnBtnSelObj)
	ON_COMMAND(ID_BTN_SEL_VERTEX, &CguiView::OnBtnSelVertex)
	ON_COMMAND(ID_BTN_SEL_CLICK, &CguiView::OnBtnSelClick)
	ON_COMMAND(ID_BTN_SEL_RECT, &CguiView::OnBtnSelRect)
	ON_COMMAND(ID_BTN_MOVE_UP, &CguiView::OnBtnMoveUp)
	ON_COMMAND(ID_BTN_MOVE_DOWN, &CguiView::OnBtnMoveDown)
	ON_UPDATE_COMMAND_UI(ID_BTN_SEL_OBJ, &CguiView::OnUpdateBtnSelObj)
	ON_UPDATE_COMMAND_UI(ID_BTN_SEL_VERTEX, &CguiView::OnUpdateBtnSelVertex)
	ON_UPDATE_COMMAND_UI(ID_BTN_SEL_CLICK, &CguiView::OnUpdateBtnSelClick)
	ON_UPDATE_COMMAND_UI(ID_BTN_SEL_RECT, &CguiView::OnUpdateBtnSelRect)
	ON_UPDATE_COMMAND_UI(ID_BTN_ADD_LINE, &CguiView::OnUpdateBtnAddLine)
	ON_UPDATE_COMMAND_UI(ID_BTN_ADD_BREAK_LINE, &CguiView::OnUpdateBtnAddBreakLine)
	ON_UPDATE_COMMAND_UI(ID_BTN_ADD_TRIANGLE, &CguiView::OnUpdateBtnAddTriangle)
	ON_UPDATE_COMMAND_UI(ID_BTN_ADD_RECTANGLE, &CguiView::OnUpdateBtnAddRectangle)
	ON_UPDATE_COMMAND_UI(ID_BTN_ADD_CIRCLE, &CguiView::OnUpdateBtnAddCircle)
	ON_UPDATE_COMMAND_UI(ID_BTN_ADD_BEZIER, &CguiView::OnUpdateBtnAddBezier)
	ON_UPDATE_COMMAND_UI(ID_BTN_MOVE, &CguiView::OnUpdateBtnMove)
	ON_UPDATE_COMMAND_UI(ID_BTN_SCALE, &CguiView::OnUpdateBtnScale)
	ON_UPDATE_COMMAND_UI(ID_BTN_ROTATE, &CguiView::OnUpdateBtnRotate)
	ON_UPDATE_COMMAND_UI(ID_BTN_MOVE_UP, &CguiView::OnUpdateBtnMoveUp)
	ON_UPDATE_COMMAND_UI(ID_BTN_MOVE_DOWN, &CguiView::OnUpdateBtnMoveDown)
	ON_UPDATE_COMMAND_UI(ID_BTN_TO_POLYGON, &CguiView::OnUpdateBtnToPolygon)
	ON_UPDATE_COMMAND_UI(ID_BTN_REMOVE, &CguiView::OnUpdateBtnRemove)
	ON_UPDATE_COMMAND_UI(ID_FRAME_NEXT, &CguiView::OnUpdateFrameNext)
	ON_UPDATE_COMMAND_UI(ID_FRAME_PREV, &CguiView::OnUpdateFramePrev)
	ON_MESSAGE(WM_VIEW_RESET, &CguiView::OnViewReset)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
	ON_MESSAGE(WT_PACKET, &CguiView::OnWtPacket)
	ON_COMMAND(ID_BTN_ADD_WACOM, &CguiView::OnBtnAddWacom)
	ON_UPDATE_COMMAND_UI(ID_BTN_ADD_WACOM, &CguiView::OnUpdateBtnAddWacom)
	ON_COMMAND(ID_SELECT_ALL, &CguiView::OnSelectAll)
	ON_UPDATE_COMMAND_UI(ID_PAN, &CguiView::OnUpdatePan)
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CguiView construction/destruction

CguiView::CguiView()
{
	state = GUI_STATE_NONE;
	selectMode = GUI_SELECT_MODE_OBJECT;
	selectTool = GUI_SELECT_TOOL_POINTER;
	editTool = GUI_TOOL_NONE;
	cameraTool = GUI_TOOL_NONE;

	frame = 0;

	selectedGraphic.clear();
	selectedPoint.clear();

	lastFrame = std::chrono::steady_clock::now();

	HRESULT hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&pD2DFactory
	);
	if (hr != S_OK)throw hr;
	

	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(pDWriteFactory),
		reinterpret_cast<IUnknown **>(&pDWriteFactory)
	);
	if (hr != S_OK)throw hr;

	hr = pDWriteFactory->CreateTextFormat(
		L"Verdana",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		12,
		L"", //locale
		&pTextFormat
	);
	if (hr != S_OK)throw hr;

	pWTMutex = new CMutex(TRUE, NULL, NULL);
	hCtx = 0;
}

CguiView::~CguiView()
{
	SafeRelease(&pD2DFactory);
	SafeRelease(&pDWriteFactory);
	SafeRelease(&pTextFormat);

	delete pWTMutex;
	if (hCtx)
	{
		gpWTClose(hCtx);
	}
}

BOOL CguiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CguiView drawing

void CguiView::OnDraw(CDC* /*pDC*/)
{
	drawed = true;
	CguiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (!pDoc->inited)
		return;

	RECT rc;
	GetClientRect(&rc);

	ID2D1HwndRenderTarget* pRT = NULL;
	HRESULT hr = pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			GetSafeHwnd(),
			D2D1::SizeU(
				rc.right - rc.left,
				rc.bottom - rc.top)
		),
		&pRT
	);

	ID2D1SolidColorBrush* pGrayBrush = NULL;
	if (SUCCEEDED(hr))
	{

		pRT->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Gray),
			&pGrayBrush
		);
	}

	ID2D1StrokeStyle * style = NULL;
	if (SUCCEEDED(hr))
	{
		pD2DFactory->CreateStrokeStyle(
			D2D1::StrokeStyleProperties(
				D2D1_CAP_STYLE_ROUND,
				D2D1_CAP_STYLE_ROUND,
				D2D1_CAP_STYLE_ROUND
			),
			0, 0, &style
		);
	}

	ID2D1SolidColorBrush* pRedBrush = NULL;
	if (SUCCEEDED(hr))
	{

		pRT->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Red),
			&pRedBrush
		);
	}

	ID2D1SolidColorBrush* pWhiteBrush = NULL;
	if (SUCCEEDED(hr))
	{

		pRT->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::White),
			&pWhiteBrush
		);
	}


	ID2D1SolidColorBrush* pGreenBrush = NULL;
	if (SUCCEEDED(hr))
	{
		pRT->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Green),
			&pGreenBrush
		);
	}

	ASSERT(pDoc != nullptr);
	ASSERT(pDoc->cameras.find(pDoc->currentCamera) != pDoc->cameras.end());
	GraphicCamera * camera = pDoc->cameras[pDoc->currentCamera].get();
	
	pRT->BeginDraw();
	pRT->Clear();
	// begin draw
	
	if (selectMode == GUI_SELECT_MODE_OBJECT)
	{
		for (auto & guid : selectedGraphic)
		{
			ASSERT(pDoc->grphics.find(guid) != pDoc->grphics.end());
			ASSERT(pDoc->grphics[guid].get() != nullptr);

			Graphic * g = pDoc->grphics[guid].get();
			switch (g->type)
			{
			case GRA_POLYGON:
				{
					// try to render polygon here
					ASSERT(g->graphicPolygon.get() != nullptr);
					auto polygon = g->graphicPolygon.get();
					auto ptList = polygon->atFrame(frame);
					if (ptList.size() < 2)
						continue;
					auto lastPoint = ptList.begin();
					for (auto i = ptList.begin()+1; i < ptList.end(); ++i)
					{
						auto pt1 = camera->toCameraView(lastPoint->x, lastPoint->y);
						auto pt2 = camera->toCameraView(i->x, i->y);

						pRT->DrawLine(pt1, pt2, pWhiteBrush, (i->width + lastPoint->width) / 2, style);

						lastPoint = i;
					}
				}
				break;
			case GRA_CIRCLE:
				{
					// try to render circle here
					ASSERT(g->graphicCircle.get() != nullptr);
					auto circle = g->graphicCircle.get();
					auto pt = camera->toCameraView(circle->x.atFrame(frame), circle->y.atFrame(frame));
					auto r = camera->scale * circle->r.atFrame(frame);
					D2D1_ELLIPSE eclipse;
					eclipse.point = pt;
					eclipse.radiusX = r;
					eclipse.radiusY = r;
					pRT->DrawEllipse(eclipse, pWhiteBrush, circle->width.atFrame(frame), style);
				}
				break;
			case GRA_BEZIER:
				// try to render bezier here
				break;
			case GRA_NONE:
				break;
			default:
				throw "unkown type";
			}	
		}
		
	}
	else if (selectMode == GUI_SELECT_MODE_VERTEX)
	{
		for (auto & pt : selectedPoint)
		{
			
		}
	}
	

	// end draw
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	int fps = (int)(1000000.0 / (std::chrono::duration_cast<std::chrono::microseconds>(now - lastFrame).count()));
	lastFrame = now;
	CString fpsStr;
	fpsStr.Format(L"FPS:%d ", fps);
	pRT->DrawTextW(fpsStr, fpsStr.GetLength(), pTextFormat, D2D1::RectF(0, 0, 1000, 30), pGreenBrush);
	hr = pRT->EndDraw();
	
	SafeRelease(&pRT);
	SafeRelease(&pGrayBrush);
	SafeRelease(&pGreenBrush);
	SafeRelease(&pRedBrush);
	SafeRelease(&pWhiteBrush);
	SafeRelease(&style);
}

void CguiView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CguiView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CguiView diagnostics

#ifdef _DEBUG
void CguiView::AssertValid() const
{
	CView::AssertValid();
}

void CguiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CguiDoc* CguiView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CguiDoc)));
	return (CguiDoc*)m_pDocument;
}
#endif //_DEBUG


// CguiView message handlers


void CguiView::OnBtnAddLine()
{
	editTool = GUI_TOOL_ADD_LINE;
}


void CguiView::OnBtnAddBreakLine()
{
	editTool = GUI_TOOL_ADD_BREAKLINE;
}


void CguiView::OnBtnAddTriangle()
{
	editTool = GUI_TOOL_ADD_TRANGLE;
}


void CguiView::OnBtnAddRectangle()
{
	editTool = GUI_TOOL_ADD_RECT;
}


void CguiView::OnBtnAddCircle()
{
	editTool = GUI_TOOL_ADD_CIRCLE;
}


void CguiView::OnBtnAddBezier()
{
	editTool = GUI_TOOL_ADD_BEZIER;
}


void CguiView::OnBtnAddCamera()
{
	// TODO: Add your command handler code here
}


void CguiView::OnBtnMove()
{
	editTool = GUI_TOOL_EDIT_MOVE;
}


void CguiView::OnBtnScale()
{
	editTool = GUI_TOOL_EDIT_SCALE;
}


void CguiView::OnBtnRotate()
{
	editTool = GUI_TOOL_EDIT_ROTATE;
}


void CguiView::OnBtnToPolygon()
{
	// TODO: Add your command handler code here
}


void CguiView::OnBtnRemove()
{
	// TODO: Add your command handler code here
}


void CguiView::OnBtnChooseCamera()
{
	// TODO: Add your command handler code here
}


void CguiView::OnBtnZoomIn()
{
	CguiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	ASSERT(pDoc->cameras.find(pDoc->currentCamera) != pDoc->cameras.end());
	GraphicCamera * camera = pDoc->cameras[pDoc->currentCamera].get();

	camera->scale = camera->scale * 2.0f;
}


void CguiView::OnBtnZoomOut()
{
	CguiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	ASSERT(pDoc->cameras.find(pDoc->currentCamera) != pDoc->cameras.end());
	GraphicCamera * camera = pDoc->cameras[pDoc->currentCamera].get();

	camera->scale = camera->scale * 0.5f;
}


void CguiView::OnPan()
{
	cameraTool = GUI_TOOL_CAMERA_PAN;
}


void CguiView::OnFrameNext()
{
	// TODO: Add your command handler code here
}


void CguiView::OnFramePrev()
{
	// TODO: Add your command handler code here
}


void CguiView::OnBtnRenderImg()
{
	// TODO: Add your command handler code here
}


void CguiView::OnBtnRenderSequence()
{
	// TODO: Add your command handler code here
}


void CguiView::OnBtnSelObj()
{
	selectMode = GUI_SELECT_MODE_OBJECT;
}


void CguiView::OnBtnSelVertex()
{
	selectMode = GUI_SELECT_MODE_VERTEX;
}


void CguiView::OnBtnSelClick()
{
	selectTool = GUI_SELECT_TOOL_POINTER;
}


void CguiView::OnBtnSelRect()
{
	selectTool = GUI_SELECT_TOOL_RECT;
}


void CguiView::OnBtnMoveUp()
{
	// TODO: Add your command handler code here
}


void CguiView::OnBtnMoveDown()
{
	// TODO: Add your command handler code here
}

void CguiView::OnBtnAddWacom()
{
	editTool = GUI_TOOL_ADD_WACOM;
	selectedGraphic.clear();
	selectedPoint.clear();
}



void CguiView::OnUpdateBtnSelObj(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(selectMode == GUI_SELECT_MODE_OBJECT);
}


void CguiView::OnUpdateBtnSelVertex(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(selectMode == GUI_SELECT_MODE_VERTEX);
}


void CguiView::OnUpdateBtnSelClick(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(selectTool == GUI_SELECT_TOOL_POINTER);
}


void CguiView::OnUpdateBtnSelRect(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(selectTool == GUI_SELECT_TOOL_RECT);
}


void CguiView::OnUpdateBtnAddLine(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(editTool == GUI_TOOL_ADD_LINE);
}


void CguiView::OnUpdateBtnAddBreakLine(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(editTool == GUI_TOOL_ADD_BREAKLINE);
}


void CguiView::OnUpdateBtnAddTriangle(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(editTool == GUI_TOOL_ADD_TRANGLE);
}


void CguiView::OnUpdateBtnAddRectangle(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(editTool == GUI_TOOL_ADD_RECT);
}


void CguiView::OnUpdateBtnAddCircle(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(editTool == GUI_TOOL_ADD_CIRCLE);
}


void CguiView::OnUpdateBtnAddBezier(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(editTool == GUI_TOOL_ADD_BEZIER);
}


void CguiView::OnUpdateBtnMove(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(editTool == GUI_TOOL_EDIT_MOVE);
}


void CguiView::OnUpdateBtnScale(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(editTool == GUI_TOOL_EDIT_SCALE);
}


void CguiView::OnUpdateBtnRotate(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(editTool == GUI_TOOL_EDIT_ROTATE);
}


void CguiView::OnUpdateBtnMoveUp(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(selectMode==GUI_SELECT_MODE_OBJECT && selectedGraphic.size()==1);
}


void CguiView::OnUpdateBtnMoveDown(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(selectMode == GUI_SELECT_MODE_OBJECT && selectedGraphic.size() == 1);
}


void CguiView::OnUpdateBtnToPolygon(CCmdUI *pCmdUI)
{
	auto * doc = GetDocument();
	if (selectMode == GUI_SELECT_MODE_OBJECT && selectedGraphic.size() == 1)
	{
		try 
		{
			if (GetDocument()->grphics[selectedGraphic.at(0)]->type != GRA_POLYGON)
			{
				pCmdUI->Enable(1);
			}
		}
		catch (...)
		{
			pCmdUI->Enable(0);
		}
	}
	else
	{
		pCmdUI->Enable(0);
	}
	
}


void CguiView::OnUpdateBtnRemove(CCmdUI *pCmdUI)
{
	if (selectMode == GUI_SELECT_MODE_OBJECT)
		pCmdUI->Enable(selectedGraphic.size() > 0);

	if (selectMode == GUI_SELECT_MODE_VERTEX)
		pCmdUI->Enable(selectedPoint.size() > 0);
	
}


void CguiView::OnUpdatePan(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(cameraTool == GUI_TOOL_CAMERA_PAN);
}


void CguiView::OnUpdateFrameNext(CCmdUI *pCmdUI)
{
	
}


void CguiView::OnUpdateFramePrev(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(frame > 0);
}


void CguiView::OnUpdateBtnAddWacom(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(state == GUI_STATE_NONE && editTool == GUI_TOOL_ADD_WACOM);
}



afx_msg LRESULT CguiView::OnViewReset(WPARAM wParam, LPARAM lParam)
{
	state = GUI_STATE_NONE;
	selectMode = GUI_SELECT_MODE_OBJECT;
	selectTool = GUI_SELECT_TOOL_POINTER;
	editTool = GUI_TOOL_NONE;
	cameraTool = GUI_TOOL_NONE;

	selectedGraphic.clear();
	selectedPoint.clear();

	return 0;
}


void CguiView::OnTimer(UINT_PTR nIDEvent)
{

	CView::OnTimer(nIDEvent);

	if (nIDEvent == TIMERID_REFRESH && drawed)
	{
		drawed = false;
		Invalidate(0);		
	}
		

}


void CguiView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	SetTimer(TIMERID_REFRESH, 20, 0);
}


void CguiView::OnMouseMove(UINT nFlags, CPoint point)
{
	CView::OnMouseMove(nFlags, point);

	CguiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	ASSERT(pDoc->cameras.find(pDoc->currentCamera) != pDoc->cameras.end());
	GraphicCamera * camera = pDoc->cameras[pDoc->currentCamera].get();

	auto worldPoint = camera->toWorld(point.x, point.y);

	switch (state)
	{
	case GUI_STATE_NONE:
		break;
	case GUI_STATE_LINE:
		ASSERT(selectedGraphic.size() == 1);
		ASSERT(pDoc->grphics.find(selectedGraphic[0]) != pDoc->grphics.end());
		{
			auto * g = pDoc->grphics[selectedGraphic[0]].get();
			ASSERT(g->type == GRA_POLYGON);
			g->graphicPolygon->points[1].x.setAttrAtFrame(worldPoint.x, frame);
			g->graphicPolygon->points[1].y.setAttrAtFrame(worldPoint.y, frame);
		}
		break;
	case GUI_STATE_RECT:
		ASSERT(selectedGraphic.size() == 1);
		ASSERT(pDoc->grphics.find(selectedGraphic[0]) != pDoc->grphics.end());
		{
			auto * g = pDoc->grphics[selectedGraphic[0]].get();
			ASSERT(g->type == GRA_POLYGON);
			g->graphicPolygon->points[1].x.setAttrAtFrame(worldPoint.x, frame);
			g->graphicPolygon->points[2].x.setAttrAtFrame(worldPoint.x, frame);
			g->graphicPolygon->points[2].y.setAttrAtFrame(worldPoint.y, frame);
			g->graphicPolygon->points[3].y.setAttrAtFrame(worldPoint.y, frame);
		}
		break;
	case GUI_STATE_TRANGLE_1:
		ASSERT(selectedGraphic.size() == 1);
		ASSERT(pDoc->grphics.find(selectedGraphic[0]) != pDoc->grphics.end());
		{
			auto * g = pDoc->grphics[selectedGraphic[0]].get();
			ASSERT(g->type == GRA_POLYGON);
			g->graphicPolygon->points[1].x.setAttrAtFrame(worldPoint.x, frame);
			g->graphicPolygon->points[1].y.setAttrAtFrame(worldPoint.y, frame);
		}
		break;
	case GUI_STATE_TRANGLE_2:
		ASSERT(selectedGraphic.size() == 1);
		ASSERT(pDoc->grphics.find(selectedGraphic[0]) != pDoc->grphics.end());
		{
			auto * g = pDoc->grphics[selectedGraphic[0]].get();
			ASSERT(g->type == GRA_POLYGON);
			g->graphicPolygon->points[2].x.setAttrAtFrame(worldPoint.x, frame);
			g->graphicPolygon->points[2].y.setAttrAtFrame(worldPoint.y, frame);
		}
		break;
	case GUI_STATE_BREAKLINE:
		ASSERT(selectedGraphic.size() == 1);
		ASSERT(pDoc->grphics.find(selectedGraphic[0]) != pDoc->grphics.end());
		{
			auto * g = pDoc->grphics[selectedGraphic[0]].get();
			ASSERT(g->type == GRA_POLYGON);
			int ed = g->graphicPolygon->points.size() - 1;
			g->graphicPolygon->points[ed].x.setAttrAtFrame(worldPoint.x, frame);
			g->graphicPolygon->points[ed].y.setAttrAtFrame(worldPoint.y, frame);
		}
		break;
	case GUI_STATE_CIRCLE:
		ASSERT(selectedGraphic.size() == 1);
		ASSERT(pDoc->grphics.find(selectedGraphic[0]) != pDoc->grphics.end());
		ASSERT(pDoc->grphics.find(selectedGraphic[0]) != pDoc->grphics.end());
		{
			auto * g = pDoc->grphics[selectedGraphic[0]].get();
			ASSERT(g->type == GRA_CIRCLE);
			auto x = g->graphicCircle->x.atFrame(frame);
			auto y = g->graphicCircle->y.atFrame(frame);
			float r = sqrtf((x - worldPoint.x)*(x - worldPoint.x) + (y - worldPoint.y)*(y - worldPoint.y));
			g->graphicCircle->r.setAttrAtFrame(r, frame);
		}
		break;
	case GUI_STATE_BEZIER:
		break;
	case GUI_STATE_PAN:
		{
			auto change = point - lastPointerPos;
			camera->x = panCamera.x - change.cx / panCamera.scale;
			camera->y = panCamera.y - change.cy / panCamera.scale;
		}
		break;
	}
}


void CguiView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	CView::OnMouseHWheel(nFlags, zDelta, pt);

}


void CguiView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CguiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	ASSERT(pDoc->cameras.find(pDoc->currentCamera) != pDoc->cameras.end());
	GraphicCamera * camera = pDoc->cameras[pDoc->currentCamera].get();

	auto worldPoint = camera->toWorld(point.x, point.y);

	CView::OnLButtonDown(nFlags, point);
	if (state == GUI_STATE_NONE)
	{
		if (cameraTool == GUI_TOOL_NONE)
		{
			if (editTool == GUI_TOOL_NONE)
			{
				// select objects
			}
			else if (editTool == GUI_TOOL_EDIT_MOVE || editTool == GUI_TOOL_EDIT_ROTATE || editTool == GUI_TOOL_EDIT_SCALE)
			{
				// edit
			}
			else {
				// add
				selectedPoint.clear();
				selectedGraphic.clear();

				Graphic * g = new Graphic();
				g->init();
				pDoc->grphics[g->guid] = std::auto_ptr<Graphic>(g);
				selectedGraphic.push_back(g->guid);
				pDoc->layer.push_back(g->guid);

				switch (editTool)
				{
				case GUI_TOOL_ADD_LINE:
					{
						g->graphicPolygon = std::auto_ptr<GraphicPolygon>(new GraphicPolygon);
						GraphicPoint pt = GraphicPoint();
						pt.init();
						pt.x.setAttrAtFrame(worldPoint.x, frame);
						pt.y.setAttrAtFrame(worldPoint.y, frame);
					
						g->graphicPolygon->points.push_back(pt);
						g->graphicPolygon->points.push_back(pt);

						g->type = GRA_POLYGON;
						state = GUI_STATE_LINE;
					}
					break;
				case GUI_TOOL_ADD_BREAKLINE:
					{
						g->graphicPolygon = std::auto_ptr<GraphicPolygon>(new GraphicPolygon);
						GraphicPoint pt = GraphicPoint();
						pt.init();
						pt.x.setAttrAtFrame(worldPoint.x, frame);
						pt.y.setAttrAtFrame(worldPoint.y, frame);

						g->graphicPolygon->points.push_back(pt);
						g->graphicPolygon->points.push_back(pt);

						g->type = GRA_POLYGON;
						state = GUI_STATE_BREAKLINE;
					}
					break;
				case GUI_TOOL_ADD_TRANGLE:
					{
						g->graphicPolygon = std::auto_ptr<GraphicPolygon>(new GraphicPolygon);
						GraphicPoint pt = GraphicPoint();
						pt.init();
						pt.x.setAttrAtFrame(worldPoint.x, frame);
						pt.y.setAttrAtFrame(worldPoint.y, frame);

						g->graphicPolygon->points.push_back(pt);
						g->graphicPolygon->points.push_back(pt);
						g->graphicPolygon->points.push_back(pt);
						g->graphicPolygon->points.push_back(pt);

						g->type = GRA_POLYGON;
						state = GUI_STATE_TRANGLE_1;
					}
					break;
				case GUI_TOOL_ADD_RECT:
					{
						g->graphicPolygon = std::auto_ptr<GraphicPolygon>(new GraphicPolygon);
						GraphicPoint pt = GraphicPoint();
						pt.init();
						pt.x.setAttrAtFrame(worldPoint.x, frame);
						pt.y.setAttrAtFrame(worldPoint.y, frame);

						g->graphicPolygon->points.push_back(pt);
						g->graphicPolygon->points.push_back(pt);
						g->graphicPolygon->points.push_back(pt);
						g->graphicPolygon->points.push_back(pt);
						g->graphicPolygon->points.push_back(pt);

						g->type = GRA_POLYGON;
						state = GUI_STATE_RECT;
					}
					break;
				case GUI_TOOL_ADD_CIRCLE:
					{
						g->graphicCircle = std::auto_ptr<GraphicCircle>(new GraphicCircle);
						g->graphicCircle->init();
						g->graphicCircle->x.setAttrAtFrame(worldPoint.x, frame);
						g->graphicCircle->y.setAttrAtFrame(worldPoint.y, frame);

						g->type = GRA_CIRCLE;
						state = GUI_STATE_CIRCLE;
					}
				}
			}
		}
		else
		{
			//camera edit
			switch (cameraTool)
			{
			case GUI_TOOL_CAMERA_PAN:
				lastPointerPos = point;
				state = GUI_STATE_PAN;
				panCamera = *camera;
				break;
			default:
				throw "unknow camera tool";
			}
		}
	}
	else
	{
		
		switch (state)
		{
		case GUI_STATE_LINE:
			ASSERT(selectedGraphic.size() == 1);
			ASSERT(pDoc->grphics.find(selectedGraphic[0]) != pDoc->grphics.end());
			{
				auto * g = pDoc->grphics[selectedGraphic[0]].get();
				ASSERT(g->type == GRA_POLYGON);
				g->graphicPolygon->points[1].x.setAttrAtFrame(worldPoint.x, frame);
				g->graphicPolygon->points[1].y.setAttrAtFrame(worldPoint.y, frame);
				state = GUI_STATE_NONE;
				editTool = GUI_TOOL_NONE;
			}
			break;
		case GUI_STATE_BREAKLINE:
			ASSERT(selectedGraphic.size() == 1);
			ASSERT(pDoc->grphics.find(selectedGraphic[0]) != pDoc->grphics.end());
			{
				auto * g = pDoc->grphics[selectedGraphic[0]].get();
				ASSERT(g->type == GRA_POLYGON);
				int ed = g->graphicPolygon->points.size() - 1;
				g->graphicPolygon->points[ed].x.setAttrAtFrame(worldPoint.x, frame);
				g->graphicPolygon->points[ed].y.setAttrAtFrame(worldPoint.y, frame);
				g->graphicPolygon->points.push_back(g->graphicPolygon->points[ed]);
			}
			break;
		case GUI_STATE_TRANGLE_1:
			ASSERT(selectedGraphic.size() == 1);
			ASSERT(pDoc->grphics.find(selectedGraphic[0]) != pDoc->grphics.end());
			{
				auto * g = pDoc->grphics[selectedGraphic[0]].get();
				ASSERT(g->type == GRA_POLYGON);
				g->graphicPolygon->points[1].x.setAttrAtFrame(worldPoint.x, frame);
				g->graphicPolygon->points[1].y.setAttrAtFrame(worldPoint.y, frame);
				state = GUI_STATE_TRANGLE_2;
			}
			break;
		case GUI_STATE_TRANGLE_2:
			ASSERT(selectedGraphic.size() == 1);
			ASSERT(pDoc->grphics.find(selectedGraphic[0]) != pDoc->grphics.end());
			{
				auto * g = pDoc->grphics[selectedGraphic[0]].get();
				ASSERT(g->type == GRA_POLYGON);
				g->graphicPolygon->points[2].x.setAttrAtFrame(worldPoint.x, frame);
				g->graphicPolygon->points[2].y.setAttrAtFrame(worldPoint.y, frame);
				state = GUI_STATE_NONE;
				editTool = GUI_TOOL_NONE;
			}
			break;
		case GUI_STATE_RECT:
			ASSERT(selectedGraphic.size() == 1);
			ASSERT(pDoc->grphics.find(selectedGraphic[0]) != pDoc->grphics.end());
			{
				auto * g = pDoc->grphics[selectedGraphic[0]].get();
				ASSERT(g->type == GRA_POLYGON);
				g->graphicPolygon->points[1].x.setAttrAtFrame(worldPoint.x, frame);
				g->graphicPolygon->points[2].x.setAttrAtFrame(worldPoint.x, frame);
				g->graphicPolygon->points[2].y.setAttrAtFrame(worldPoint.y, frame);
				g->graphicPolygon->points[3].y.setAttrAtFrame(worldPoint.y, frame);
				state = GUI_STATE_NONE;
				editTool = GUI_TOOL_NONE;
			}
			break;
		case GUI_STATE_CIRCLE:
			ASSERT(selectedGraphic.size() == 1);
			ASSERT(pDoc->grphics.find(selectedGraphic[0]) != pDoc->grphics.end());
			ASSERT(pDoc->grphics.find(selectedGraphic[0]) != pDoc->grphics.end());
			{
				auto * g = pDoc->grphics[selectedGraphic[0]].get();
				ASSERT(g->type == GRA_CIRCLE);
				auto x = g->graphicCircle->x.atFrame(frame);
				auto y = g->graphicCircle->y.atFrame(frame);
				float r = sqrtf((x - worldPoint.x)*(x - worldPoint.x) + (y - worldPoint.y)*(y - worldPoint.y));
				g->graphicCircle->r.setAttrAtFrame(r, frame);
				state = GUI_STATE_NONE;
				editTool = GUI_TOOL_NONE;
			}
			break;
		case GUI_STATE_BEZIER:
			break;
		case GUI_STATE_PAN:
			break;
		default:
			throw "unkown state";
		}
	}
}


void CguiView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CView::OnLButtonUp(nFlags, point);

	switch (state)
	{
		case GUI_STATE_PAN:
		{
			state = GUI_STATE_NONE;
		}	
		break;

	}
}


void CguiView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CView::OnRButtonDown(nFlags, point);
}


void CguiView::OnMButtonDown(UINT nFlags, CPoint point)
{
	CView::OnMButtonDown(nFlags, point);

	CguiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	ASSERT(pDoc->cameras.find(pDoc->currentCamera) != pDoc->cameras.end());
	GraphicCamera * camera = pDoc->cameras[pDoc->currentCamera].get();

	cameraTool == GUI_TOOL_CAMERA_PAN;
	stateBackUp = state;
	state = GUI_STATE_PAN;
	lastPointerPos = point;
	panCamera = *camera;
}


void CguiView::OnMButtonUp(UINT nFlags, CPoint point)
{
	CView::OnMButtonUp(nFlags, point);

	cameraTool == GUI_TOOL_NONE;
	state = stateBackUp;
}


void CguiView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CView::OnLButtonDblClk(nFlags, point);

	CguiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	ASSERT(pDoc->cameras.find(pDoc->currentCamera) != pDoc->cameras.end());
	GraphicCamera * camera = pDoc->cameras[pDoc->currentCamera].get();

	auto worldPoint = camera->toWorld(point.x, point.y);

	if (state == GUI_STATE_BREAKLINE)
	{
		auto close = MessageBox(L"close breakline?", 0, MB_YESNO);
		if (close == IDYES)
		{
			ASSERT(selectedGraphic.size() == 1);
			ASSERT(pDoc->grphics.find(selectedGraphic[0]) != pDoc->grphics.end());
			auto * g = pDoc->grphics[selectedGraphic[0]].get();
			ASSERT(g->type == GRA_POLYGON);
			g->graphicPolygon->points.push_back(g->graphicPolygon->points[0]);
		}
		state = GUI_STATE_NONE;
		editTool = GUI_TOOL_NONE;
	}
}


int CguiView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Open a Wintab context

	// Get default context information
	gpWTInfoA(WTI_DEFCONTEXT, 0, &lc);

	// Open the context
	lc.lcPktData = PACKETDATA;
	lc.lcPktMode = PACKETMODE;
	lc.lcOptions = CXO_MESSAGES;
	lc.lcSysMode = 1;
	hCtx = gpWTOpenA(m_hWnd, &lc, TRUE);
	return 0;
}


afx_msg LRESULT CguiView::OnWtPacket(WPARAM wSerial, LPARAM hCtx)
{
	// Read the packet
	PACKET pkt;
	gpWTPacket((HCTX)hCtx, wSerial, &pkt);

	// Process packets in order, one at a time
	CSingleLock lock(pWTMutex, TRUE);

	// Get window size
	RECT window_rect;
	RECT desktop_rect;
	//GetWindowPlacement(&window_rect);
	GetWindowRect(&window_rect);
	GetDesktopWindow()->GetWindowRect(&desktop_rect);

	int sizeX = desktop_rect.right - desktop_rect.left;
	int sizeY = desktop_rect.bottom - desktop_rect.top;

	int absX = (pkt.pkX * sizeX) / lc.lcInExtX + lc.lcSysOrgX;
	int absY = sizeY - (pkt.pkY * sizeY) / lc.lcInExtY + lc.lcSysOrgY;

	int x = absX - window_rect.left;
	int y = absY - window_rect.top;

	SetCursorPos(absX, absY);

	if (editTool == GUI_TOOL_ADD_WACOM)
	{
		auto pDoc = GetDocument();
		if (pDoc == nullptr)
			return 0;

		if (selectedGraphic.size() > 1)
		{
			selectedGraphic.clear();
		}
		else if (selectedGraphic.size() == 1)
		{
			auto g = pDoc->grphics[selectedGraphic[0]].get();
			if (g->type != GRA_POLYGON)
			{
				selectedGraphic.clear();
				return 0;
			}

			if (!pkt.pkButtons && g->graphicPolygon->points.size()>1)
			{
				selectedGraphic.clear();
				return 0;
			}

			if (pkt.pkButtons)
			{
				ASSERT(pDoc->cameras.find(pDoc->currentCamera) != pDoc->cameras.end());
				GraphicCamera * camera = pDoc->cameras[pDoc->currentCamera].get();

				auto pts = g->graphicPolygon.get();

				GraphicPoint pt;
				auto pos = camera->toWorld(x, y);
				pt.init();
				pt.x.setAttrAtFrame(pos.x, frame);
				pt.y.setAttrAtFrame(pos.y, frame);
				pt.width.setAttrAtFrame(pkt.pkNormalPressure/64, frame);

				pts->points.push_back(pt);
			}
		}
		else if (selectedGraphic.size() == 0)
		{
			Graphic * g = new Graphic;
			g->init();
			g->graphicPolygon = std::auto_ptr<GraphicPolygon>(new GraphicPolygon);
			g->type = GRA_POLYGON;
			pDoc->grphics[g->guid] = std::auto_ptr<Graphic>(g);
			selectedGraphic.push_back(g->guid);
			pDoc->layer.push_back(g->guid);
		}
		
	}
	else if(pkt.pkButtons!=oldPenDown)
	{
		if (pkt.pkButtons)
		{
			mouse_event(MOUSEEVENTF_LEFTDOWN, absX, absY, 0, 0);
		}
		else
		{
			mouse_event(MOUSEEVENTF_LEFTUP, absX, absY, 0, 0);
		}
		oldPenDown = pkt.pkButtons;
	}
	
	return 0;
}

void CguiView::OnSelectAll()
{
	auto pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (state == GUI_STATE_NONE && selectMode == GUI_SELECT_MODE_OBJECT)
	{
		selectedGraphic.clear();
		for (auto & guid : pDoc->layer)
		{
			selectedGraphic.push_back(guid);
		}
	}
}




BOOL CguiView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	

	CguiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	ASSERT(pDoc->cameras.find(pDoc->currentCamera) != pDoc->cameras.end());
	GraphicCamera * camera = pDoc->cameras[pDoc->currentCamera].get();

	if (zDelta > 0)
	{
		camera->scale = camera->scale * (1+zDelta / 240.f);
	}
	else if(zDelta < 0)
	{
		camera->scale = camera->scale / (1-zDelta / 240.f);
	}

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
