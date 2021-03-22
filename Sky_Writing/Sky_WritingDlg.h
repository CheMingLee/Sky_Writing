// Sky_WritingDlg.h : 標頭檔
//
#include "RTC6impl.h"
#pragma once


// CSky_WritingDlg 對話方塊
class CSky_WritingDlg : public CDialog
{
// 建構
public:
	CSky_WritingDlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
	enum { IDD = IDD_SKY_WRITING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void Scan_System_Initialization();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonSetParams();
};
