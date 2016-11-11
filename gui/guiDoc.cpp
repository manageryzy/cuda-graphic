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

// guiDoc.cpp : implementation of the CguiDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "gui.h"
#endif

#include "guiDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CguiDoc

IMPLEMENT_DYNCREATE(CguiDoc, CDocument)

BEGIN_MESSAGE_MAP(CguiDoc, CDocument)
END_MESSAGE_MAP()


// CguiDoc construction/destruction

CguiDoc::CguiDoc()
{
	// TODO: add one-time construction code here

}

CguiDoc::~CguiDoc()
{
}

BOOL CguiDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	this->graphics.clear();
	this->layer.clear();
	this->cameras.clear();

	GraphicCamera * defaultCamera = new GraphicCamera;
	this->cameras[defaultCamera->guid] = std::auto_ptr<GraphicCamera>(defaultCamera);
	this->currentCamera = defaultCamera->guid;

	inited = true;

	POSITION pos = GetFirstViewPosition();
	auto view = GetNextView(pos);
	if (view != nullptr)
	{
		view->PostMessageW(WM_VIEW_RESET);
	}

	return TRUE;
}




// CguiDoc serialization

void CguiDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << (DWORD)0x41445543;

		ar << this->graphics.size();
		for (auto & g : this->graphics)
		{
			g.second->Serialize(ar);
		}

		ar << this->layer.size();
		for (auto & l : this->layer)
		{
			l.Serialize(ar);
		}

		ar << cameras.size();
		for (auto & c : cameras)
		{
			c.second->Serialize(ar);
		}

		currentCamera.Serialize(ar);

	}
	else
	{
		// TODO: add loading code here
		DWORD magic;
		ar >> magic;
		if (magic != 0x41445543)
			throw "wrong magic number";

		this->graphics.clear();
		this->layer.clear();
		this->cameras.clear();

		long long int graphicCount;
		ar >> graphicCount;
		for (auto i = 0; i < graphicCount; i++)
		{
			Graphic * g = new Graphic;
			g->Serialize(ar);
			this->graphics[g->guid] = std::auto_ptr<Graphic>(g);
		}

		long long int layerCount;
		ar >> layerCount;
		for (auto i = 0; i < layerCount; i++)
		{
			GUID_ guid;
			guid.Serialize(ar);
			this->layer.push_back(guid);
		}

		long long int cameraCount;
		ar >> cameraCount;
		if (cameraCount == 0)
			throw "default camera not found";
		for (auto i = 0; i < cameraCount; i++)
		{
			GraphicCamera * c = new GraphicCamera;
			c->Serialize(ar);
			cameras[c->guid] = std::auto_ptr<GraphicCamera>(c);
		}

		currentCamera.Serialize(ar);

		POSITION pos = GetFirstViewPosition();
		auto view = GetNextView(pos);
		if (view != nullptr)
		{
			view->PostMessageW(WM_VIEW_RESET);
		}
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CguiDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CguiDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CguiDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CguiDoc diagnostics

#ifdef _DEBUG
void CguiDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CguiDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CguiDoc commands


BOOL CguiDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	POSITION pos = GetFirstViewPosition();
	auto view = GetNextView(pos);
	if (view != nullptr)
	{
		view->PostMessageW(WM_VIEW_RESET);
	}

	return TRUE;
}
