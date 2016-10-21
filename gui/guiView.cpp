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

#include "guiDoc.h"
#include "guiView.h"

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
END_MESSAGE_MAP()

// CguiView construction/destruction

CguiView::CguiView()
{
	state = GUI_STATE_NONE;
	selectMode = GUI_SELECT_MODE_OBJECT;
	selectTool = GUI_SELECT_TOOL_POINTER;
	editTool = GUI_TOOL_NONE;
	cameraTool = GUI_TOOL_NONE;

	selectedGraphic.clear();
	selectedPoint.clear();
}

CguiView::~CguiView()
{
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
	CguiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
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
	// TODO: Add your command handler code here
}


void CguiView::OnBtnZoomOut()
{
	// TODO: Add your command handler code here
}


void CguiView::OnPan()
{
	// TODO: Add your command handler code here
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


void CguiView::OnUpdateFrameNext(CCmdUI *pCmdUI)
{
	
}


void CguiView::OnUpdateFramePrev(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(frame > 0);
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
