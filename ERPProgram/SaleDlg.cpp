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
}


BEGIN_MESSAGE_MAP(SaleDlg, CDialogEx)
END_MESSAGE_MAP()


// SaleDlg 메시지 처리기


BOOL SaleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	SetSaleDlg();

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
}