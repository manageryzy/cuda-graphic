// guiView.cpp : implementation of the CguiView class
//

#include "stdafx.h"

#ifndef SHARED_HANDLERS
#include "gui.h"
#endif

#define USE_GRA_TOOL
#include "guiDoc.h"
#include "guiView.h"

#undef USE_GRA_TOOL
char * gpszProgramName = "CUDAX";

#include "MainFrm.h"
#include <exception>  

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
	ON_COMMAND(ID_ESC, &CguiView::OnEsc)
	ON_COMMAND(ID_PREV_FRAME, &CguiView::OnPrevFrame)
	ON_COMMAND(ID_NEXT_FRAME, &CguiView::OnNextFrame)
END_MESSAGE_MAP()

// CguiView construction/destruction

CguiView::CguiView()
{
	selectMode = GUI_SELECT_MODE_OBJECT;
	selectTool = nullptr;
	editTool = nullptr;
	cameraTool = nullptr;

	toolAddBezier = new GraphicToolAddBezier();
	toolAddBreakline = new GraphicToolAddBreakline();
	toolAddCircle = new GraphicToolAddCircle();
	toolAddLine = new GraphicToolAddLine();
	toolAddRect = new GraphicToolAddRect();
	toolAddTrangle = new GraphicToolAddTrangle();
	toolAddWacom = new GraphicToolAddWacom();
	toolCameraPan = new GraphicToolCameraPan();
	toolCameraZoomIn = new GraphicToolCameraZoomIn();
	toolCameraZoomOut = new GraphicToolCameraZoomOut();
	toolMove = new GraphicToolMove();
	toolRotate = new GraphicToolRotate();
	toolScale = new GraphicToolScale();
	toolSelectRect = new GraphicToolSelecRect();
	toolSelectPointer = new GraphicToolSelectPointer();

	toolAddBezier->bind(this);
	toolAddBreakline->bind(this);
	toolAddCircle->bind(this);
	toolAddLine->bind(this);
	toolAddRect->bind(this);
	toolAddTrangle->bind(this);
	toolAddWacom->bind(this);
	toolCameraPan->bind(this);
	toolCameraZoomIn->bind(this);
	toolCameraZoomOut->bind(this);
	toolMove->bind(this);
	toolRotate->bind(this);
	toolScale->bind(this);
	toolSelectRect->bind(this);
	toolSelectPointer->bind(this);

	try 
	{
		cudaRender = CUDARender::getCudaRender();
	}
	catch (std::exception& e)
	{
		::MessageBox(0,CString(e.what()),L"error",MB_ICONERROR);
		exit(-1);
	}
	d2dRender = new D2DRender(this);
	
	creating = nullptr;

	frame = 0;

	selectedGraphic.clear();
	selectedPoint.clear();

	pWTMutex = new CMutex(TRUE, NULL, NULL);
	hCtx = 0;
}

CguiView::~CguiView()
{
	delete pWTMutex;
	if (hCtx)
	{
		gpWTClose(hCtx);
	}
}

BOOL CguiView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

// CguiView drawing

void CguiView::beginCreating()
{
	selectedGraphic.clear();
	cudaRender->getCache()->change(frame);
	d2dRender->flush();
}

void CguiView::endCreating(bool end)
{
	CguiDoc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc);
	if (creating)
	{
		pDoc->graphics[creating->guid] = std::auto_ptr<Graphic>(creating);
		pDoc->layer.push_back(creating->guid);
		selectedGraphic.insert(creating->guid);
	}
	creating = nullptr;
	if(end)
		editTool = nullptr;

	cudaRender->getCache()->change(frame);
	d2dRender->flush();

	CMainFrame * frame = (CMainFrame *)AfxGetMainWnd();
	frame->m_wndSceneView.FillClassView(pDoc);
}


inline bool CguiView::dispatchToolMsg(int msg, void * param)
{
	if (cameraTool != nullptr)
	{
		if (cameraTool->on(msg, param))
			return true;
	}

	if (editTool != nullptr)
	{
		if (editTool->on(msg, param))
			return true;
	}

	if (selectTool != nullptr)
	{
		if (selectTool->on(msg, param))
			return true;
	}

	return false;
}

void CguiView::OnDraw(CDC* /*pDC*/)
{
	drawed = true;
	d2dRender->renderScence();
}

void CguiView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	if (!dispatchToolMsg(WM_RBUTTONUP, &point))
	{
		ClientToScreen(&point);
		OnContextMenu(this, point);
	}
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
	if (editTool == nullptr)
		editTool = toolAddLine;
	else if (editTool == toolAddLine)
	{
		if (creating) delete creating;
		creating = nullptr;
		editTool = nullptr;
		toolAddLine->reset();
		d2dRender->flush();
	}
}


void CguiView::OnBtnAddBreakLine()
{
	if (editTool == nullptr)
		editTool = toolAddBreakline;
	else if (editTool == toolAddBreakline)
	{
		if (creating) delete creating;
		creating = nullptr;
		editTool = nullptr;
		toolAddBreakline->reset();
	}
}


void CguiView::OnBtnAddTriangle()
{
	if (editTool == nullptr)
		editTool = toolAddTrangle;
	else if (editTool == toolAddTrangle)
	{
		if (creating) delete creating;
		creating = nullptr;
		editTool = nullptr;
		toolAddTrangle->reset();
	}
}


void CguiView::OnBtnAddRectangle()
{
	if (editTool == nullptr)
		editTool = toolAddRect;
	else if (editTool == toolAddRect)
	{
		if (creating) delete creating;
		creating = nullptr;
		editTool = nullptr;
		toolAddRect->reset();
	}
}


void CguiView::OnBtnAddCircle()
{
	if (editTool == nullptr)
		editTool = toolAddCircle;
	else if (editTool == toolAddCircle)
	{
		if (creating) delete creating;
		creating = nullptr;
		editTool = nullptr;
		toolAddCircle->reset();
	}
}


void CguiView::OnBtnAddBezier()
{
	if (editTool == nullptr)
		editTool = toolAddBezier;
	else if (editTool == toolAddBezier)
	{
		if (creating) delete creating;
		creating = nullptr;
		editTool = nullptr;
		toolAddBezier->reset();
	}
}


void CguiView::OnBtnAddCamera()
{
	// TODO: Add your command handler code here
}


void CguiView::OnBtnMove()
{
	if (editTool == nullptr)
		editTool = toolMove;
	else if (editTool == toolMove && !toolMove->isBusy())
		editTool = nullptr;
}


void CguiView::OnBtnScale()
{
	if (editTool == nullptr)
		editTool = toolScale;
	else if (editTool == toolScale && !toolScale->isBusy())
		editTool = nullptr;
}


void CguiView::OnBtnRotate()
{
	if (editTool == nullptr)
		editTool = toolRotate;
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
	toolCameraZoomIn->zoomIn();
}


void CguiView::OnBtnZoomOut()
{
	toolCameraZoomOut->zoomOut();
}


void CguiView::OnPan()
{
	if (cameraTool == nullptr)
		cameraTool = toolCameraPan;
}


void CguiView::OnFrameNext()
{
	if (editTool != nullptr)
	{
		if (editTool == toolAddBezier ||
			editTool == toolAddBreakline ||
			editTool == toolAddCircle ||
			editTool == toolAddLine ||
			editTool == toolAddRect ||
			editTool == toolAddTrangle ||
			editTool == toolAddWacom)
			return;
	}

	frame += 1;
	auto f = (CMainFrame *)GetTopLevelFrame();
	CString out;
	out.Format(L"%s - frame: %d", title, frame);
	f->SetWindowTextW(out);
	d2dRender->flush();
}


void CguiView::OnFramePrev()
{
	if (editTool != nullptr)
	{
		if (editTool == toolAddBezier ||
			editTool == toolAddBreakline ||
			editTool == toolAddCircle ||
			editTool == toolAddLine ||
			editTool == toolAddRect ||
			editTool == toolAddTrangle ||
			editTool == toolAddWacom)
			return;
	}

	if (frame > 0)
		frame -= 1;
	auto f = (CMainFrame *)GetTopLevelFrame();
	CString out;
	out.Format(L"%s - frame: %d", title, frame);
	f->SetWindowTextW(out);
	d2dRender->flush();
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
	if(editTool == nullptr)
		selectMode = GUI_SELECT_MODE_OBJECT;
}


void CguiView::OnBtnSelVertex()
{
	if(editTool == nullptr)
		selectMode = GUI_SELECT_MODE_VERTEX;
}


void CguiView::OnBtnSelClick()
{
	selectTool = toolSelectPointer;
}


void CguiView::OnBtnSelRect()
{
	selectTool = toolSelectRect;
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
	if (editTool == nullptr)
		editTool = toolAddWacom;
	else if (editTool == toolAddWacom)
	{
		if(creating)delete creating;
		creating = nullptr;
		editTool = nullptr;
	}
		
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
	pCmdUI->SetRadio(selectTool == toolSelectPointer);
}


void CguiView::OnUpdateBtnSelRect(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(selectTool == toolSelectRect);
}


void CguiView::OnUpdateBtnAddLine(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(editTool == toolAddLine);
	pCmdUI->Enable(editTool == nullptr || editTool == toolAddLine);
}


void CguiView::OnUpdateBtnAddBreakLine(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(editTool == toolAddBreakline);
	pCmdUI->Enable(editTool == nullptr || editTool == toolAddBreakline);
}


void CguiView::OnUpdateBtnAddTriangle(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(editTool == toolAddTrangle);
	pCmdUI->Enable(editTool == nullptr || editTool == toolAddTrangle);
}


void CguiView::OnUpdateBtnAddRectangle(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(editTool == toolAddRect);
	pCmdUI->Enable(editTool == nullptr || editTool == toolAddRect);
}


void CguiView::OnUpdateBtnAddCircle(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(editTool == toolAddCircle);
	pCmdUI->Enable(editTool == nullptr || editTool == toolAddCircle);
}


void CguiView::OnUpdateBtnAddBezier(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(editTool == toolAddBezier);
	pCmdUI->Enable(editTool == nullptr || editTool == toolAddBezier);
}


void CguiView::OnUpdateBtnMove(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(editTool == toolMove);
	pCmdUI->Enable(editTool == nullptr || editTool == toolMove);
}


void CguiView::OnUpdateBtnScale(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(editTool == toolScale);
	pCmdUI->Enable(editTool == nullptr || editTool == toolScale);
}


void CguiView::OnUpdateBtnRotate(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(editTool == toolRotate);
	pCmdUI->Enable(editTool == nullptr || editTool == toolRotate);
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
			if (GetDocument()->graphics[*selectedGraphic.begin()]->type != GRA_POLYGON)
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
	pCmdUI->SetRadio(cameraTool == toolCameraPan);
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
	pCmdUI->Enable(theApp.tabletOk && (editTool == nullptr || editTool == toolAddWacom ));
	pCmdUI->SetRadio(editTool == toolAddWacom);
}



afx_msg LRESULT CguiView::OnViewReset(WPARAM wParam, LPARAM lParam)
{
	selectTool = nullptr;
	editTool = nullptr;
	cameraTool = nullptr;

	toolAddBezier->reset();
	toolAddBreakline->reset();
	toolAddCircle->reset();
	toolAddLine->reset();
	toolAddRect->reset();
	toolAddTrangle->reset();
	toolAddWacom->reset();
	toolCameraPan->reset();
	toolCameraZoomIn->reset();
	toolCameraZoomOut->reset();
	toolMove->reset();
	toolRotate->reset();
	toolScale->reset();
	toolSelectRect->reset();
	toolSelectPointer->reset();

	selectedGraphic.clear();
	selectedPoint.clear();

	if (creating)
		delete creating;
	creating = nullptr;

	auto pDoc = GetDocument();
	CMainFrame * f = (CMainFrame *)AfxGetMainWnd();
	f->m_wndSceneView.FillClassView(pDoc);

	
	title = f->GetTitle();
	CString out;
	out.Format(L"%s - frame: %ld", title, frame);
	f->SetWindowTextW(out);

	d2dRender->flush();

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

	auto pDoc = GetDocument();
	CMainFrame * frame = (CMainFrame *)AfxGetMainWnd();
	frame->m_wndSceneView.FillClassView(pDoc);
}


void CguiView::OnMouseMove(UINT nFlags, CPoint point)
{
	if(!dispatchToolMsg(WM_MOUSEMOVE, &point))
		CView::OnMouseMove(nFlags, point);
}


void CguiView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (!dispatchToolMsg(WM_MOUSEHWHEEL, &zDelta))
		CView::OnMouseHWheel(nFlags, zDelta, pt);
}


void CguiView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!dispatchToolMsg(WM_LBUTTONDOWN, &point))
		CView::OnLButtonDown(nFlags, point);
}


void CguiView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!dispatchToolMsg(WM_LBUTTONUP, &point))
		CView::OnLButtonUp(nFlags, point);
}


void CguiView::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (!dispatchToolMsg(WM_RBUTTONDOWN, &point))
		CView::OnRButtonDown(nFlags, point);
}


void CguiView::OnMButtonDown(UINT nFlags, CPoint point)
{
	if (!cameraTool)
	{
		cameraTool = toolCameraPan;
		toolCameraPan->startMove(&point);
	}

	if (!dispatchToolMsg(WM_MBUTTONDOWN, &point))
		CView::OnMButtonDown(nFlags, point);
}


void CguiView::OnMButtonUp(UINT nFlags, CPoint point)
{
	if (cameraTool == toolCameraPan)
	{
		toolCameraPan->endMove();
		cameraTool = nullptr;
	}

	if (!dispatchToolMsg(WM_MBUTTONUP, &point))
		CView::OnMButtonUp(nFlags, point);
}


void CguiView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (!dispatchToolMsg(WM_LBUTTONDBLCLK, &point))
		CView::OnLButtonDblClk(nFlags, point);
}


int CguiView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Open a Wintab context

	// Get default context information

	if (theApp.tabletOk)
	{
		gpWTInfoA(WTI_DEFCONTEXT, 0, &lc);

		// Open the context
		lc.lcPktData = PACKETDATA;
		lc.lcPktMode = PACKETMODE;
		lc.lcOptions = CXO_MESSAGES;
		lc.lcSysMode = 1;
		hCtx = gpWTOpenA(m_hWnd, &lc, TRUE);
	}

	return 0;
}


afx_msg LRESULT CguiView::OnWtPacket(WPARAM wSerial, LPARAM hCtx)
{
	// Read the packet
	PACKET pkt;
	gpWTPacket((HCTX)hCtx, (UINT)wSerial, &pkt);

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

	if (editTool == toolAddWacom)
	{
		toolAddWacom->on(WT_PACKET, new GraphicToolMsgTablet(x, y, pkt.pkButtons, pkt.pkNormalPressure));
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

	if (editTool == nullptr && selectMode == GUI_SELECT_MODE_OBJECT)
	{
		selectedGraphic.clear();
		for (auto & guid : pDoc->layer)
		{
			selectedGraphic.insert(guid);
		}
		cudaRender->getCache()->change(frame);
		d2dRender->flush();
	}
}




BOOL CguiView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (zDelta > 0)
	{
		toolCameraZoomIn->zoomIn();
	}
	if (zDelta < 0)
	{
		toolCameraZoomOut->zoomOut();
	}

	if (!dispatchToolMsg(WM_MOUSEWHEEL, &zDelta))
	{
		return CView::OnMouseWheel(nFlags, zDelta, pt);
	}
	return true;
}


void CguiView::OnEsc()
{
	dispatchToolMsg(ID_ESC, 0);
}


void CguiView::OnPrevFrame()
{
	OnFramePrev();
}


void CguiView::OnNextFrame()
{
	OnFrameNext();
}
