
// A GDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "A G.h"
#include "A GDlg.h"
#include "afxdialogex.h"
#include "m_Main.h"
#include "Resource.h"
#include "alaming.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT Mai(LPVOID wparam);
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAGDlg 对话框



CAGDlg::CAGDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_A_G_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_clocklist, clocklist);
}

BEGIN_MESSAGE_MAP(CAGDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_BUTTON1, &CAGDlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_alaming, &CAGDlg::OnBnClickedalaming)
ON_BN_CLICKED(IDC_tomato, &CAGDlg::OnBnClickedtomato)
ON_BN_CLICKED(IDC_optins, &CAGDlg::OnBnClickedoptins)
ON_BN_CLICKED(IDC_scudule, &CAGDlg::OnBnClickedscudule)
END_MESSAGE_MAP()


// CAGDlg 消息处理程序

BOOL CAGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAGDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
static HWND a{};
CString sh;
int fir = 1;
void CAGDlg::OnPaint()
{
	if (fir)
	{
		a = GetDlgItem(IDC_clock)->GetSafeHwnd();
		AfxBeginThread(Mai, 0);
		fir = 0;
	}
	CString lis;
	DWORD unused;
	TCHAR read[512]{};
	HANDLE CI = CreateFile(L"clockinfo", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	ReadFile(CI, read, GetFileSize(CI, 0), &unused, 0);
	for (int i=0;i<=512;i++)
	{
		int j=0;
		if (!read[i])
		{
			break;
		}
		if (read[i]=='@')
		{
			for (j;j<i;j++)
			{
				lis += read[j];
			}
			clocklist.InsertString(0,lis);
			
		}
		lis.Empty();
	}
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

UINT Mai(LPVOID wparam)
{
	while (1)
	{
		/*M.GetDlgItem(IDC_clock)->SetWindowTextW(L"123");*/
		int Time = time(0);
		int hour = (Time / 3600 % 24) + 8;
		int minu = Time / 60 % 60;
		int second = Time % 60;
		sh.Format(_T("现在时间:%d:%d:%d"), hour, minu, second);
		SetWindowText(a, sh);
		Sleep(1000);
	}
	return 0;
}

alaming AL;
void CAGDlg::OnBnClickedalaming()
{
	// TODO: 在此添加控件通知处理程序代码
	AL.Create(IDD_alaming);
	AL.ShowWindow(SW_SHOW);
}


void CAGDlg::OnBnClickedtomato()
{
	// TODO: 在此添加控件通知处理程序代码

}


void CAGDlg::OnBnClickedoptins()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CAGDlg::OnBnClickedscudule()
{
	// TODO: 在此添加控件通知处理程序代码
}
