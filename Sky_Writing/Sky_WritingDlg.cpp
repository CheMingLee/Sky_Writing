// Sky_WritingDlg.cpp : ��@��
//

#include "stdafx.h"
#include "Sky_Writing.h"
#include "Sky_WritingDlg.h"
#include "math.h"

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
	, m_u32Jump_delay(25)
	, m_u32Mark_delay(10)
	, m_u32Polygon_delay(5)
	, m_dJumpSpeed(2000.0)
	, m_dMarkSpeed(1000.0)
	, m_u32HalfPeriod(25)
	, m_u32PulseLength(20)
	, m_LgLaserOnDelay(0)
	, m_u32LaserOffDelay(0)
	, m_dTimelag(50)
	, m_LgLaserOnShift(10)
	, m_u32Nprev(500)
	, m_u32Npost(500)
	, m_u32Mode(1)
	, m_dCosAngle(0.49)
	, m_u32Standby_HfPeriod(100)
	, m_u32Standby_PlsLen(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSky_WritingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_JUMP_DELAY, m_u32Jump_delay);
	DDX_Text(pDX, IDC_EDIT_MARK_DELAY, m_u32Mark_delay);
	DDX_Text(pDX, IDC_EDIT_POLY_DELAY, m_u32Polygon_delay);
	DDX_Text(pDX, IDC_EDIT_JUMP_SPEED, m_dJumpSpeed);
	DDX_Text(pDX, IDC_EDIT_MARK_SPEED, m_dMarkSpeed);
	DDX_Text(pDX, IDC_EDIT_HALF_PERIOD, m_u32HalfPeriod);
	DDX_Text(pDX, IDC_EDIT_PULSE_LENGTH, m_u32PulseLength);
	DDX_Text(pDX, IDC_EDIT_LASER_ON_DELAY, m_LgLaserOnDelay);
	DDX_Text(pDX, IDC_EDIT_LASER_OFF_DELAY, m_u32LaserOffDelay);
	DDX_Text(pDX, IDC_EDIT_STANDBY_HALF_PERIOD, m_u32Standby_HfPeriod);
	DDX_Text(pDX, IDC_EDIT_STANDBY_PULSE_LENGTH, m_u32Standby_PlsLen);
	DDX_Text(pDX, IDC_EDIT_SKY_TIMELAG, m_dTimelag);
	DDX_Text(pDX, IDC_EDIT_SKY_LASERON_SHIFT, m_LgLaserOnShift);
	DDX_Text(pDX, IDC_EDIT_SKY_PRE, m_u32Nprev);
	DDX_Text(pDX, IDC_EDIT_SKY_POST, m_u32Npost);
	DDX_Text(pDX, IDC_EDIT_SKY_MODE, m_u32Mode);
	DDX_Text(pDX, IDC_EDIT_SKY_ANGLE, m_dCosAngle);
	DDX_Control(pDX, IDC_CHECK_SKY_LIST_FLAG, m_ckListFlag);
}

BEGIN_MESSAGE_MAP(CSky_WritingDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_SKYW_LINE, &CSky_WritingDlg::OnBnClickedButtonSkywLine)
	ON_BN_CLICKED(IDC_BUTTON_SKYR_ARC, &CSky_WritingDlg::OnBnClickedButtonSkyrArc)
	ON_BN_CLICKED(IDC_BUTTON_SET_SKY, &CSky_WritingDlg::OnBnClickedButtonSetSky)
	ON_BN_CLICKED(IDC_CHECK_SKY_LIST_FLAG, &CSky_WritingDlg::OnBnClickedCheckSkyListFlag)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CSky_WritingDlg::OnBnClickedButtonStop)
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
	Scan_System_Initialization();
	

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

	write_8bit_port(0x00);
	free_rtc5_dll();
}

void CSky_WritingDlg::Scan_System_Initialization()
{
	m_XYRatio = 524288.0/60.0;
	m_bListFlag = TRUE;
	m_ckListFlag.SetCheck(m_bListFlag);
	
	UINT errcode;
	errcode = init_rtc5_dll();

	(void) select_rtc(1);
	set_rtc5_mode();
	stop_execution();
	load_program_file(NULL);

	// Setting the CO2 laser mode
	set_laser_mode(0);

	write_8bit_port(0x12);
}

void CSky_WritingDlg::SetParams()
{
	set_standby(m_u32Standby_HfPeriod * 64, m_u32Standby_PlsLen * 64);
	set_scanner_delays(m_u32Jump_delay, m_u32Mark_delay, m_u32Polygon_delay);
	set_jump_speed(m_dJumpSpeed * m_XYRatio / 1000.0);
	set_mark_speed(m_dMarkSpeed * m_XYRatio / 1000.0);
	set_laser_pulses(m_u32HalfPeriod * 64, m_u32PulseLength * 64);
	set_laser_delays(m_LgLaserOnDelay * 2, m_u32LaserOffDelay * 2);
}

void CSky_WritingDlg::OnBnClickedButtonSkywLine()
{
	UpdateData(TRUE);
	set_start_list(1);
	SetParams();
	if (m_bListFlag)
	{
		SetSkyList();
	}
	jump_abs(m_XYRatio*(-10), m_XYRatio*(-10));
	mark_abs(m_XYRatio*(-30), m_XYRatio*(-10));
	mark_abs(m_XYRatio*(-30), m_XYRatio*(10));
	mark_abs(m_XYRatio*(-10), m_XYRatio*(10));
	mark_abs(m_XYRatio*(-10), m_XYRatio*(-10));
	jump_abs(0, 0);
	mark_abs(m_XYRatio*(5), m_XYRatio*(5*sqrt(3.0)));
	mark_abs(m_XYRatio*(15), m_XYRatio*(5*sqrt(3.0)));
	mark_abs(m_XYRatio*(20), 0);
	mark_abs(m_XYRatio*(15), m_XYRatio*(-5*sqrt(3.0)));
	mark_abs(m_XYRatio*(5), m_XYRatio*(-5*sqrt(3.0)));
	mark_abs(0, 0);
	set_end_of_list();
	execute_list(1);
}

void CSky_WritingDlg::OnBnClickedButtonSkyrArc()
{
	UpdateData(TRUE);
	set_start_list(1);
	SetParams();
	if (m_bListFlag)
	{
		SetSkyList();
	}
	jump_abs(m_XYRatio*(-20), 0);
	arc_abs(m_XYRatio*(-10), 0, 180.0);
	arc_abs(m_XYRatio*(10), 0, 180.0);
	jump_abs(m_XYRatio*(-20), m_XYRatio*(-10));
	arc_abs(m_XYRatio*(-10), m_XYRatio*(-10), 180.0);
	arc_abs(m_XYRatio*(10), m_XYRatio*(-10), 180.0);
	set_end_of_list();
	execute_list(1);
}

void CSky_WritingDlg::SetSkyListFlag()
{
	if (m_ckListFlag.GetCheck() == BST_CHECKED)
	{
		m_bListFlag = TRUE;
		GetDlgItem(IDC_BUTTON_SET_SKY)->EnableWindow(FALSE);
	}
	else
	{
		m_bListFlag = FALSE;
		GetDlgItem(IDC_BUTTON_SET_SKY)->EnableWindow(TRUE);
	}
}

void CSky_WritingDlg::SetSkyList()
{
	set_sky_writing_para_list(m_dTimelag, m_LgLaserOnShift * 2, m_u32Nprev, m_u32Npost);
	set_sky_writing_mode_list(m_u32Mode);
	if (m_u32Mode > 2)
	{
		set_sky_writing_limit_list(m_dCosAngle);
	}
}

void CSky_WritingDlg::OnBnClickedButtonSetSky()
{
	UpdateData(TRUE);
	set_sky_writing_para(m_dTimelag, m_LgLaserOnShift * 2, m_u32Nprev, m_u32Npost);
	set_sky_writing_mode(m_u32Mode);
	if (m_u32Mode > 2)
	{
		set_sky_writing_limit(m_dCosAngle);
	}
}

void CSky_WritingDlg::OnBnClickedCheckSkyListFlag()
{
	SetSkyListFlag();
}

void CSky_WritingDlg::OnBnClickedButtonStop()
{
	stop_execution();
}
