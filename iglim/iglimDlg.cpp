
// iglimDlg.cpp : implementation file
//

#include "stdafx.h"
#include "iglim.h"
#include "iglimDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CiglimDlg dialog



CiglimDlg::CiglimDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IGLIM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CiglimDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CiglimDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CREATE, &CiglimDlg::OnBnClickedBtnCreate)
	ON_BN_CLICKED(IDC_BTN_RESET, &CiglimDlg::OnBnClickedBtnReset)
	ON_BN_CLICKED(IDC_BTN_TOPLEFT, &CiglimDlg::OnBnClickedBtnTopleft)
END_MESSAGE_MAP()


// CiglimDlg message handlers

BOOL CiglimDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	MoveWindow(0, 0, 1600, 840);
	GetDlgItem(IDC_BTN_RESET)->EnableWindow(false);

	InitImg();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CiglimDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CiglimDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	if (m_pImg) {
		m_pImg.Draw(dc, 0, 0);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CiglimDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#define WIDTH 1200
#define HEIGHT 800
#define BPP 8

void CiglimDlg::InitImg()
{
	int nWidth = WIDTH;
	int nHeight = HEIGHT;
	int nBpp = BPP;

	m_pImg.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_pImg.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_pImg.GetPitch();
	unsigned char* fm = (unsigned char*)m_pImg.GetBits();

	memset(fm, 0xff, nWidth * nHeight);
}

void CiglimDlg::OnBnClickedBtnCreate()
{
	// TODO: Add your control notification handler code here
		int nXpos = GetDlgItemInt(IDC_EDIT_XPOS);
		int nYpos = GetDlgItemInt(IDC_EDIT_YPOS);
		int nRadius = GetDlgItemInt(IDC_EDIT_RADIUS);
		if (nXpos + nRadius * 2 > WIDTH || nYpos + nRadius * 2 > HEIGHT) {
			AfxMessageBox(_T("Out Of Range"), MB_ICONERROR);
			return;
		}
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(true);
		GetDlgItem(IDC_BTN_CREATE)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_XPOS)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_YPOS)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_RADIUS)->EnableWindow(false);

		int nPitch = m_pImg.GetPitch();
		unsigned char* fm = (unsigned char*)m_pImg.GetBits();

		drawCircle(fm, nXpos, nYpos, nRadius, 0x00);

		Invalidate();
}

void CiglimDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int color)
{
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_pImg.GetPitch();

	for (int j = y; j < y + nRadius * 2; j++) {
		for (int i = x; i < x + nRadius * 2; i++) {
			if (isCircle(i, j, nCenterX, nCenterY, nRadius))
				fm[j * nPitch + i] = color;
		}
	}
}

bool CiglimDlg::isCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius/* && dDist > (radious - 1) * (radious - 1)*/) {
		bRet = true;
	}

	return bRet;
}


void CiglimDlg::OnBnClickedBtnReset()
{
	// TODO: Add your control notification handler code here
	m_pImg.Destroy();
	InitImg();

	GetDlgItem(IDC_BTN_RESET)->EnableWindow(false);
	GetDlgItem(IDC_BTN_CREATE)->EnableWindow(true);
	GetDlgItem(IDC_EDIT_XPOS)->EnableWindow(true);
	GetDlgItem(IDC_EDIT_YPOS)->EnableWindow(true);
	GetDlgItem(IDC_EDIT_RADIUS)->EnableWindow(true);

	Invalidate();
}

void CiglimDlg::OnBnClickedBtnTopleft()
{
	// TODO: Add your control notification handler code here
	int nXpos = GetDlgItemInt(IDC_EDIT_XPOS);
	int nYpos = GetDlgItemInt(IDC_EDIT_YPOS);
	int nRadius = GetDlgItemInt(IDC_EDIT_RADIUS);

	unsigned char* fm = (unsigned char*)m_pImg.GetBits();
	for (int i = 0; i < 20; i++) {
		drawCircle(fm, nXpos--, nYpos--, nRadius, 0xff);
		drawCircle(fm, nXpos, nYpos, nRadius, 0x00);
		CClientDC dc(this);
		m_pImg.Draw(dc, 0, 0);
		Sleep(10);
	}
}
