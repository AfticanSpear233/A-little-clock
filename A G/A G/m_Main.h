#pragma once
#include "afxdialogex.h"


// m_Main 对话框

class m_Main : public CDialogEx
{
	DECLARE_DYNAMIC(m_Main)

public:
	m_Main(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~m_Main();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_A_G_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
