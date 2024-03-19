// DlgImg.cpp : implementation file
//

#include "stdafx.h"
#include "iglim.h"
#include "DlgImg.h"
#include "afxdialogex.h"
#include <iostream>

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#define WIDTH 1200
#define HEIGHT 800

// CDlgImg dialog

IMPLEMENT_DYNAMIC(CDlgImg, CDialogEx)

CDlgImg::CDlgImg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLGIMG, pParent)
{
}

CDlgImg::~CDlgImg()
{
}

void CDlgImg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgImg message handlers


BOOL CDlgImg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	MoveWindow(0, 0, 1220, 840);

	return TRUE;
}

void CDlgImg::OnPaint()
{
	CPaintDC dc(this);
	m_pImg.Load(m_strFilePath);
	m_pImg.Draw(dc, 0, 0);

	unsigned char* fm = (unsigned char*)m_pImg.GetBits();
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

	std::cout << "Center of Circle (" << nCenterX << "," << nCenterY << ")" << std::endl;
}
