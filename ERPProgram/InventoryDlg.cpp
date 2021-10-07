// InventoryDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "ERPProgram.h"
#include "ERPProgramDlg.h"
#include "InventoryDlg.h"
#include "afxdialogex.h"


// InventoryDlg 대화 상자

IMPLEMENT_DYNAMIC(InventoryDlg, CDialogEx)

InventoryDlg::InventoryDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INVENTORY_DLALOG, pParent)
{

}

InventoryDlg::~InventoryDlg()
{
}

void InventoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ALL_INVENTORY, m_ListCtr_AllInventory);
	DDX_Control(pDX, IDC_LIST_SELECT_INVENTORY, m_ListCtr_SelectInventory);
	DDX_Control(pDX, IDC_EDIT_PRODUCT_NAME, m_Edit_ProductName);
	DDX_Control(pDX, IDC_EDIT_PRODUCT_COUNT, m_Edit_ProductCount);
}


BEGIN_MESSAGE_MAP(InventoryDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_PRODUCT_ADD, &InventoryDlg::OnBnClickedBtnProductAdd)
END_MESSAGE_MAP()


// InventoryDlg 메시지 처리기

BOOL InventoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_IniInventory.SetFile("D:\\Test.Ini");

	SetInventoryDlg();

	InitAllInventoryList();
	InitSelectInventoryList();

	LoadAllInventoryList();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void InventoryDlg::SetInventoryDlg()
{
	int nInventoryDlg_X = 120;
	int nInventoryDlg_Y = 10;
	int nInventoryDlg_Width = 1350;
	int nInventoryDlg_Height = 840;

	MoveWindow(nInventoryDlg_X, nInventoryDlg_Y, nInventoryDlg_Width, nInventoryDlg_Height);

	SetTitle();
	SetPosition_AllInventory();
	SetPosition_SelectInventory();
	SetPosition_EditProductName();
	SetPosition_EditProductCount();
	SetPosition_BtnProductAdd();
	SetPosition_StaticProductName();
	SetPosition_StaticProductCount();
}

void InventoryDlg::SetTitle()
{
	int nTitle_Width = 1350;
	int nTitle_Height = 45;

	GetDlgItem(IDC_BTN_INVENTORY_TITLE)->MoveWindow(0, 0, nTitle_Width, nTitle_Height);
}

void InventoryDlg::SetPosition_AllInventory()
{
	int nAllInventory_X = 20;
	int nAllInventory_Y = 110;
	int nAllInventory_Width = 300;
	int nAllInventory_Height = 500;

	m_ListCtr_AllInventory.MoveWindow(nAllInventory_X, nAllInventory_Y, nAllInventory_Width, nAllInventory_Height);
}

void InventoryDlg::SetPosition_SelectInventory()
{
	int nSelectInventory_X = 330;
	int nSelectInventory_Y = 110;
	int nSelectInventory_Width = 400;
	int nSelectInventory_Height = 500;

	m_ListCtr_SelectInventory.MoveWindow(nSelectInventory_X, nSelectInventory_Y, nSelectInventory_Width, nSelectInventory_Height);
}

void InventoryDlg::SetPosition_EditProductName()
{
	int nEditProductName_X = 60;
	int nEditProductName_Y = 620;
	int nEditProductName_Width = 180;
	int nEditProductName_Height = 25;

	GetDlgItem(IDC_EDIT_PRODUCT_NAME)->MoveWindow(nEditProductName_X, nEditProductName_Y, nEditProductName_Width, nEditProductName_Height);
}

void InventoryDlg::SetPosition_EditProductCount()
{
	int nEditProductCount_X = 60;
	int nEditProductCount_Y = 660;
	int nEditProductCount_Width = 180;
	int nEditProductCount_Height = 25;

	GetDlgItem(IDC_EDIT_PRODUCT_COUNT)->MoveWindow(nEditProductCount_X, nEditProductCount_Y, nEditProductCount_Width, nEditProductCount_Height);
}

void InventoryDlg::SetPosition_BtnProductAdd()
{
	int nBtnProductAdd_X = 250;
	int nBtnProductAdd_Y = 620;
	int nBtnProductAdd_Width = 70;
	int nBtnProductAdd_Height = 65;

	GetDlgItem(IDC_BTN_PRODUCT_ADD)->MoveWindow(nBtnProductAdd_X, nBtnProductAdd_Y, nBtnProductAdd_Width, nBtnProductAdd_Height);
}

void InventoryDlg::SetPosition_StaticProductName()
{
	int nStaticProductName_X = 20;
	int nStaticProductName_Y = 625;
	int nStaticProductName_Width = 40;
	int nStaticProductName_Height = 25;

	GetDlgItem(IDC_STATIC_PRODUCT_NAME)->MoveWindow(nStaticProductName_X, nStaticProductName_Y, nStaticProductName_Width, nStaticProductName_Height);
}

void InventoryDlg::SetPosition_StaticProductCount()
{
	int nStaticProductCount_X = 20;
	int nStaticProductCount_Y = 665;
	int nStaticProductCount_Width = 40;
	int nStaticProductCount_Height = 25;

	GetDlgItem(IDC_STATIC_PRODUCT_COUNT)->MoveWindow(nStaticProductCount_X, nStaticProductCount_Y, nStaticProductCount_Width, nStaticProductCount_Height);
}

void InventoryDlg::InitAllInventoryList()
{
	m_ListCtr_AllInventory.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_ListCtr_AllInventory.InsertColumn(0, _T(""), NULL, 0);
	m_ListCtr_AllInventory.InsertColumn(1, _T("제품리스트"), LVCFMT_CENTER, 300);

	//LoadAllProductList();
}

void InventoryDlg::InitSelectInventoryList()
{
	m_ListCtr_SelectInventory.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_ListCtr_SelectInventory.InsertColumn(0, _T(""), NULL, 0);
	m_ListCtr_SelectInventory.InsertColumn(1, _T("유통채널"), LVCFMT_CENTER, 300);
	m_ListCtr_SelectInventory.InsertColumn(2, _T("수량"), LVCFMT_CENTER, 100);
}

void InventoryDlg::AddProduct(CString strProductName, CString strProductCount)
{
	int nCount = _ttoi(strProductCount);

	m_IniInventory.SetSection(_T("자사몰"));
	m_IniInventory.WriteInt(strProductName, nCount);

	LoadAllInventoryList();
}

void InventoryDlg::OnBnClickedBtnProductAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strProductName, strProductCount, strMessage;

	m_Edit_ProductName.GetWindowText(strProductName);
	m_Edit_ProductCount.GetWindowText(strProductCount);

	if (strProductName == "" || strProductCount == "")
	{
		AfxMessageBox(_T("품명 및 수량을 입력하세요"));
		return;
	}

	strMessage.Format(_T("[ %s, %s개 ] 제품을 추가 하시겠습니까?"), strProductName, strProductCount);

	if (IDYES == AfxMessageBox(strMessage, MB_YESNO))
	{
		AddProduct(strProductName, strProductCount);
	}
	else
		return;
}

void InventoryDlg::LoadAllInventoryList()
{
	m_ListCtr_AllInventory.DeleteAllItems();

	CStringList		strAllInventoryList, strAllInventoryValue;
	CString			str;
	POSITION		pos;

	m_IniInventory.GetAllKeyValue(_T("자사몰"), &strAllInventoryList, &strAllInventoryValue);

	int nCount = strAllInventoryList.GetCount();

	for (int i = 0; i < nCount; i++)
	{
		pos = strAllInventoryList.FindIndex(i);
		str = strAllInventoryList.GetAt(pos);

		m_ListCtr_AllInventory.InsertItem(i, _T(""));
		m_ListCtr_AllInventory.SetItem(i, 1, LVIF_TEXT, str, 0, 0, 0, NULL);
	}
}