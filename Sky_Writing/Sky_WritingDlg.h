// Sky_WritingDlg.h : ���Y��
//
#include "RTC6impl.h"
#pragma once#include "afxwin.h"



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
	double m_XYRatio;
	bool m_bListFlag;
	UINT m_u32Jump_delay, m_u32Mark_delay, m_u32Polygon_delay;
	double m_dJumpSpeed, m_dMarkSpeed;
	UINT m_u32HalfPeriod, m_u32PulseLength;
	long m_LgLaserOnDelay;
	UINT m_u32LaserOffDelay;
	double m_dTimelag;
	long m_LgLaserOnShift;
	UINT m_u32Nprev, m_u32Npost;
	UINT m_u32Mode;
	double m_dCosAngle;
	UINT m_u32Standby_HfPeriod, m_u32Standby_PlsLen;
	void Scan_System_Initialization();
	void SetParams();
	void SetSkyList();
	void SetSkyListFlag();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonSkywLine();
	afx_msg void OnBnClickedButtonSkyrArc();
	CButton m_ckListFlag;
	afx_msg void OnBnClickedButtonSetSky();
	afx_msg void OnBnClickedCheckSkyListFlag();
};
