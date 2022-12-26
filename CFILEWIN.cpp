// CFILEWIN.cpp: 实现文件
//

#include "pch.h"
#include "MFCSEG.h"
#include "afxdialogex.h"
#include "CFILEWIN.h"


// CFILEWIN 对话框

IMPLEMENT_DYNAMIC(CFILEWIN, CDialogEx)

CFILEWIN::CFILEWIN(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILEWIN, pParent)
{

}

CFILEWIN::~CFILEWIN()
{
}

void CFILEWIN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCSHELLTREE1, m_shellTree);
	DDX_Control(pDX, IDC_MFCSHELLLIST1, m_shellList);
}


BEGIN_MESSAGE_MAP(CFILEWIN, CDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_MFCSHELLTREE1, &CFILEWIN::OnTvnSelchangedMfcshelltree1)
	ON_NOTIFY(NM_CLICK, IDC_MFCSHELLLIST1, &CFILEWIN::OnNMClickMfcshelllist1)
END_MESSAGE_MAP()


// CFILEWIN 消息处理程序

// 点击目录树
void CFILEWIN::OnTvnSelchangedMfcshelltree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	CString str_path;
	m_shellTree.GetItemPath(str_path,pNMTreeView->itemNew.hItem);
	m_shellList.DisplayFolder(str_path);


	*pResult = 0;
}

//点击shelllist组件
void CFILEWIN::OnNMClickMfcshelllist1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CString Filename;
	for (int i = 0; i < m_shellList.GetItemCount(); i++)
	{
		if (m_shellList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			m_shellList.GetItemPath(Filename,i);
			//MessageBox(Filename);
			m_filewin_str = Filename;
		}
	}






	*pResult = 0;
}
