#pragma once


// CDlgImg dialog

class CDlgImg : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImg)

public:
	CDlgImg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgImg();

	CImage m_pImg;
	CString m_strFilePath;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGIMG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
