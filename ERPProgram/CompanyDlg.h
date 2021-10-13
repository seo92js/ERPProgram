#pragma once
#include "Ini.h"


// CompanyDlg 대화 상자

class CompanyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CompanyDlg)

public:
	CompanyDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CompanyDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_COMPANY_DIALOG };

public:
	CIni			m_IniInventory;
	CIni			m_IniCompanyInfo;
	CIni			m_IniCompanyStock;

	int				m_nSavedItem, m_nSavedSubitem;

	//Company 다이얼로그 버튼 및 크기 설정
	void			SetCompanyDlg();
	void			SetTitle();
	void			SetPosition_Company();
	void			SetPosition_CompanyInfo();
	void			SetPosition_CompanyStock();
	void			SetPosition_StaticCompany();
	void			SetPosition_StaticManager();
	void			SetPosition_StaticPhone();
	void			SetPosition_EditCompany();
	void			SetPosition_EditManager();
	void			SetPosition_EditPhone();
	void			SetPosition_BtnCompanyAdd();
	void			SetPosition_BtnSave();

	//Company List 관련
	void			InitCompanyList();
	void			InitCompanyInfo();
	void			InitCompanyStock();
	void			LoadCompanyList();
	void			LoadCompanyInfo(int nIndex);
	void			LoadCompanyStock(int nIndex);

	//업체 추가기능
	void			AddCompany(CString strCompany, CString strManager, CString strPhone);

protected:
	virtual void	DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL	OnInitDialog();
	CListCtrl		m_ListCtr_Company;
	CEdit			m_Edit_Company;
	CEdit			m_Edit_Manager;
	CEdit			m_Edit_Phone;
	afx_msg void	OnBnClickedBtnCompanyAdd();
	afx_msg void	OnClickListCompany(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl		m_ListCtr_CompanyInfo;
	CListCtrl		m_ListCtr_CompanyStock;
	afx_msg void	OnDblclkListCompanyStock(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnSave();
};
