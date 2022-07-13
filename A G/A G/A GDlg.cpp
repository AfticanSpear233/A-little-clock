
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
#include<mmsystem.h>
#pragma comment (lib,"winmm.lib")
//#include "resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static BOOL pressd = 0;
static int timenow = 0;
UINT Mai(LPVOID wparam);
UINT CoC(LPVOID wparam);
UINT rang(LPVOID wparam);
UINT mation(LPVOID wparam);
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
	DDX_Control(pDX, IDC_PROGRESS1, DalyPro);
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
static HWND cl{},mai{},test{};
CString sh;
int fir = 1;
static CProgressCtrl* CP;
void CAGDlg::OnPaint()
{
	if (fir)
	{
		test = GetDlgItem(aaaaa)->GetSafeHwnd();
		CP = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
		mai=::GetParent(GetDlgItem(IDC_clock)->GetSafeHwnd());
		cl = GetDlgItem(IDC_clock)->GetSafeHwnd();
		AfxBeginThread(Mai, 0);
		AfxBeginThread(CoC, 0);
		AfxBeginThread(rang, 0);
		fir = 0;
	}
	CString lis;
	DWORD unused;
	TCHAR read[512]{};
	HANDLE CI = CreateFile(L"clockinfo", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	ReadFile(CI, read, GetFileSize(CI, 0), &unused, 0);
	int j = 0;
	for (int i=0;i<=512;i++)
	{
		if (!read[i])
		{
			break;
		}
		if (read[i]=='\n')
		{
			for (j;j<i;j++)
			{
				lis += read[j];
			}
			clocklist.InsertString(0,lis);
		}
		lis.Empty();
		//clocklist.DeleteString(clocklist.GetCount());
	}
	CloseHandle(CI);
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
static int Time, hour, minu, second;
UINT Mai(LPVOID wparam)
{
	CString b{};
	while (1)
	{
		
		/*M.GetDlgItem(IDC_clock)->SetWindowTextW(L"123");*/
		Time = time(0);
		hour = (Time / 3600 % 24) + 8;
		minu = Time / 60 % 60;
		second = Time % 60;
		timenow = hour * 3600 + minu * 60 + second;
		b.Format(_T("%d"),timenow);
		sh.Format(_T("现在时间:%d:%d:%d"), hour, minu, second);
		SetWindowText(cl, sh);
		SetWindowTextW(test, b);
		Sleep(1000);
	}
	return 0;
}

UINT CoC(LPVOID wparam)
{
	//CListCtrl a;
	//CProgressCtrl *CP=(CProgressCtrl*) GetDlgItem(mai, IDC_PROGRESS1);
	//CP->SetRange(0, 86400);
	int end = hour * 3600 + minu * 60 + second;
	int sus = 0;
	
	CP->SetRange(0, 21600);
	CP->OffsetPos(end/4);
	while (true)
	{
		sus++;
		if (sus%4)
		{}
		else
		{
			CP->OffsetPos(1);
			sus = 0;
		}
		//timenow = CP->GetPos() * 4;
		Sleep(1000);
	}
	return 0;
}

UINT rang(LPVOID wparam)
{
	DWORD unused;
	TCHAR RanS[512]={0};
	CString R;
	while (true)
	{
		int allS[64] = { 0 };//存储闹钟列表
		int site = 0;//指针
		//CP->GetPos()
		CP->GetPos() * 4;
		HANDLE CI = CreateFile(L"clockdata", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		ReadFile(CI, &RanS, GetFileSize(CI, 0), &unused, 0);//阅读文件记录时间
		R = RanS;//TCHAR类型转换为CString
		for (int i = 0; i < R.GetLength(); i++)//CString转换为int
		{
			int tes = 0;
			if (R[i] == '\n')
			{
				site++;
				continue;
			}
			if (R[i] == '\r')
			{
				continue;
			}
			allS[site] *= 10;
			allS[site] += (R[i] - '0');
		}
		for (int i=0;;i++)
		{
			if (allS[i] == 0)
			{
				break;
			}
			if (abs(allS[i]==timenow))
			{
				AfxBeginThread(mation, 0);
				Sleep(1000);
			}
		}
	}
	return 0;
}

UINT mation(LPVOID wparam)
{
	PlaySound(L"rang.wav", 0, SND_ASYNC | SND_FILENAME | SND_LOOP | SND_SYSTEM);
	MessageBox(0, L"ramg", L"rang", MB_OK);
	PlaySound(0, 0, SND_PURGE | SND_FILENAME);
	pressd = 0;
	return 0;
}

alaming AL;
void CAGDlg::OnBnClickedalaming()
{
	// TODO: 在此添加控件通知处理程序代码
	AL.Create(IDD_alaming);
	AL.ShowWindow(SW_SHOW);

	CString lis;
	DWORD unused;
	TCHAR read[512]{};
	HANDLE CI = CreateFile(L"clockinfo", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	ReadFile(CI, read, GetFileSize(CI, 0), &unused, 0);
	int j = 0;
	for (int i = 0; i <= 512; i++)
	{
		if (!read[i])
		{
			break;
		}
		if (read[i] == '\n')
		{
			for (j; j < i; j++)
			{
				lis += read[j];
			}
			lis.Remove('@');
			CListBox *CHC=(CListBox*) AL.GetDlgItem(IDC_AlaList);
			CHC->InsertString(0, lis);
			j++;
		}
		lis.Empty();
	}
	CloseHandle(CI);
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
