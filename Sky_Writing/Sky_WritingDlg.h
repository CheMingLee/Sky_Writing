// Sky_WritingDlg.h : ���Y��
//
#include "RTC6impl.h"
#pragma once


// CSky_WritingDlg ��ܤ��
class CSky_WritingDlg : public CDialog
{
// �غc
public:
	CSky_WritingDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
	enum { IDD = IDD_SKY_WRITING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
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
