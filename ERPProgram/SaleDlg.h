#pragma once
#include "Ini.h"


// SaleDlg 대화 상자

class SaleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SaleDlg)

public:
	SaleDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SaleDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SALE_DIALOG };
	
public:
	CIni				m_IniInventory;
	CIni				m_IniCompanyInfo;
	CIni				m_IniCompanyStock;

	//Sale 다이얼로그 버튼 및 크기 설정
	void				SetSaleDlg();
	void				SetTitle();
	void				SetPosition_StaticChannel();
	void				SetPosition_StaticName();
	void				SetPosition_StaticPhone();
	void				SetPosition_StaticPostCode();
	void				SetPosition_StaticAddress();
	void				SetPosition_StaticNum();
	void				SetPosition_StaticProdName();
	void				SetPosition_ComboCompany();
	void				SetPosition_EditName();
	void				SetPosition_EditPhone();
	void				SetPosition_EditPostCode();
	void				SetPosition_EditAddress();
	void				SetPosition_EditNum();
	void				SetPosition_ComboProdName();
	void				SetPosition_BtnOrder();

	//
	void				LoadCompanyList();
	void				LoadCompanyStock();

	//
	void				WriteCSV(CString strChannel, CString strName, CString strPhone, CString strPostCode
								,CString strAddress, CString strNum, CString strProdName, CString strSum);

protected:
	virtual void		DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL		OnInitDialog();
	CComboBox			m_Combo_Company;
	CEdit				m_Edit_Name;
	CEdit				m_Edit_Phone;
	CEdit				m_Edit_PostCode;
	CEdit				m_Edit_Address;
	CEdit				m_Edit_Num;
	CComboBox m_Combo_ProdName;
	afx_msg void OnBnClickedBtnOrder();
};
