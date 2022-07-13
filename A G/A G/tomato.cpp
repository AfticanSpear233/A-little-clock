// tomato.cpp: 实现文件
//

#include "pch.h"
#include "A G.h"
#include "afxdialogex.h"
#include "tomato.h"


// tomato 对话框

IMPLEMENT_DYNAMIC(tomato, CDialogEx)

tomato::tomato(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_tomato, pParent)
{

}

tomato::~tomato()
{
}

void tomato::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(tomato, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &tomato::OnBnClickedCancel)
END_MESSAGE_MAP()


// tomato 消息处理程序


void tomato::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	DestroyWindow();
}


