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
}


BEGIN_MESSAGE_MAP(CompanyDlg, CDialogEx)
END_MESSAGE_MAP()


// CompanyDlg 메시지 처리기


BOOL CompanyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	SetCompanyDlg();

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
}
