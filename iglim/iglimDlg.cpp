
// iglimDlg.cpp : implementation file
//

#include "stdafx.h"
#include "iglim.h"
#include "iglimDlg.h"
#include "afxdialogex.h"
#include "DlgImg.h"
#include <iostream>
#include <vector>

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
	DDX_Control(pDX, IDC_LIST, m_List);
}

BEGIN_MESSAGE_MAP(CiglimDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CREATE, &CiglimDlg::OnBnClickedBtnCreate)
	ON_BN_CLICKED(IDC_BTN_REMOVE, &CiglimDlg::OnBnClickedBtnRemove)
	ON_BN_CLICKED(IDC_BTN_TOPLEFT, &CiglimDlg::OnBnClickedBtnTopleft)
	ON_BN_CLICKED(IDC_BTN_TOP, &CiglimDlg::OnBnClickedBtnTop)
	ON_BN_CLICKED(IDC_BTN_TOPRIGHT, &CiglimDlg::OnBnClickedBtnTopright)
	ON_BN_CLICKED(IDC_BTN_LEFT, &CiglimDlg::OnBnClickedBtnLeft)
	ON_BN_CLICKED(IDC_BTN_RIGHT, &CiglimDlg::OnBnClickedBtnRight)
	ON_BN_CLICKED(IDC_BTN_BOTTOMLEFT, &CiglimDlg::OnBnClickedBtnBottomleft)
	ON_BN_CLICKED(IDC_BTN_BOTTOM, &CiglimDlg::OnBnClickedBtnBottom)
	ON_BN_CLICKED(IDC_BTN_BOTTOMRIGHT, &CiglimDlg::OnBnClickedBtnBottomright)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CiglimDlg::OnNMDblclkList)
	ON_BN_CLICKED(IDC_BTN_QUIT, &CiglimDlg::OnBnClickedBtnQuit)
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
	GetDlgItem(IDC_EDIT_XPOS)->SetWindowTextW(_T("0"));
	GetDlgItem(IDC_EDIT_YPOS)->SetWindowTextW(_T("0"));
	GetDlgItem(IDC_EDIT_RADIUS)->SetWindowTextW(_T("0"));
	GetDlgItem(IDC_BTN_RESET)->EnableWindow(false);
	GetDlgItem(IDC_BTN_TOPLEFT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_TOP)->EnableWindow(false);
	GetDlgItem(IDC_BTN_TOPRIGHT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_LEFT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_RIGHT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_BOTTOMLEFT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_BOTTOM)->EnableWindow(false);
	GetDlgItem(IDC_BTN_BOTTOMRIGHT)->EnableWindow(false);
	GetDlgItem(IDC_EDIT_DISTANCE)->EnableWindow(false);

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

	m_pImg.Create(nWidth, nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_pImg.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_pImg.GetPitch();
	unsigned char* fm = (unsigned char*)m_pImg.GetBits();

	for (int j = 0; j < HEIGHT; j++) {
		for (int i = 0; i < WIDTH; i++) {
			fm[j * nPitch + i] = 0xff;
		}
	}
}

void CiglimDlg::UpdateImg()
{
	CClientDC dc(this);
	m_pImg.Draw(dc, 0, 0);
	Sleep(0);
}

void CiglimDlg::OnBnClickedBtnCreate()
{
		int nXpos = GetDlgItemInt(IDC_EDIT_XPOS);
		int nYpos = GetDlgItemInt(IDC_EDIT_YPOS);
		int nRadius = GetDlgItemInt(IDC_EDIT_RADIUS);
		if (nRadius == NULL) {
			AfxMessageBox(_T("Fill In Radius"));
			return;
		}
		if (nXpos + nRadius * 2 > WIDTH || nYpos + nRadius * 2 > HEIGHT) {
			AfxMessageBox(_T("Out Of Range"));
			return;
		}

		GetDlgItem(IDC_BTN_RESET)->EnableWindow(true);
		GetDlgItem(IDC_BTN_TOPLEFT)->EnableWindow(true);
		GetDlgItem(IDC_BTN_TOP)->EnableWindow(true);
		GetDlgItem(IDC_BTN_TOPRIGHT)->EnableWindow(true);
		GetDlgItem(IDC_BTN_LEFT)->EnableWindow(true);
		GetDlgItem(IDC_BTN_RIGHT)->EnableWindow(true);
		GetDlgItem(IDC_BTN_BOTTOMLEFT)->EnableWindow(true);
		GetDlgItem(IDC_BTN_BOTTOM)->EnableWindow(true);
		GetDlgItem(IDC_BTN_BOTTOMRIGHT)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_DISTANCE)->EnableWindow(true);

		GetDlgItem(IDC_BTN_CREATE)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_XPOS)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_YPOS)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_RADIUS)->EnableWindow(false);

		int nPitch = m_pImg.GetPitch();
		unsigned char* fm = (unsigned char*)m_pImg.GetBits();

		DrawCircle(fm, nXpos, nYpos, nRadius, 0x00);

		Invalidate();
}

void CiglimDlg::DrawCircle(unsigned char* fm, int x, int y, int nRadius, int color)
{
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_pImg.GetPitch();

	for (int j = y; j < y + nRadius * 2; j++) {
		for (int i = x; i < x + nRadius * 2; i++) {
			if (IsCircle(i, j, nCenterX, nCenterY, nRadius))
				fm[j * nPitch + i] = color;
		}
	}
}

bool CiglimDlg::IsCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius)
		bRet = true;

	return bRet;
}


void CiglimDlg::OnBnClickedBtnRemove()
{
	m_pImg.Destroy();
	InitImg();

	GetDlgItem(IDC_BTN_RESET)->EnableWindow(false);
	GetDlgItem(IDC_BTN_RESET)->EnableWindow(false);
	GetDlgItem(IDC_BTN_TOPLEFT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_TOP)->EnableWindow(false);
	GetDlgItem(IDC_BTN_TOPRIGHT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_LEFT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_RIGHT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_BOTTOMLEFT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_BOTTOM)->EnableWindow(false);
	GetDlgItem(IDC_BTN_BOTTOMRIGHT)->EnableWindow(false);
	GetDlgItem(IDC_EDIT_DISTANCE)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_DISTANCE)->EnableWindow(false);

	GetDlgItem(IDC_BTN_CREATE)->EnableWindow(true);
	GetDlgItem(IDC_EDIT_XPOS)->EnableWindow(true);
	GetDlgItem(IDC_EDIT_YPOS)->EnableWindow(true);
	GetDlgItem(IDC_EDIT_RADIUS)->EnableWindow(true);

	Invalidate();
}

bool CiglimDlg::BeforeMove()
{
	bool bRet = true;
	int nDistance = GetDlgItemInt(IDC_EDIT_DISTANCE);
	if (nDistance == NULL) {
		AfxMessageBox(_T("Fill In Distance"));
		bRet = false;
	}
	return bRet;
}

std::vector<int> CiglimDlg::GetCenter(unsigned char* fm)
{
	std::vector<int> vPoint{};

	int nPitch = m_pImg.GetPitch();
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;

	CRect rect(0, 0, WIDTH, HEIGHT);
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			if (fm[j * nPitch + i] == 0x00) {
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}
	
	int nCenterX = nSumX / nCount;
	int nCenterY = nSumY / nCount;

	vPoint.push_back(nCenterX);
	vPoint.push_back(nCenterY);

	return vPoint;
}

void CiglimDlg::SaveImg()
{
	CString strFileName;
	strFileName.Format(_T("%02d.bmp"), m_nNum);

	CString strFilePath;
	strFilePath.Format(_T("C:\\image\\%s"), strFileName);

	m_pImg.Save(strFilePath);
	m_List.InsertItem(0, strFileName, 0);
	m_nNum++;
}

void CiglimDlg::MoveCircle(int direction)
{
	if (!BeforeMove())
		return;

	unsigned char* fm = (unsigned char*)m_pImg.GetBits();
	int nRadius = GetDlgItemInt(IDC_EDIT_RADIUS);
	int nDistance = GetDlgItemInt(IDC_EDIT_DISTANCE);

	std::vector<int> vCenter = GetCenter(fm);

	int nStartX = vCenter[0] - nRadius;
	int nStartY = vCenter[1] - nRadius;

	for (int i = 0; i < nDistance; i++) {
		if (direction == 1)
		{
			if (nStartX == 0 || nStartY == 0) {
				AfxMessageBox(_T("Can't Escape From Area"));
				break;
			}
			DrawCircle(fm, nStartX--, nStartY--, nRadius, 0xff);
			DrawCircle(fm, nStartX, nStartY, nRadius, 0x00);
			UpdateImg();
		}
		else if (direction == 2)
		{
			if (nStartY == 0) {
				AfxMessageBox(_T("Can't Escape From Area"));
				break;
			}
			DrawCircle(fm, nStartX, nStartY--, nRadius, 0xff);
			DrawCircle(fm, nStartX, nStartY, nRadius, 0x00);
			UpdateImg();
		}
		else if (direction == 3)
		{
			if (nStartX + (nRadius * 2) == WIDTH || nStartY == 0) {
				AfxMessageBox(_T("Can't Escape From Area"));
				break;
			}
			DrawCircle(fm, nStartX++, nStartY--, nRadius, 0xff);
			DrawCircle(fm, nStartX, nStartY, nRadius, 0x00);
			UpdateImg();
		}
		else if (direction == 4)
		{
			if (nStartX == 0) {
				AfxMessageBox(_T("Can't Escape From Area"));
				break;
			}
			DrawCircle(fm, nStartX--, nStartY, nRadius, 0xff);
			DrawCircle(fm, nStartX, nStartY, nRadius, 0x00);
			UpdateImg();
		}
		else if (direction == 5)
		{
			if (nStartX + (nRadius * 2) == WIDTH) {
				AfxMessageBox(_T("Can't Escape From Area"));
				break;
			}
			DrawCircle(fm, nStartX++, nStartY, nRadius, 0xff);
			DrawCircle(fm, nStartX, nStartY, nRadius, 0x00);
			UpdateImg();
		}
		else if (direction == 6)
		{
			if (nStartX == 0 || nStartY + (nRadius * 2) == HEIGHT) {
				AfxMessageBox(_T("Can't Escape From Area"));
				break;
			}
			DrawCircle(fm, nStartX--, nStartY++, nRadius, 0xff);
			DrawCircle(fm, nStartX, nStartY, nRadius, 0x00);
			UpdateImg();
		}
		else if (direction == 7)
		{
			if (nStartY + (nRadius * 2) == HEIGHT) {
				AfxMessageBox(_T("Can't Escape From Area"));
				break;
			}
			DrawCircle(fm, nStartX, nStartY++, nRadius, 0xff);
			DrawCircle(fm, nStartX, nStartY, nRadius, 0x00);
			UpdateImg();
		}
		else if (direction == 8)
		{
			if (nStartX + (nRadius * 2) == WIDTH || nStartY + (nRadius * 2) == HEIGHT) {
				AfxMessageBox(_T("Can't Escape From Area"));
				break;
			}
			DrawCircle(fm, nStartX++, nStartY++, nRadius, 0xff);
			DrawCircle(fm, nStartX, nStartY, nRadius, 0x00);
			UpdateImg();
		}
	}

	SaveImg();
}

void CiglimDlg::OnBnClickedBtnTopleft()
{
	MoveCircle(1);
}

void CiglimDlg::OnBnClickedBtnTop()
{
	MoveCircle(2);
}

void CiglimDlg::OnBnClickedBtnTopright()
{
	MoveCircle(3);
}

void CiglimDlg::OnBnClickedBtnLeft()
{
	MoveCircle(4);
}

void CiglimDlg::OnBnClickedBtnRight()
{
	MoveCircle(5);
}

void CiglimDlg::OnBnClickedBtnBottomleft()
{
	MoveCircle(6);
}

void CiglimDlg::OnBnClickedBtnBottom()
{
	MoveCircle(7);
}

void CiglimDlg::OnBnClickedBtnBottomright()
{
	MoveCircle(8);
}

void CiglimDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (pNMItemActivate->iItem != -1) {
		CString strFileName = m_List.GetItemText(pNMItemActivate->iItem, 0);
		CString strFilePath;
		strFilePath.Format(_T("C:\\image\\%s"), strFileName);

		CDlgImg dig;
		dig.m_strFilePath = strFilePath;
		dig.DoModal();
	}

	*pResult = 0;
}


void CiglimDlg::OnBnClickedBtnQuit()
{
	// TODO: Add your control notification handler code here
	if (AfxMessageBox(_T("Are you sure to quit?"), MB_OKCANCEL) == IDOK)
		EndDialog(IDOK);
}
