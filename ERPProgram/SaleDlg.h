#pragma once


// SaleDlg 대화 상자

class SaleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SaleDlg)

public:
	SaleDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SaleDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SALE_DIALOG };

	//Sale 다이얼로그 버튼 및 크기 설정
	void		SetSaleDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
