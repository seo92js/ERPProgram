#pragma once
#include "Ini.h"


// InventoryDlg 대화 상자

class InventoryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(InventoryDlg)

public:
	InventoryDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~InventoryDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_INVENTORY_DLALOG };

public:
	CIni			m_IniInventory;
	CIni			m_IniCompanyStock;

	void			Init();

	//InventoryDlg 다이얼로그 버튼 및 크기 설정
	void			SetInventoryDlg();
	void			SetTitle();
	void			SetPosition_AllInventory();
	void			SetPosition_SelectInventory();
	void			SetPosition_EditProductName();
	void			SetPosition_BtnProductAdd();
	void			SetPosition_StaticProductName();

	//Inventory List 관련
	void			InitAllInventoryList();
	void			InitSelectInventoryList();
	void			LoadAllInventoryList();
	void			LoadSelectInventoryList(int nIndex);

	//제품 추가기능
	void			AddProduct(CString strProductName);


protected:
	virtual void	DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL	OnInitDialog();
	CListCtrl		m_ListCtr_AllInventory;
	CListCtrl		m_ListCtr_SelectInventory;
	CEdit			m_Edit_ProductName;
	
	afx_msg void	OnBnClickedBtnProductAdd();
	afx_msg void	OnClickListAllInventory(NMHDR* pNMHDR, LRESULT* pResult);
};
