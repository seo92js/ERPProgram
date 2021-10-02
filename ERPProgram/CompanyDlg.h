#pragma once


// CompanyDlg 대화 상자

class CompanyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CompanyDlg)

public:
	CompanyDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CompanyDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_COMPANY_DIALOG };

	//Company 다이얼로그 버튼 및 크기 설정
	void		SetCompanyDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
