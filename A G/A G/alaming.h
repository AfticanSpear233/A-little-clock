#pragma once
#include "afxdialogex.h"


// alaming 对话框

class alaming : public CDialogEx
{
	DECLARE_DYNAMIC(alaming)

public:
	alaming(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~alaming();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_alaming };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CListBox AList;
	afx_msg void OnBnClickedimport();
	afx_msg void OnBnClickedCancel();
	int m_hour;
	int m_minu;
	int m_sec;
	afx_msg void OnEnSetfocushour();
	afx_msg void OnEnSetfocusminu();
	afx_msg void OnEnSetfocussec();
};
