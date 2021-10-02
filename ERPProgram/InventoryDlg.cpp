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
}


BEGIN_MESSAGE_MAP(InventoryDlg, CDialogEx)
END_MESSAGE_MAP()


// InventoryDlg 메시지 처리기

BOOL InventoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	SetInventoryDlg();

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
}


