
// A GDlg.h: 头文件
//

#pragma once


// CAGDlg 对话框
class CAGDlg : public CDialogEx
{
// 构造
public:
	CAGDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_A_G_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedalaming();
	afx_msg void OnBnClickedtomato();
	afx_msg void OnBnClickedoptins();
	afx_msg void OnBnClickedscudule();
	CListBox clocklist;
	CProgressCtrl DalyPro;
};
