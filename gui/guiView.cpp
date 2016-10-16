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
END_MESSAGE_MAP()

// CguiView construction/destruction

CguiView::CguiView()
{
	// TODO: add construction code here

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
	// TODO: Add your command handler code here
}


void CguiView::OnBtnAddBreakLine()
{
	// TODO: Add your command handler code here
}


void CguiView::OnBtnAddTriangle()
{
	// TODO: Add your command handler code here
}


void CguiView::OnBtnAddRectangle()
{
	// TODO: Add your command handler code here
}


void CguiView::OnBtnAddCircle()
{
	// TODO: Add your command handler code here
}


void CguiView::OnBtnAddBezier()
{
	// TODO: Add your command handler code here
}


void CguiView::OnBtnAddCamera()
{
	// TODO: Add your command handler code here
}


void CguiView::OnBtnMove()
{
	// TODO: Add your command handler code here
}


void CguiView::OnBtnScale()
{
	// TODO: Add your command handler code here
}


void CguiView::OnBtnRotate()
{
	// TODO: Add your command handler code here
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
