#pragma once
#include "afxdialogex.h"


// CFILESAVE 对话框

class CFILESAVE : public CDialogEx
{
	DECLARE_DYNAMIC(CFILESAVE)

public:
	CFILESAVE(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFILESAVE();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILESAVE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CMFCShellTreeCtrl m_shellTree_save;
	CString m_filewin_str;
	CString save_path;
	afx_msg void OnTvnSelchangedMfcshelltree1(NMHDR* pNMHDR, LRESULT* pResult);
};
