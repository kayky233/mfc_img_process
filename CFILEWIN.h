#pragma once
#include "afxdialogex.h"


// CFILEWIN 对话框

class CFILEWIN : public CDialogEx
{
	DECLARE_DYNAMIC(CFILEWIN)

public:
	CFILEWIN(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFILEWIN();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILEWIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMFCShellTreeCtrl m_shellTree;
	CMFCShellListCtrl m_shellList;
	afx_msg void OnTvnSelchangedMfcshelltree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMClickMfcshelllist1(NMHDR* pNMHDR, LRESULT* pResult);

	CString m_filewin_str;
};
