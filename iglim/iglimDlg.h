
// iglimDlg.h : header file
//

#pragma once


// CiglimDlg dialog
class CiglimDlg : public CDialogEx
{
// Construction
public:
	CiglimDlg(CWnd* pParent = NULL);	// standard constructor

	CImage m_pImg;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IGLIM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	void InitImg();
	void drawCircle(unsigned char* fm, int x, int y, int nRadius, int color);
	bool isCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
public:
	afx_msg void OnBnClickedBtnCreate();
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedBtnTopleft();
};
