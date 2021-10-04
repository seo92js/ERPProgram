#pragma once


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
	//InventoryDlg 다이얼로그 버튼 및 크기 설정
	void		SetInventoryDlg();
	void		SetTitle();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
