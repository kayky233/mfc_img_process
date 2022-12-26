// CFILESAVE.cpp: 实现文件
//

#include "pch.h"
#include "MFCSEG.h"
#include "afxdialogex.h"
#include "CFILESAVE.h"


// CFILESAVE 对话框

IMPLEMENT_DYNAMIC(CFILESAVE, CDialogEx)

CFILESAVE::CFILESAVE(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILESAVE, pParent)
{

}

CFILESAVE::~CFILESAVE()
{
}

void CFILESAVE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCSHELLTREE1, m_shellTree_save);
}


BEGIN_MESSAGE_MAP(CFILESAVE, CDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_MFCSHELLTREE1, &CFILESAVE::OnTvnSelchangedMfcshelltree1)
END_MESSAGE_MAP()


// CFILESAVE 消息处理程序


void CFILESAVE::OnTvnSelchangedMfcshelltree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CString str_path;
	m_shellTree_save.GetItemPath(str_path, pNMTreeView->itemNew.hItem);
	//MessageBox(str_path);
	//MessageBox(TEXT("已经选中路径: " + str_path + "，请退出窗口后点击选择"), L"提示");
	m_filewin_str = str_path;



	*pResult = 0;
}
