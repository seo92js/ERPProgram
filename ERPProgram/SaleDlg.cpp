// SaleDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "ERPProgram.h"
#include "ERPProgramDlg.h"
#include "SaleDlg.h"
#include "afxdialogex.h"


// SaleDlg 대화 상자

IMPLEMENT_DYNAMIC(SaleDlg, CDialogEx)

SaleDlg::SaleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SALE_DIALOG, pParent)
{

}

SaleDlg::~SaleDlg()
{
}

void SaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COMPANY, m_Combo_Company);
	DDX_Control(pDX, IDC_EDIT_NAME, m_Edit_Name);
	DDX_Control(pDX, IDC_EDIT_PHONE_SALE, m_Edit_Phone);
	DDX_Control(pDX, IDC_EDIT_POSTCODE, m_Edit_PostCode);
	DDX_Control(pDX, IDC_EDIT_ADDRESS, m_Edit_Address);
	DDX_Control(pDX, IDC_EDIT_NUM, m_Edit_Num);
	DDX_Control(pDX, IDC_COMBO_PRODNAME, m_Combo_ProdName);
}


BEGIN_MESSAGE_MAP(SaleDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ORDER, &SaleDlg::OnBnClickedBtnOrder)
END_MESSAGE_MAP()


// SaleDlg 메시지 처리기


BOOL SaleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_IniInventory.SetFile("D:\\제품리스트.ini");
	m_IniCompanyInfo.SetFile("D:\\업체정보리스트.ini");
	m_IniCompanyStock.SetFile("D:\\업체상품리스트.ini");

	SetSaleDlg();

	LoadCompanyList();
	LoadCompanyStock();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void SaleDlg::SetSaleDlg()
{
	int nSaleDlg_X = 120;
	int nSaleDlg_Y = 10;
	int nSaleDlg_Width = 1350;
	int nSaleDlg_Height = 840;

	MoveWindow(nSaleDlg_X, nSaleDlg_Y, nSaleDlg_Width, nSaleDlg_Height);

	SetPosition_StaticChannel();
	SetPosition_StaticName();
	SetPosition_StaticPhone();
	SetPosition_StaticPostCode();
	SetPosition_StaticAddress();
	SetPosition_StaticNum();
	SetPosition_StaticProdName();
	SetPosition_ComboCompany();
	SetPosition_EditName();
	SetPosition_EditPhone();
	SetPosition_EditPostCode();
	SetPosition_EditAddress();
	SetPosition_EditNum();
	SetPosition_ComboProdName();
	SetPosition_BtnOrder();

	SetTitle();
}

void SaleDlg::SetTitle()
{
	int nTitle_Width = 1350;
	int nTitle_Height = 45;

	GetDlgItem(IDC_BTN_SALE_TITLE)->MoveWindow(0, 0, nTitle_Width, nTitle_Height);
}

void SaleDlg::SetPosition_StaticChannel()
{
	int nStaticChannel_X = 20;
	int nStaticChannel_Y = 115;
	int nStaticChannel_Width = 40;
	int nStaticChannel_Height = 25;

	GetDlgItem(IDC_STATIC_CHANNEL)->MoveWindow(nStaticChannel_X, nStaticChannel_Y, nStaticChannel_Width, nStaticChannel_Height);
}

void SaleDlg::SetPosition_StaticName()
{
	int nStaticName_X = 180;
	int nStaticName_Y = 115;
	int nStaticName_Width = 40;
	int nStaticName_Height = 25;

	GetDlgItem(IDC_STATIC_NAME)->MoveWindow(nStaticName_X, nStaticName_Y, nStaticName_Width, nStaticName_Height);
}

void SaleDlg::SetPosition_StaticPhone()
{
	int nStaticPhone_X = 310;
	int nStaticPhone_Y = 115;
	int nStaticPhone_Width = 40;
	int nStaticPhone_Height = 25;

	GetDlgItem(IDC_STATIC_PHONE_SALE)->MoveWindow(nStaticPhone_X, nStaticPhone_Y, nStaticPhone_Width, nStaticPhone_Height);
}

void SaleDlg::SetPosition_StaticPostCode()
{
	int nStaticPostCode_X = 470;
	int nStaticPostCode_Y = 115;
	int nStaticPostCode_Width = 50;
	int nStaticPostCode_Height = 25;

	GetDlgItem(IDC_STATIC_POSTCODE)->MoveWindow(nStaticPostCode_X, nStaticPostCode_Y, nStaticPostCode_Width, nStaticPostCode_Height);
}

void SaleDlg::SetPosition_StaticAddress()
{
	int nStaticAddress_X = 600;
	int nStaticAddress_Y = 115;
	int nStaticAddress_Width = 40;
	int nStaticAddress_Height = 25;

	GetDlgItem(IDC_STATIC_ADDRESS)->MoveWindow(nStaticAddress_X, nStaticAddress_Y, nStaticAddress_Width, nStaticAddress_Height);
}

void SaleDlg::SetPosition_StaticNum()
{
	int nStaticNum_X = 840;
	int nStaticNum_Y = 115;
	int nStaticNum_Width = 40;
	int nStaticNum_Height = 25;

	GetDlgItem(IDC_STATIC_NUM)->MoveWindow(nStaticNum_X, nStaticNum_Y, nStaticNum_Width, nStaticNum_Height);
}

void SaleDlg::SetPosition_StaticProdName()
{
	int nStaticProdName_X = 940;
	int nStaticProdName_Y = 115;
	int nStaticProdName_Width = 40;
	int nStaticProdName_Height = 25;

	GetDlgItem(IDC_STATIC_PRODNAME)->MoveWindow(nStaticProdName_X, nStaticProdName_Y, nStaticProdName_Width, nStaticProdName_Height);
}

void SaleDlg::SetPosition_ComboCompany()
{
	int nComboCompany_X = 65;
	int nComboCompany_Y = 110;
	int nComboCompany_Width = 100;
	int nComboCompany_Height = 25;

	m_Combo_Company.MoveWindow(nComboCompany_X, nComboCompany_Y, nComboCompany_Width, nComboCompany_Height);
}

void SaleDlg::SetPosition_EditName()
{
	int nEditName_X = 225;
	int nEditName_Y = 110;
	int nEditName_Width = 70;
	int nEditName_Height = 20;

	m_Edit_Name.MoveWindow(nEditName_X, nEditName_Y, nEditName_Width, nEditName_Height);
}

void SaleDlg::SetPosition_EditPhone()
{
	int nEditPhone_X = 355;
	int nEditPhone_Y = 110;
	int nEditPhone_Width = 100;
	int nEditPhone_Height = 20;

	m_Edit_Phone.MoveWindow(nEditPhone_X, nEditPhone_Y, nEditPhone_Width, nEditPhone_Height);
}

void SaleDlg::SetPosition_EditPostCode()
{
	int nEditPostCode_X = 525;
	int nEditPostCode_Y = 110;
	int nEditPostCode_Width = 70;
	int nEditPostCode_Height = 20;

	m_Edit_PostCode.MoveWindow(nEditPostCode_X, nEditPostCode_Y, nEditPostCode_Width, nEditPostCode_Height);
}

void SaleDlg::SetPosition_EditAddress()
{
	int nEditAddress_X = 645;
	int nEditAddress_Y = 110;
	int nEditAddress_Width = 180;
	int nEditAddress_Height = 20;

	m_Edit_Address.MoveWindow(nEditAddress_X, nEditAddress_Y, nEditAddress_Width, nEditAddress_Height);
}

void SaleDlg::SetPosition_EditNum()
{
	int nEditNum_X = 875;
	int nEditNum_Y = 110;
	int nEditNum_Width = 50;
	int nEditNum_Height = 20;

	m_Edit_Num.MoveWindow(nEditNum_X, nEditNum_Y, nEditNum_Width, nEditNum_Height);
}

void SaleDlg::SetPosition_ComboProdName()
{
	int nComboProdName_X = 985;
	int nComboProdName_Y = 110;
	int nComboProdName_Width = 100;
	int nComboProdName_Height = 20;

	m_Combo_ProdName.MoveWindow(nComboProdName_X, nComboProdName_Y, nComboProdName_Width, nComboProdName_Height);
}

void SaleDlg::SetPosition_BtnOrder()
{
	int nBtnOrder_X = 1100;
	int nBtnOrder_Y = 110;
	int nBtnOrder_Width = 70;
	int nBtnOrder_Height = 20;

	GetDlgItem(IDC_BTN_ORDER)->MoveWindow(nBtnOrder_X, nBtnOrder_Y, nBtnOrder_Width, nBtnOrder_Height);
}

void SaleDlg::LoadCompanyList()
{
	CStringList strCompanyList;
	CString     strTemp;

	m_Combo_Company.ResetContent();

	//모든 섹션 찾기
	_TCHAR	buff[4096] = { 0x20, };
	_TCHAR	sect[1024] = { 0x00, };

	DWORD n = ::GetPrivateProfileSectionNames(buff, 4096, m_IniCompanyInfo.Filename);

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
			strCompanyList.AddTail(sect);
			memset(sect, 0x00, sizeof(sect));
			bMakedSect = TRUE;
		}
	}

	int nCount = strCompanyList.GetSize();

	for (int i = 0; i < nCount; i++)
	{
		POSITION pos = strCompanyList.FindIndex(i);
		strTemp = strCompanyList.GetAt(pos);

		m_Combo_Company.AddString(strTemp);
	}
}

void SaleDlg::LoadCompanyStock()
{
	CStringList strAllInventoryList, strAllInventoryValue;
	CString		str;
	POSITION	pos;

	m_Combo_ProdName.ResetContent();

	m_IniInventory.GetAllKeyValue(_T("제품리스트"), &strAllInventoryList, &strAllInventoryValue);

	int nCount = strAllInventoryList.GetCount();

	for (int i = 0; i < nCount; i++)
	{
		pos = strAllInventoryList.FindIndex(i);
		str = strAllInventoryList.GetAt(pos);

		m_Combo_ProdName.AddString(str);
	}
}

void SaleDlg::WriteCSV(CString strChannel, CString strName, CString strPhone, CString strPostCode
	, CString strAddress, CString strNum, CString strProdName, CString strSum)
{
	CFile file;
	CString str;
	CFileFind fileFind;
	BOOL bCheck = FALSE;
	SYSTEMTIME lpSystemTime;
	CString strCSVPath;

	GetLocalTime(&lpSystemTime); 


	strCSVPath.Format(_T("D:\\%04d.%02d_정산내역.csv"), lpSystemTime.wYear, lpSystemTime.wMonth);


	bCheck = fileFind.FindFile(strCSVPath);

	if (file.Open(strCSVPath, CFile::modeCreate | CFile::modeRead | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone) == FALSE)
	{
		AfxMessageBox(_T("CSV file open Fail"));
		return;
	}

	USHORT nShort = 0xfeff;  // Unicode BOM(Byte Order Mark).
	file.Write(&nShort, 2);

	if (!bCheck)
	{
		str.Format(_T("날짜\t채널\t수령인\t전화\t우편번호\t주소\t수량\t품목명\t금액(수량*물품액)"));
		file.Write((LPCSTR)(LPCTSTR)str, str.GetLength() * 2);
		file.Write(_T("\r\n"), 2);
	}

	file.SeekToEnd();

	str.Format(_T("%04d-%02d-%02d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s") ,lpSystemTime.wYear, lpSystemTime.wMonth, lpSystemTime.wDay, strChannel, strName, strPhone, strPostCode, strAddress, strNum, strProdName, strSum);


	file.Write((LPCSTR)(LPCTSTR)str, str.GetLength() * 2);
	file.Write(_T("\r\n"), 2);
	file.Close();
}

void SaleDlg::OnBnClickedBtnOrder()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (!(IDYES == AfxMessageBox(_T("발주확인 하시겠습니까?"), MB_YESNO)))
		return;

	int nIndex;
	CString strChannel, strName, strPhone, strPostCode, strAddress, strNum, strProdName, strSum;

	//채널
	nIndex = m_Combo_Company.GetCurSel();
	m_Combo_Company.GetLBText(nIndex, strChannel);

	//이름
	m_Edit_Name.GetWindowText(strName);

	//전화
	m_Edit_Phone.GetWindowText(strPhone);

	//우편번호
	m_Edit_PostCode.GetWindowText(strPostCode);

	//주소
	m_Edit_Address.GetWindowText(strAddress);

	//수량
	m_Edit_Num.GetWindowText(strNum);

	//품목명
	nIndex = m_Combo_ProdName.GetCurSel();
	m_Combo_ProdName.GetLBText(nIndex, strProdName);

	m_IniCompanyStock.SetSection(strChannel);

	int nStocknPrice[2];

	m_IniCompanyStock.GetIntArray(strProdName, nStocknPrice, 2);

	int nStock = nStocknPrice[0];
	int nSum = nStocknPrice[1] * _ttoi(strNum);
	
	strSum.Format(_T("%d"), nSum);

	if (_ttoi(strNum) > nStock)
	{
		CString strMsg;
		strMsg.Format(_T("[ %s , %s ] 재고가 부족합니다."), strChannel, strProdName);
		AfxMessageBox(strMsg);
		return;
	}

	WriteCSV(strChannel, strName, strPhone, strPostCode, strAddress, strNum, strProdName, strSum);

	nStocknPrice[0] = nStocknPrice[0] - _ttoi(strNum);

	m_IniCompanyStock.WriteIntArray(strProdName, nStocknPrice, 2);
}
