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
}


BEGIN_MESSAGE_MAP(InventoryDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_PRODUCT_ADD, &InventoryDlg::OnBnClickedBtnProductAdd)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ALL_INVENTORY, &InventoryDlg::OnClickListAllInventory)
END_MESSAGE_MAP()


// InventoryDlg 메시지 처리기

BOOL InventoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_IniInventory.SetFile("D:\\제품리스트.Ini");
	m_IniCompanyStock.SetFile("D:\\업체상품리스트.ini");

	SetInventoryDlg();
	 
	InitAllInventoryList();
	InitSelectInventoryList();

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
	SetPosition_BtnProductAdd();
	SetPosition_StaticProductName();
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
	int nEditProductName_Y = 630;
	int nEditProductName_Width = 180;
	int nEditProductName_Height = 25;

	GetDlgItem(IDC_EDIT_PRODUCT_NAME)->MoveWindow(nEditProductName_X, nEditProductName_Y, nEditProductName_Width, nEditProductName_Height);
}

void InventoryDlg::SetPosition_BtnProductAdd()
{
	int nBtnProductAdd_X = 250;
	int nBtnProductAdd_Y = 630;
	int nBtnProductAdd_Width = 70;
	int nBtnProductAdd_Height = 25;

	GetDlgItem(IDC_BTN_PRODUCT_ADD)->MoveWindow(nBtnProductAdd_X, nBtnProductAdd_Y, nBtnProductAdd_Width, nBtnProductAdd_Height);
}

void InventoryDlg::SetPosition_StaticProductName()
{
	int nStaticProductName_X = 20;
	int nStaticProductName_Y = 635;
	int nStaticProductName_Width = 40;
	int nStaticProductName_Height = 25;

	GetDlgItem(IDC_STATIC_PRODUCT_NAME)->MoveWindow(nStaticProductName_X, nStaticProductName_Y, nStaticProductName_Width, nStaticProductName_Height);
}

void InventoryDlg::InitAllInventoryList()
{
	m_ListCtr_AllInventory.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_ListCtr_AllInventory.InsertColumn(0, _T(""), NULL, 0);
	m_ListCtr_AllInventory.InsertColumn(1, _T("제품리스트"), LVCFMT_CENTER, 300);

	LoadAllInventoryList();
}

void InventoryDlg::InitSelectInventoryList()
{
	m_ListCtr_SelectInventory.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_ListCtr_SelectInventory.InsertColumn(0, _T(""), NULL, 0);
	m_ListCtr_SelectInventory.InsertColumn(1, _T("유통채널"), LVCFMT_CENTER, 300);
	m_ListCtr_SelectInventory.InsertColumn(2, _T("수량"), LVCFMT_CENTER, 100);
}

void InventoryDlg::AddProduct(CString strProductName)
{
	m_IniInventory.SetSection(_T("제품리스트"));
	m_IniInventory.WriteInt(strProductName, 0);

	LoadAllInventoryList();
}

void InventoryDlg::OnBnClickedBtnProductAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strProductName, strMessage;

	m_Edit_ProductName.GetWindowText(strProductName);

	if (strProductName == "")
	{
		AfxMessageBox(_T("품명을 입력하세요"));
		return;
	}

	strMessage.Format(_T("[ %s ] 제품을 추가 하시겠습니까?"), strProductName);

	if (IDYES == AfxMessageBox(strMessage, MB_YESNO))
	{
		AddProduct(strProductName);
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

	m_IniInventory.GetAllKeyValue(_T("제품리스트"), &strAllInventoryList, &strAllInventoryValue);

	int nCount = strAllInventoryList.GetCount();

	for (int i = 0; i < nCount; i++)
	{
		pos = strAllInventoryList.FindIndex(i);
		str = strAllInventoryList.GetAt(pos);

		m_ListCtr_AllInventory.InsertItem(i, _T(""));
		m_ListCtr_AllInventory.SetItem(i, 1, LVIF_TEXT, str, 0, 0, 0, NULL);
	}
}


void InventoryDlg::OnClickListAllInventory(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int index = pNMItemActivate->iItem; // 클릭한 아이템의 인덱스 얻어옴

	if (index >= 0 && index < m_ListCtr_AllInventory.GetItemCount()) // 표시된 아이템들중에 클릭시 아래 코드 실행
	{
		LoadSelectInventoryList(index);
	}

	*pResult = 0;
}

void InventoryDlg::LoadSelectInventoryList(int nIndex)
{
	
	CStringList strProductList;
	CString		strSelectProduct, strTemp;
	int			nStocknPrice[2];
	int			nDefValue[2] = { 0,0 };
	CFileFind	Find;

	m_ListCtr_SelectInventory.DeleteAllItems();

	BOOL		bRet = Find.FindFile(_T("D:\\업체상품리스트.ini"));

	if (!bRet) return;

	strSelectProduct = m_ListCtr_AllInventory.GetItemText(nIndex, 1);

	//모든 섹션 찾기
	_TCHAR	buff[4096] = { 0x20, };
	_TCHAR	sect[1024] = { 0x00, };

	DWORD n = ::GetPrivateProfileSectionNames(buff, 4096, m_IniCompanyStock.Filename);

	int pos = 0;
	BOOL bMakedSect = FALSE; // 하나의 섹션을 구성완료하면 TRUE하여 pos를 0으로 초기화
	for (int i = 0; i < n; i++, pos++)
	{
		if (buff[i] != '\0')
		{
			if (bMakedSect) pos = 0;
			memcpy(sect + pos, buff + i, 2);
			bMakedSect = FALSE;
			continue;
		}
		else
		{
			sect[i] = '\0';
			strProductList.AddTail(sect);
			memset(sect, 0x00, sizeof(sect));
			bMakedSect = TRUE;
		}
	}

	int nCount = strProductList.GetSize();

	for (int i = 0; i < nCount; i++)
	{
		POSITION pos = strProductList.FindIndex(i);
		strTemp		 = strProductList.GetAt(pos);

		m_ListCtr_SelectInventory.InsertItem(i, _T(""));
		m_ListCtr_SelectInventory.SetItem(i, 1, LVIF_TEXT, strTemp, 0, 0, 0, NULL);

		m_IniCompanyStock.SetSection(strTemp);
		m_IniCompanyStock.GetIntArray(strSelectProduct, nStocknPrice, 2, nDefValue);

		int nCount = nStocknPrice[0];

		strTemp.Format(_T("%d"), nCount);

		m_ListCtr_SelectInventory.SetItem(i, 2, LVIF_TEXT, strTemp, 0, 0, 0, NULL);
	}
}
