// CalculateDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "ERPProgram.h"
#include "ERPProgramDlg.h"
#include "CalculateDlg.h"
#include "afxdialogex.h"


// CalculateDlg 대화 상자

IMPLEMENT_DYNAMIC(CalculateDlg, CDialogEx)

CalculateDlg::CalculateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATE_DIALOG, pParent)
{

}

CalculateDlg::~CalculateDlg()
{
}

void CalculateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CalculateDlg, CDialogEx)
END_MESSAGE_MAP()


// CalculateDlg 메시지 처리기


BOOL CalculateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	SetCalculateDlg();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CalculateDlg::SetCalculateDlg()
{
	int nCaculateDlg_X = 120;
	int nCaculateDlg_Y = 10;
	int nCalculateDlg_Width = 1350;
	int nCalculateDlg_Height = 840;

	MoveWindow(nCaculateDlg_X, nCaculateDlg_Y, nCalculateDlg_Width, nCalculateDlg_Height);

	SetTitle();
}

void CalculateDlg::SetTitle()
{
	int nTitle_Width = 1350;
	int nTitle_Height = 45;

	GetDlgItem(IDC_BTN_CALCULATE_TITLE)->MoveWindow(0, 0, nTitle_Width, nTitle_Height);
}