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


class CguiView : public CView
{
protected: // create from serialization only
	CguiView();
	DECLARE_DYNCREATE(CguiView)

// Attributes
public:
	CguiDoc* GetDocument() const;

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
};

#ifndef _DEBUG  // debug version in guiView.cpp
inline CguiDoc* CguiView::GetDocument() const
   { return reinterpret_cast<CguiDoc*>(m_pDocument); }
#endif

