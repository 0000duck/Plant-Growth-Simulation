
// FractalTreeView.cpp : CFractalTreeView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "FractalTree.h"
#endif

#include "FractalTreeDoc.h"
#include "FractalTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "OpenGL.h"
#include "MyDialog.h"

// CFractalTreeView

IMPLEMENT_DYNCREATE(CFractalTreeView, CView)

BEGIN_MESSAGE_MAP(CFractalTreeView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_setData, &CFractalTreeView::OnSetdata)
	ON_COMMAND(ID_Reset, &CFractalTreeView::OnReset)
END_MESSAGE_MAP()

// CFractalTreeView ����/����

CFractalTreeView::CFractalTreeView()
{
	// TODO: �ڴ˴���ӹ������

}

CFractalTreeView::~CFractalTreeView()
{
}

BOOL CFractalTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);

}

// CFractalTreeView ����

void CFractalTreeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
 	// TODO: д������ѡ��ģʽ����֮���Ƴ��˴���
	//m_pSelection = NULL;    // ��ʼ����ѡ����
	opengl.SetupPixelFormat(::GetDC(GetSafeHwnd()));
	opengl.SetupRC();
}


void CFractalTreeView::OnDraw(CDC* /*pDC*/)
{
	CFractalTreeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

	opengl.RenderSence();  //���Ƴ���
	//glFlush();
	
}


// CFractalTreeView ��ӡ

BOOL CFractalTreeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CFractalTreeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CFractalTreeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CFractalTreeView ���

#ifdef _DEBUG
void CFractalTreeView::AssertValid() const
{
	CView::AssertValid();
}

void CFractalTreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFractalTreeDoc* CFractalTreeView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFractalTreeDoc)));
	return (CFractalTreeDoc*)m_pDocument;
}
#endif //_DEBUG


// CFractalTreeView ��Ϣ�������


void CFractalTreeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	opengl.ChangeSize(cx, cy);
	
}


void CFractalTreeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int n = 0;
	int m = 0;
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	if (nChar == VK_UP) {
		RedrawWindow();
		opengl.SpecialKeys(nChar, 0, 0);
	}
		

	if (nChar == VK_DOWN) {
		opengl.SpecialKeys(nChar, 0, 0);
		RedrawWindow();
	}

	if (nChar == VK_LEFT) {
		opengl.SpecialKeys(nChar, 0, 0);
		RedrawWindow();
	}

	if (nChar == VK_RIGHT) {
		
		opengl.SpecialKeys(nChar, 0, 0);
		RedrawWindow();
	}

	if (nChar == VK_SPACE) {
		while (n < 6) {
			opengl.tree.setN(n);
			opengl.tree.setbaseTall(n + m);
			if(n < 3)
				m = m + 1;
			RedrawWindow();
			n++;
		}
	}

	if (nChar == 82) {
		opengl.tree.setbaseTall(8);
		opengl.tree.setbaseR(6);
		opengl.tree.setAngle(55);
		opengl.tree.setleaf(9);
		opengl.tree.setM(0.65);
		opengl.tree.setN(5);
		opengl.tree.setQ(0.5);
		Tree::img = opengl.tree.loadPNGTexture("leaf.png");
		Tree::shape = 0;
		RedrawWindow();
	}
	
}


BOOL CFractalTreeView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return true;
}


void CFractalTreeView::OnSetdata()
{
	// TODO: �ڴ���������������
	CMyDialog dlg;
	//��ȡ��ǰ�Ĳ���
	dlg.m_n = opengl.tree.getN();
	dlg.m_high = opengl.tree.getbaseTall();
	dlg.m_M = opengl.tree.getm();
	dlg.m_angle = opengl.tree.getAngle();
	dlg.m_leaf = opengl.tree.getleaf();
	dlg.m_width = opengl.tree.getbaseR();
	dlg.m_q = opengl.tree.getq();
	UpdateData(false);
	if (CMyDialog::radioState == 1) {
		dlg.m_iRadio = 1;
		//CheckRadioButton(IDC_RADIO3, IDC_RADIO4, IDC_RADIO4);
	}
	

	UpdateData(true);
	if (IDOK == dlg.DoModal()) {
		opengl.tree.setN(dlg.m_n);
		opengl.tree.setbaseTall(dlg.m_high);
		opengl.tree.setM(dlg.m_M);
		opengl.tree.setAngle(dlg.m_angle);
		opengl.tree.setleaf(dlg.m_leaf);
		opengl.tree.setbaseR(dlg.m_width);
		opengl.tree.setQ(dlg.m_q);
	}
	else
		return;
	RedrawWindow();
	opengl.RenderSence();
}


void CFractalTreeView::OnReset()
{
	// TODO: �ڴ���������������
	opengl.tree.setbaseTall(8);
	opengl.tree.setbaseR(6);
	opengl.tree.setAngle(55);
	opengl.tree.setleaf(9);
	opengl.tree.setM(0.65);
	opengl.tree.setN(5);
	opengl.tree.setQ(0.5);
	Tree::img = opengl.tree.loadPNGTexture("leaf.png");
	Tree::shape = 0;
	RedrawWindow();
}
