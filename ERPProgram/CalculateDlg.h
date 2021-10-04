#pragma once


// CalculateDlg 대화 상자

class CalculateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CalculateDlg)

public:
	CalculateDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CalculateDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CALCULATE_DIALOG };

	//Calculate 다이얼로그 버튼 및 크기 설정
	void		SetCalculateDlg();
	void		SetTitle();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
