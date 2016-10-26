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

// guiDoc.h : interface of the CguiDoc class
//


#pragma once

#include <vector>
#include <map>
#include <memory>
#include "Graphic.h"

class CguiDoc : public CDocument
{
protected: // create from serialization only
	CguiDoc();
	DECLARE_DYNCREATE(CguiDoc)

// Attributes
public:
	

// Operations
public:
	bool inited = false;
	std::map<GUID_, std::auto_ptr<Graphic>> grphics;// store the elements 
	std::vector<GUID_> layer;// store the order of layer
	std::map<GUID_, std::auto_ptr<GraphicCamera>> cameras; // store the camera
	GUID_ currentCamera;
	
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CguiDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};
