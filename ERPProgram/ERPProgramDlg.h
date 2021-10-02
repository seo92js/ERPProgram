
// ERPProgramDlg.h: 헤더 파일
#pragma once
#include "InventoryDlg.h"
#include "CompanyDlg.h"
#include "CalculateDlg.h"
#include "SaleDlg.h"

// CERPProgramDlg 대화 상자
class CERPProgramDlg : public CDialogEx
{
// 생성입니다.
public:
	CERPProgramDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ERPPROGRAM_DIALOG };
#endif

public:
	//자식 다이얼로그 객체
	InventoryDlg*	m_pInventoryDlg;
	CompanyDlg*		m_pCompanyDlg;
	CalculateDlg*	m_pCalculateDlg;
	SaleDlg*		m_pSaleDlg;

	//메인 다이얼로그 버튼 및 크기 설정
	void			SetMainDialog();
	void			SetMainButtonPosition();

	//자식 다이얼로그 Create & Show
	void			CreateInventoryDlg();
	void			CreateCompanyDlg();
	void			CreateCalculateDlg();
	void			CreateSaleDlg();
	void			ShowInventoryDlg(int nShowOrHide);
	void			ShowCompanyDlg(int nShowOrHide);
	void			ShowCaculateDlg(int nShowOrHide);
	void			ShowSaleDlg(int nShowOrHide);

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	
// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnInventory();
	afx_msg void OnBnClickedBtnCompany();
	afx_msg void OnBnClickedBtnCalculate();
	afx_msg void OnBnClickedBtnSale();
};
