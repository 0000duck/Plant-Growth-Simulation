#pragma once
#include "afxwin.h"


// CMyDialog �Ի���

class CMyDialog : public CDialog
{
	DECLARE_DYNAMIC(CMyDialog)

public:
	CMyDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��������
	int m_n;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	
	// ��ʼ�߶�
	int m_high;
	
	// �߶����ű���
	float m_M;
	// ��֦���ϽǶ�
	float m_angle;
	// ҶƬ��Դ�С
	int m_leaf;
	// ��֦�ֶ����ű���
	float m_q;
	// ��ʼ��֦�ֶ�
	float m_width;
	afx_msg void OnBnClickedleaf1();
	afx_msg void OnBnClickedleaf2();
	afx_msg void OnBnClickedleaf3();
	afx_msg void OnBnClickedleaf4();
	CBitmapButton m_Btn1;
	CBitmapButton m_Btn2;
	CBitmapButton m_Btn3;
	CBitmapButton m_Btn4;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	int m_iRadio;

	static int radioState;
};
