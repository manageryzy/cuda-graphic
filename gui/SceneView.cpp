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

#include "stdafx.h"
#include "MainFrm.h"

#include "Resource.h"
#include "gui.h"
#include "guiDoc.h"
#include "guiView.h"
#include "SceneView.h"

class CClassViewMenuButton : public CMFCToolBarMenuButton
{
	friend class CSceneView;

	DECLARE_SERIAL(CClassViewMenuButton)

public:
	CClassViewMenuButton(HMENU hMenu = NULL) : CMFCToolBarMenuButton((UINT)-1, hMenu, -1)
	{
	}

	virtual void OnDraw(CDC* pDC, const CRect& rect, CMFCToolBarImages* pImages, BOOL bHorz = TRUE,
		BOOL bCustomizeMode = FALSE, BOOL bHighlight = FALSE, BOOL bDrawBorder = TRUE, BOOL bGrayDisabledButtons = TRUE)
	{
		pImages = CMFCToolBar::GetImages();

		CAfxDrawState ds;
		pImages->PrepareDrawImage(ds);

		CMFCToolBarMenuButton::OnDraw(pDC, rect, pImages, bHorz, bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);

		pImages->EndDrawImage(ds);
	}
};

IMPLEMENT_SERIAL(CClassViewMenuButton, CMFCToolBarMenuButton, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSceneView::CSceneView()
{
	m_nCurrSort = ID_SORTING_GROUPBYTYPE;
	treeItem = new std::map<HTREEITEM, GUID_>();
}

CSceneView::~CSceneView()
{
}

BEGIN_MESSAGE_MAP(CSceneView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnSort)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnUpdateSort)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassView message handlers

int CSceneView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create views:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndClassView.Create(dwViewStyle, rectDummy, this, 2))
	{
		TRACE0("Failed to create Scene View\n");
		return -1;      // fail to create
	}

	// Load images:
	//m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_SORT);
	//m_wndToolBar.LoadToolBar(IDR_SORT, 0, 0, TRUE /* Is locked */);

	OnChangeVisualStyle();

	//m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	//m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	//m_wndToolBar.SetOwner(this);

	//// All commands will be routed via this control , not via the parent frame:
	//m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	//CMenu menuSort;
	//menuSort.LoadMenu(IDR_POPUP_SORT);

	//m_wndToolBar.ReplaceButton(ID_SORT_MENU, CClassViewMenuButton(menuSort.GetSubMenu(0)->GetSafeHmenu()));

	//CClassViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CClassViewMenuButton, m_wndToolBar.GetButton(0));

	//if (pButton != NULL)
	//{
	//	pButton->m_bText = FALSE;
	//	pButton->m_bImage = TRUE;
	//	pButton->SetImage(GetCmdMgr()->GetCmdImage(m_nCurrSort));
	//	pButton->SetMessageWnd(this);
	//}

	// Fill in some static tree view data (dummy code, nothing magic here)
	FillClassView();

	return 0;
}

void CSceneView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CSceneView::FillClassView(CguiDoc * doc, CguiView * view)
{
	m_wndClassView.DeleteAllItems();
	treeItem->clear();

	HTREEITEM hRoot = m_wndClassView.InsertItem(_T("Scene"), 0, 0);
	m_wndClassView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
	

	HTREEITEM hClass = m_wndClassView.InsertItem(_T("Camera"), 2, 2, hRoot);
	if(doc)for (auto & c : doc->cameras)
	{
		m_wndClassView.InsertItem(c.second->label, 5, 5, hClass);
	}
	m_wndClassView.Expand(hClass, TVE_EXPAND);

	hClass = m_wndClassView.InsertItem(_T("Graphics"), 2, 2, hRoot);
	if (doc)for (int i = doc->layer.size()-1;i>=0;i--)
	{
		auto & guid = doc->layer.at(i);
		auto g = doc->graphics[guid].get();
		HTREEITEM item = 0;
		
		switch (g->type)
		{
		case GRA_POLYGON:
			item = m_wndClassView.InsertItem(g->label, 1, 1, hClass);
			break;
		case GRA_CIRCLE:
			item = m_wndClassView.InsertItem(g->label, 3, 3, hClass);
			break;
		case GRA_BEZIER:
			item = m_wndClassView.InsertItem(g->label, 4, 4, hClass);
			break;
		default:
			break;
		}

		(*treeItem)[item] = guid;
		if (view->selectedGraphic.find(guid) != view->selectedGraphic.end())
			m_wndClassView.SelectItem(item);
	}
	m_wndClassView.Expand(hClass, TVE_EXPAND);
	m_wndClassView.Expand(hRoot, TVE_EXPAND);
}

void CSceneView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndClassView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// Select clicked item:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_SORT);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}
}

void CSceneView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	//int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	//m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndClassView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top  + 1, rectClient.Width() - 2, rectClient.Height()  - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

BOOL CSceneView::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}

void CSceneView::OnSort(UINT id)
{
	if (m_nCurrSort == id)
	{
		return;
	}

	m_nCurrSort = id;

	//CClassViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CClassViewMenuButton, m_wndToolBar.GetButton(0));

	//if (pButton != NULL)
	//{
	//	pButton->SetImage(GetCmdMgr()->GetCmdImage(id));
	//	m_wndToolBar.Invalidate();
	//	m_wndToolBar.UpdateWindow();
	//}
}

void CSceneView::OnUpdateSort(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nCurrSort);
}



void CSceneView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectTree;
	m_wndClassView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CSceneView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndClassView.SetFocus();
}

void CSceneView::OnChangeVisualStyle()
{
	m_ClassViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("Can't load bitmap: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_ClassViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_ClassViewImages.Add(&bmp, RGB(255, 0, 0));

	m_wndClassView.SetImageList(&m_ClassViewImages, TVSIL_NORMAL);

	//m_wndToolBar.CleanUpLockedImages();
	//m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* Locked */);
}
