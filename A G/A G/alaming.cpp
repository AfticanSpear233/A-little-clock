// alaming.cpp: 实现文件
//

#include "pch.h"
#include "A G.h"
#include "afxdialogex.h"
#include "alaming.h"
#include "Resource.h"


// alaming 对话框

IMPLEMENT_DYNAMIC(alaming, CDialogEx)

alaming::alaming(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_alaming, pParent)
{

}

alaming::~alaming()
{
}

void alaming::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AlaList, AList);
}


BEGIN_MESSAGE_MAP(alaming, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &alaming::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &alaming::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_import, &alaming::OnBnClickedimport)
	ON_BN_CLICKED(IDCANCEL, &alaming::OnBnClickedCancel)
END_MESSAGE_MAP()


// alaming 消息处理程序

void alaming::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString times{},temp{};
	GetDlgItemText(IDC_hour, temp);
	times += temp;
	times += "h";
	GetDlgItemText(IDC_minu, temp);
	times += temp;
	times += "m";
	GetDlgItemText(IDC_sec, temp);
	times += temp;
	times += "s	        attach:";
	GetDlgItemText(IDC_attach, temp);
	times += temp;
	
	CListBox* ALi = (CListBox*)GetDlgItem(IDC_AlaList);
	ALi->InsertString(0, times);
	HANDLE CI= CreateFile(L"clockinfo", GENERIC_WRITE| GENERIC_READ, FILE_SHARE_WRITE| FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	DWORD unused{};
	int log=times.GetLength();
	times += L"@\n";
	//ReadFile(CI, NULL, GetFileSize(CI, 0), NULL, 0);
	SetFilePointer(CI, GetFileSize(CI, 0), NULL, FILE_BEGIN);
	WriteFile(CI, times, sizeof(TCHAR)*times.GetLength(), &unused, 0);
	CloseHandle(CI);
	GetDlgItem(IDC_hour)->SetWindowTextW(0);
	GetDlgItem(IDC_minu)->SetWindowTextW(0);
	GetDlgItem(IDC_sec)->SetWindowTextW(0);
	GetDlgItem(IDC_attach)->SetWindowTextW(0);
	GetParent()->PostMessageW(WM_PAINT);
}


void alaming::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CListBox* ALi = (CListBox*)GetDlgItem(IDC_AlaList);
	DWORD unused;
	TCHAR del[512]{};
	int choi=ALi->GetAnchorIndex();
	ALi->GetText(choi, del);
	ALi->DeleteString(choi);
	HANDLE CI = CreateFile(L"clockinfo", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	TCHAR a[512]{};
	ReadFile(CI, &a, GetFileSize(CI, 0), &unused, 0);
	
	SetFilePointer(CI, 0, 0, FILE_BEGIN);
	SetEndOfFile(CI);
	for (int i=0;i<=512;i++)
	{
		if (!del[i])
		{
			del[i] = '@';
			del[i + 1] = '\n';
			break;
		}
	}

	CString d;
	d.Insert(0, a);
	d.Replace(del, 0);
	WriteFile(CI, d, sizeof(TCHAR) * d.GetLength(), &unused, 0);
	CloseHandle(CI);
	CWnd *se= GetParent();
	CListBox *pa=(CListBox*)se->GetDlgItem(IDC_clocklist);
	pa->DeleteString(choi);
}


void alaming::OnBnClickedimport()
{
	// TODO: 在此添加控件通知处理程序代码
	CString times;
	TCHAR temp[512]={0};
	HANDLE CI = CreateFile(L"clockinfo", GENERIC_READ| GENERIC_WRITE, FILE_SHARE_READ| FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	DWORD unused{};
	CListBox* ALi = (CListBox*)GetDlgItem(IDC_AlaList);
	ReadFile(CI, temp, GetFileSize(CI, 0), &unused, 0);
	int le = 0;
	for (int i=0;i<=512;i++)
	{
		le++;
		if (!temp[i])
		{
			break;
		}
		if (temp[i]=='@')
		{
			for (int j=0;j<le;j++)
			{
				times += temp[i-j];
			}
			le = 0;
			times.Remove('@');
			times.MakeReverse();
			ALi->InsertString(0, times);
			continue;
		}
		times.Empty();
	}
	times = temp;
	CloseHandle(CI);
}


void alaming::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	DestroyWindow();
	//CDialogEx::OnCancel();
}
