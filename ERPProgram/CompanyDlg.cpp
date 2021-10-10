// CompanyDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "ERPProgram.h"
#include "ERPProgramDlg.h"
#include "CompanyDlg.h"
#include "afxdialogex.h"


// CompanyDlg 대화 상자

IMPLEMENT_DYNAMIC(CompanyDlg, CDialogEx)

CompanyDlg::CompanyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COMPANY_DIALOG, pParent)
{

}

CompanyDlg::~CompanyDlg()
{
}

void CompanyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_COMPANY, m_ListCtr_Company);
	DDX_Control(pDX, IDC_EDIT_COMPANY, m_Edit_Company);
	DDX_Control(pDX, IDC_EDIT_MANAGER, m_Edit_Manager);
	DDX_Control(pDX, IDC_EDIT_PHONE, m_Edit_Phone);
}


BEGIN_MESSAGE_MAP(CompanyDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_COMPANY_ADD, &CompanyDlg::OnBnClickedBtnCompanyAdd)
END_MESSAGE_MAP()


// CompanyDlg 메시지 처리기


BOOL CompanyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_IniCompanyInfo.SetFile("D:\\업체정보리스트.Ini");
	m_IniCompanyStock.SetFile("D:\\업체상품리스트.Ini");

	SetCompanyDlg();

	InitCompanyList();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CompanyDlg::SetCompanyDlg()
{
	int nCompanyDlg_X = 120;
	int nCompanyDlg_Y = 10;
	int nCompanyDlg_Width = 1350;
	int nCompanyDlg_Height = 840;

	MoveWindow(nCompanyDlg_X, nCompanyDlg_Y, nCompanyDlg_Width, nCompanyDlg_Height);

	SetTitle();
	SetPosition_Company();
	SetPosition_StaticCompany();
	SetPosition_StaticManager();
	SetPosition_StaticPhone();
	SetPosition_EditCompany();
	SetPosition_EditManager();
	SetPosition_EditPhone();
	SetPosition_BtnCompanyAdd();
}

void CompanyDlg::SetTitle()
{
	int nTitle_Width = 1350;
	int nTitle_Height = 45;

	GetDlgItem(IDC_BTN_COMPANY_TITLE)->MoveWindow(0, 0, nTitle_Width, nTitle_Height);
}

void CompanyDlg::SetPosition_Company()
{
	int nCompany_X = 20;
	int nCompany_Y = 110;
	int nCompany_Width = 300;
	int nCompany_Height = 500;

	m_ListCtr_Company.MoveWindow(nCompany_X, nCompany_Y, nCompany_Width, nCompany_Height);
}

void CompanyDlg::SetPosition_StaticCompany()
{
	int nStaticCompany_X = 20;
	int nStaticCompany_Y = 625;
	int nStaticCompany_Width = 40;
	int nStaticCompany_Height = 25;

	GetDlgItem(IDC_STATIC_COMPANY)->MoveWindow(nStaticCompany_X, nStaticCompany_Y, nStaticCompany_Width, nStaticCompany_Height);
}

void CompanyDlg::SetPosition_StaticManager()
{
	int nStaticManager_X = 20;
	int nStaticManager_Y = 665;
	int nStaticManager_Width = 40;
	int nStaticManager_Height = 25;

	GetDlgItem(IDC_STATIC_MANAGER)->MoveWindow(nStaticManager_X, nStaticManager_Y, nStaticManager_Width, nStaticManager_Height);
}

void CompanyDlg::SetPosition_StaticPhone()
{
	int nStaticPhone_X = 20;
	int nStaticPhone_Y = 705;
	int nStaticPhone_Width = 40;
	int nStaticPhone_Height = 25;

	GetDlgItem(IDC_STATIC_PHONE)->MoveWindow(nStaticPhone_X, nStaticPhone_Y, nStaticPhone_Width, nStaticPhone_Height);
}

void CompanyDlg::SetPosition_EditCompany()
{
	int nEditCompany_X = 60;
	int nEditCompany_Y = 620;
	int nEditCompany_Width = 180;
	int nEditCompany_Height = 25;

	GetDlgItem(IDC_EDIT_COMPANY)->MoveWindow(nEditCompany_X, nEditCompany_Y, nEditCompany_Width, nEditCompany_Height);
}

void CompanyDlg::SetPosition_EditManager()
{
	int nEditManager_X = 60;
	int nEditManager_Y = 660;
	int nEditManager_Width = 180;
	int nEditManager_Height = 25;

	GetDlgItem(IDC_EDIT_MANAGER)->MoveWindow(nEditManager_X, nEditManager_Y, nEditManager_Width, nEditManager_Height);
}

void CompanyDlg::SetPosition_EditPhone()
{
	int nEditPhone_X = 60;
	int nEditPhone_Y = 700;
	int nEditPhone_Width = 180;
	int nEditPhone_Height = 25;

	GetDlgItem(IDC_EDIT_PHONE)->MoveWindow(nEditPhone_X, nEditPhone_Y, nEditPhone_Width, nEditPhone_Height);
}

void CompanyDlg::SetPosition_BtnCompanyAdd()
{
	int nBtnCompanyAdd_X = 250;
	int nBtnCompanyAdd_Y = 620;
	int nBtnCompanyAdd_Width = 70;
	int nBtnCompanyAdd_Height = 65;
	  
	GetDlgItem(IDC_BTN_COMPANY_ADD)->MoveWindow(nBtnCompanyAdd_X, nBtnCompanyAdd_Y, nBtnCompanyAdd_Width, nBtnCompanyAdd_Height);
}

void CompanyDlg::InitCompanyList()
{
	m_ListCtr_Company.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_ListCtr_Company.InsertColumn(0, _T(""), NULL, 0);
	m_ListCtr_Company.InsertColumn(1, _T("업체리스트"), LVCFMT_CENTER, 300);

	LoadCompanyList();
}

void CompanyDlg::AddCompany(CString strCompany, CString strManager, CString strPhone)
{
	POSITION pos;
	CString str, strProductCount, strProductName, strProductPrice;
	int nTemp;

	m_IniCompanyInfo.SetSection(strCompany);

	m_IniCompanyInfo.Write_String(_T("담당자"), strManager);
	m_IniCompanyInfo.Write_String(_T("연락처"), strPhone);

	LoadCompanyList();
}

void CompanyDlg::OnBnClickedBtnCompanyAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strCompany, strManager, strManagerPhone, strMessage;

	m_Edit_Company.GetWindowText(strCompany);
	m_Edit_Manager.GetWindowText(strManager);
	m_Edit_Phone.GetWindowText(strManagerPhone);

	if (strCompany == "")
	{
		AfxMessageBox(_T("업체명을 입력하세요"));
		return;
	}

	strMessage.Format(_T("[ %s ] 업체를 추가 하시겠습니까?"), strCompany);

	if (IDYES == AfxMessageBox(strMessage, MB_YESNO))
	{
		AddCompany(strCompany, strManager, strManagerPhone);
	}
	else
		return;
}

void CompanyDlg::LoadCompanyList()
{
	CStringList strCompanyList;
	CString     strTemp;

	m_ListCtr_Company.DeleteAllItems();

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

		m_ListCtr_Company.InsertItem(i, _T(""));
		m_ListCtr_Company.SetItem(i, 1, LVIF_TEXT, strTemp, 0, 0, 0, NULL);
	}
}