// Sky_WritingDlg.cpp : ��@��
//

#include "stdafx.h"
#include "Sky_Writing.h"
#include "Sky_WritingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �� App About �ϥ� CAboutDlg ��ܤ��

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ܤ�����
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

// �{���X��@
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


// CSky_WritingDlg ��ܤ��




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


// CSky_WritingDlg �T���B�z�`��

BOOL CSky_WritingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �N [����...] �\���[�J�t�Υ\���C

	// IDM_ABOUTBOX �����b�t�ΩR�O�d�򤧤��C
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

	// �]�w����ܤ�����ϥܡC�����ε{�����D�������O��ܤ���ɡA
	// �ج[�|�۰ʱq�Ʀ��@�~
	SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
	SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�

	// TODO: �b���[�J�B�~����l�]�w


	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
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

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void CSky_WritingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ø�s���˸m���e

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N�ϥܸm����Τ�ݯx��
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �yø�ϥ�
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ��ϥΪ̩즲�̤p�Ƶ����ɡA
// �t�ΩI�s�o�ӥ\����o�����ܡC
HCURSOR CSky_WritingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSky_WritingDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �b���[�J�z���T���B�z�`���{���X
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
	// Setting and enabling the ��laser active�� laser control signals
	set_laser_control(0x18); // All laser signals LOW active (Bit #3 and #4)
}

void CSky_WritingDlg::OnBnClickedButtonSetParams()
{
	// Opens List 1
	set_start_list(1);
	// Setting the standby pulses
	set_standby(800, 8);
	// In RTC4 compatibility mode the standby parameters are specified in units of 1/8 �gs as with the RTC4 and the
	// RTC5 multiplies the specified values by 8 to convert in integer-multiple of 1/64 �gs.
	// Half of the standby output period = 100 �gs
	// Pulse length of the standby pulses = 1 �gs

	// Timing, delay and speed preset

	// Setting the scanner delays:
	set_scanner_delays(25, 10, 5);
	// Jump delay = 250 �gs (specified in [10 �gs])
	// Mark delay = 100 �gs (specified in [10 �gs])
	// Polygon delay = 50 �gs (specified in [10 �gs])
	
	// Setting the jump and marking speed:
	set_jump_speed(1000.0);
	set_mark_speed(250.0);
	// In RTC4 compatibility mode the speed values are specified as with the RTC4 and the RTC5 multiplies the specified
	// values by 16.
	// Jump speed = 1000.0 bits/ms
	// Marking speed = 250.0 bits/ms

	// Setting the laser timing:
	set_laser_pulses(800, 400);
	// In RTC4 compatibility mode the timing parameters are specified in units of 1/8 �gs as with the RTC4 and the RTC5
	// multiplies the specified values by 8 to convert in integer-multiple of 1/64 �gs.
	// Laser HalfPeriod = 100 �gs
	// Laser PulseLength = 50 �gs

	// Setting the laser delays:
	set_laser_delays(100, 100);
	// In RTC4 compatibility mode the laser delays are specified in units of 1 �gs as with the RTC4 and the RTC5
	// multiplies the specified values by 2 to convert in integer-multiple of 0.5 �gs.
	// LaserOn delay = 100 �gs
	// LaserOff delay = 100 �gs

	// Defining the end of the list and the end of command transfer to the RTC5 Board
	set_end_of_list();
	// Execute the list commands for initialization
	execute_list(1);
}
