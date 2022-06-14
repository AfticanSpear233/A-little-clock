// m_Main.cpp: 实现文件
//

#include "pch.h"
#include "A G.h"
#include "afxdialogex.h"
#include "m_Main.h"


// m_Main 对话框

IMPLEMENT_DYNAMIC(m_Main, CDialogEx)

m_Main::m_Main(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_A_G_DIALOG, pParent)
{

}

m_Main::~m_Main()
{
}

void m_Main::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(m_Main, CDialogEx)
END_MESSAGE_MAP()


// m_Main 消息处理程序
