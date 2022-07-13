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
	, m_hour(0)
	, m_minu(0)
	, m_sec(0)
{

}

alaming::~alaming()
{
}

void alaming::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AlaList, AList);
	DDX_Text(pDX, IDC_hour, m_hour);
	DDX_Text(pDX, IDC_minu, m_minu);
	DDX_Text(pDX, IDC_sec, m_sec);
}


BEGIN_MESSAGE_MAP(alaming, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &alaming::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &alaming::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_import, &alaming::OnBnClickedimport)
	ON_BN_CLICKED(IDCANCEL, &alaming::OnBnClickedCancel)
	ON_EN_SETFOCUS(IDC_hour, &alaming::OnEnSetfocushour)
	ON_EN_SETFOCUS(IDC_minu, &alaming::OnEnSetfocusminu)
	ON_EN_SETFOCUS(IDC_sec, &alaming::OnEnSetfocussec)
END_MESSAGE_MAP()


// alaming 消息处理程序

void alaming::OnBnClickedButton1()
{
	DWORD unused{};
	TCHAR check[512];
	HANDLE DI = CreateFile(L"clockdata", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);//存储数字
	ReadFile(DI, &check, GetFileSize(DI, 0), &unused, 0);
	CString CH = check;
	// TODO: 在此添加控件通知处理程序代码
	CString times{}, temp{}, data{};
	int a = 0;
	UpdateData();
	GetDlgItem(IDC_attach)->GetWindowTextW(temp);
	a = m_hour * 3600 + m_minu * 60 + m_sec;
	temp.Format(_T("%dh%dm%ds     attach:%s\r\n"), m_hour, m_minu, m_sec, temp);
	data.Format(_T("%d\r\n"), a);
	if (CH.Find(data)+1)
	{
		MessageBox(L"闹钟重复，请删除后再设置");
		GetDlgItem(IDC_hour)->SetWindowTextW(0);
		GetDlgItem(IDC_minu)->SetWindowTextW(0);
		GetDlgItem(IDC_sec)->SetWindowTextW(0);
		GetDlgItem(IDC_attach)->SetWindowTextW(0);
		return;
	}
	CListBox* ALi = (CListBox*)GetDlgItem(IDC_AlaList);
	ALi->InsertString(0, temp);
	CListBox* PL = (CListBox*)GetParent()->GetDlgItem(IDC_clocklist);
	PL->InsertString(0, temp);
	HANDLE CI = CreateFile(L"clockinfo", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	SetFilePointer(CI, GetFileSize(CI, 0), NULL, FILE_BEGIN);
	SetFilePointer(DI, GetFileSize(DI, 0), NULL, FILE_BEGIN);
	WriteFile(CI, temp, sizeof(TCHAR)*temp.GetLength(), &unused, 0);
	WriteFile(DI, data, sizeof(TCHAR)*data.GetLength(), &unused, 0);
	CloseHandle(CI);
	CloseHandle(DI);

	//
	GetDlgItem(IDC_hour)->SetWindowTextW(0);
	GetDlgItem(IDC_minu)->SetWindowTextW(0);
	GetDlgItem(IDC_sec)->SetWindowTextW(0);
	GetDlgItem(IDC_attach)->SetWindowTextW(0);
	//GetParent()->PostMessageW(WM_PAINT);
}


void alaming::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码s
	CListBox* ALi = (CListBox*)GetDlgItem(IDC_AlaList);
	DWORD unused;
	CString del{};
	int choi=ALi->GetAnchorIndex();

	ALi->GetText(choi, del);
	ALi->DeleteString(choi);

	HANDLE CI = CreateFile(L"clockinfo", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	HANDLE DI = CreateFile(L"clockdata", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);//存储数字
	TCHAR a[512]{},b[512]{};
	ReadFile(CI, &a, GetFileSize(CI, 0), &unused, 0);
	ReadFile(DI, &b, GetFileSize(CI, 0), &unused, 0);
	//清空文件
	SetFilePointer(CI, 0, 0, FILE_BEGIN);
	SetEndOfFile(CI);
	SetFilePointer(DI, 0, 0, FILE_BEGIN);
	SetEndOfFile(DI);

	CString mun{};
	int index = 0,down=0;
	for (int i=0;i<=512;i++)
	{		if (b[i] == NULL)
		{
			break;
		}
		if (b[i]=='\n')
		{
			index++;
			if (choi+1==index)
			{
				for (int j = i - 1;; j--)
				{
					if (b[j] == '\n' || j == -1)
					{
						break;
					}
					mun += b[j];
				}
				break;
			}
		}
	}
	mun.MakeReverse();
	mun += '\n';
	CString d, e;
	e.Insert(0, b);
	d.Insert(0, a);
	e.Replace(mun, 0);
	d.Replace(del, 0);
	//e.Delete(e.GetLength()-1);
	//d.Delete(d.GetLength()-1);
	WriteFile(CI, d, sizeof(TCHAR) * d.GetLength(), &unused, 0);
	WriteFile(DI, e, sizeof(TCHAR) * e.GetLength(), &unused, 0);
	CloseHandle(CI);
	CWnd *se= GetParent();
	CListBox *pa=(CListBox*)se->GetDlgItem(IDC_clocklist);
	pa->DeleteString(choi);
}


void alaming::OnBnClickedimport()
{
	// TODO: 在此添加控件通知处理程序代码
	CListBox* PL = (CListBox*)GetParent()->GetDlgItem(IDC_clocklist);
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
		if (temp[i]=='\n')
		{
			for (int j=0;j<le;j++)
			{
				times += temp[i-j];
			}
			le = 0;
			times.MakeReverse();
			times.Remove('@');
			ALi->InsertString(0, times);
			PL->InsertString(0, times);
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


void alaming::OnEnSetfocushour()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_hour)->SetWindowTextW(0);
}


void alaming::OnEnSetfocusminu()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_minu)->SetWindowTextW(0);
}


void alaming::OnEnSetfocussec()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_sec)->SetWindowTextW(0);
}
