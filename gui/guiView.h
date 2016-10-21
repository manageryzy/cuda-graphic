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

// guiView.h : interface of the CguiView class
//

#pragma once

#define GUI_STATE_NONE 0
#define GUI_STATE_LINE 1
#define GUI_STATE_BREAKLINE 2
#define GUI_STATE_TRANGLE_1 3
#define GUI_STATE_TRANGLE_2 4
#define GUI_STATE_RECT 5
#define GUI_STATE_CIRCLE
#define GUI_STATE_BEZIER 7

#define GUI_SELECT_MODE_OBJECT 0
#define GUI_SELECT_MODE_VERTEX 1

#define GUI_SELECT_TOOL_POINTER 0
#define GUI_SELECT_TOOL_RECT 1

#define GUI_TOOL_NONE 0
#define GUI_TOOL_ADD_LINE 1
#define GUI_TOOL_ADD_BREAKLINE 2
#define GUI_TOOL_ADD_TRANGLE 3
#define GUI_TOOL_ADD_RECT 4
#define GUI_TOOL_ADD_CIRCLE 5
#define GUI_TOOL_ADD_BEZIER 6
#define GUI_TOOL_ADD_CAMERA 7
#define GUI_TOOL_EDIT_MOVE 8
#define GUI_TOOL_EDIT_SCALE 9
#define GUI_TOOL_EDIT_ROTATE 10
#define GUI_TOOL_CAMERA_PAN 11



class CguiView : public CView
{
protected: // create from serialization only
	CguiView();
	DECLARE_DYNCREATE(CguiView)

// Attributes
public:
	CguiDoc* GetDocument() const;
	int state;
	int selectMode;
	int selectTool;
	int editTool;
	int cameraTool;
	int frame;

	std::vector<GUID_> selectedGraphic;
	std::vector<GraphicPoint *> selectedPoint;
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CguiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBtnAddLine();
	afx_msg void OnBtnAddBreakLine();
	afx_msg void OnBtnAddTriangle();
	afx_msg void OnBtnAddRectangle();
	afx_msg void OnBtnAddCircle();
	afx_msg void OnBtnAddBezier();
	afx_msg void OnBtnAddCamera();
	afx_msg void OnBtnMove();
	afx_msg void OnBtnScale();
	afx_msg void OnBtnRotate();
	afx_msg void OnBtnToPolygon();
	afx_msg void OnBtnRemove();
	afx_msg void OnBtnChooseCamera();
	afx_msg void OnBtnZoomIn();
	afx_msg void OnBtnZoomOut();
	afx_msg void OnPan();
	afx_msg void OnFrameNext();
	afx_msg void OnFramePrev();
	afx_msg void OnBtnRenderImg();
	afx_msg void OnBtnRenderSequence();
	afx_msg void OnBtnSelObj();
	afx_msg void OnBtnSelVertex();
	afx_msg void OnBtnSelClick();
	afx_msg void OnBtnSelRect();
	afx_msg void OnBtnMoveUp();
	afx_msg void OnBtnMoveDown();
	afx_msg void OnUpdateBtnSelObj(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnSelVertex(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnSelClick(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnSelRect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnAddLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnAddBreakLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnAddTriangle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnAddRectangle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnAddCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnAddBezier(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnMove(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnScale(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnRotate(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnMoveUp(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnMoveDown(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnToPolygon(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnRemove(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFrameNext(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFramePrev(CCmdUI *pCmdUI);
protected:

//	afx_msg LRESULT OnViewreset(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnViewReset(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // debug version in guiView.cpp
inline CguiDoc* CguiView::GetDocument() const
   { return reinterpret_cast<CguiDoc*>(m_pDocument); }
#endif

