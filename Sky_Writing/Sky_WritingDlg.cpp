// Sky_WritingDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "Sky_Writing.h"
#include "Sky_WritingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 對話方塊資料
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSky_WritingDlg 對話方塊




CSky_WritingDlg::CSky_WritingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSky_WritingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSky_WritingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSky_WritingDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_SET_PARAMS, &CSky_WritingDlg::OnBnClickedButtonSetParams)
END_MESSAGE_MAP()


// CSky_WritingDlg 訊息處理常式

BOOL CSky_WritingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定


	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CSky_WritingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CSky_WritingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CSky_WritingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSky_WritingDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此加入您的訊息處理常式程式碼
	free_rtc5_dll();
}

void CSky_WritingDlg::Scan_System_Initialization()
{
	init_rtc5_dll();

	(void) select_rtc(1);
	set_rtc4_mode();
	stop_execution();
	load_program_file(NULL);

	// Setting the CO2 laser mode
	set_laser_mode(0);
	// Setting and enabling the “laser active” laser control signals
	set_laser_control(0x18); // All laser signals LOW active (Bit #3 and #4)
}

void CSky_WritingDlg::OnBnClickedButtonSetParams()
{
	// Opens List 1
	set_start_list(1);
	// Setting the standby pulses
	set_standby(800, 8);
	// In RTC4 compatibility mode the standby parameters are specified in units of 1/8 μs as with the RTC4 and the
	// RTC5 multiplies the specified values by 8 to convert in integer-multiple of 1/64 μs.
	// Half of the standby output period = 100 μs
	// Pulse length of the standby pulses = 1 μs

	// Timing, delay and speed preset

	// Setting the scanner delays:
	set_scanner_delays(25, 10, 5);
	// Jump delay = 250 μs (specified in [10 μs])
	// Mark delay = 100 μs (specified in [10 μs])
	// Polygon delay = 50 μs (specified in [10 μs])
	
	// Setting the jump and marking speed:
	set_jump_speed(1000.0);
	set_mark_speed(250.0);
	// In RTC4 compatibility mode the speed values are specified as with the RTC4 and the RTC5 multiplies the specified
	// values by 16.
	// Jump speed = 1000.0 bits/ms
	// Marking speed = 250.0 bits/ms

	// Setting the laser timing:
	set_laser_pulses(800, 400);
	// In RTC4 compatibility mode the timing parameters are specified in units of 1/8 μs as with the RTC4 and the RTC5
	// multiplies the specified values by 8 to convert in integer-multiple of 1/64 μs.
	// Laser HalfPeriod = 100 μs
	// Laser PulseLength = 50 μs

	// Setting the laser delays:
	set_laser_delays(100, 100);
	// In RTC4 compatibility mode the laser delays are specified in units of 1 μs as with the RTC4 and the RTC5
	// multiplies the specified values by 2 to convert in integer-multiple of 0.5 μs.
	// LaserOn delay = 100 μs
	// LaserOff delay = 100 μs

	// Defining the end of the list and the end of command transfer to the RTC5 Board
	set_end_of_list();
	// Execute the list commands for initialization
	execute_list(1);
}
