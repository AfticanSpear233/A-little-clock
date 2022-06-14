#pragma once
#include "afxdialogex.h"


// tomato 对话框

class tomato : public CDialogEx
{
	DECLARE_DYNAMIC(tomato)

public:
	tomato(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~tomato();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_tomato };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
