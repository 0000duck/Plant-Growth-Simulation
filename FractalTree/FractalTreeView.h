
// FractalTreeView.h : CFractalTreeView ��Ľӿ�
//
#include "OpenGL.h"
#pragma once


class CFractalTreeView : public CView
{
protected: // �������л�����
	CFractalTreeView();
	DECLARE_DYNCREATE(CFractalTreeView)
	COpenGL opengl;
// ����
public:
	CFractalTreeDoc* GetDocument() const;

// ����
public:
	void OnInitialUpdate();
	
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CFractalTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSetdata();
	afx_msg void OnReset();
};

#ifndef _DEBUG  // FractalTreeView.cpp �еĵ��԰汾
inline CFractalTreeDoc* CFractalTreeView::GetDocument() const
   { return reinterpret_cast<CFractalTreeDoc*>(m_pDocument); }
#endif

