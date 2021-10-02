
// ERPProgramDlg.cpp: 구현 파일
//

#include "framework.h"
#include "ERPProgram.h"
#include "ERPProgramDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CERPProgramDlg 대화 상자



CERPProgramDlg::CERPProgramDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ERPPROGRAM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CERPProgramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CERPProgramDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_INVENTORY, &CERPProgramDlg::OnBnClickedBtnInventory)
	ON_BN_CLICKED(IDC_BTN_COMPANY, &CERPProgramDlg::OnBnClickedBtnCompany)
	ON_BN_CLICKED(IDC_BTN_CALCULATE, &CERPProgramDlg::OnBnClickedBtnCalculate)
	ON_BN_CLICKED(IDC_BTN_SALE, &CERPProgramDlg::OnBnClickedBtnSale)
END_MESSAGE_MAP()


// CERPProgramDlg 메시지 처리기

BOOL CERPProgramDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	SetMainDialog();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CERPProgramDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CERPProgramDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CERPProgramDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CERPProgramDlg::SetMainDialog()
{
	int nMainDlg_X = 0;
	int	nMainDlg_Y = 0;
	int nMainDlg_Width = 1500;
	int nMainDlg_Height = 900;

	MoveWindow(nMainDlg_X, nMainDlg_Y, nMainDlg_Width, nMainDlg_Height);

	SetMainButtonPosition();

	CreateInventoryDlg();
	CreateCompanyDlg();
	CreateCalculateDlg();
	CreateSaleDlg();
}

void CERPProgramDlg::SetMainButtonPosition()
{
	int nWidth, nHeight, nXPos, nYPos, nYPosGap;

	nWidth = 100;
	nHeight = 80;
	nXPos = 10;
	nYPos = 10;
	nYPosGap = nHeight + 10;

	GetDlgItem(IDC_BTN_INVENTORY)->MoveWindow(nXPos, nYPos, nWidth, nHeight);

	nYPos += nYPosGap;
	GetDlgItem(IDC_BTN_COMPANY)->MoveWindow(nXPos, nYPos, nWidth, nHeight);

	nYPos += nYPosGap;
	GetDlgItem(IDC_BTN_SALE)->MoveWindow(nXPos, nYPos, nWidth, nHeight);

	nYPos += nYPosGap;
	GetDlgItem(IDC_BTN_CALCULATE)->MoveWindow(nXPos, nYPos, nWidth, nHeight);

	//
	GetDlgItem(IDCANCEL)->MoveWindow(1400, 800, 70, 30);
}

void CERPProgramDlg::OnBnClickedBtnInventory()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowInventoryDlg(SW_SHOW);
	ShowCompanyDlg(SW_HIDE);
	ShowCaculateDlg(SW_HIDE);
	ShowSaleDlg(SW_HIDE);
}


void CERPProgramDlg::OnBnClickedBtnCompany()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowCompanyDlg(SW_SHOW);
	ShowInventoryDlg(SW_HIDE);
	ShowCaculateDlg(SW_HIDE);
	ShowSaleDlg(SW_HIDE);
}


void CERPProgramDlg::OnBnClickedBtnCalculate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowCaculateDlg(SW_SHOW);
	ShowInventoryDlg(SW_HIDE);
	ShowCompanyDlg(SW_HIDE);
	ShowSaleDlg(SW_HIDE);
}


void CERPProgramDlg::OnBnClickedBtnSale()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowSaleDlg(SW_SHOW);
	ShowInventoryDlg(SW_HIDE);
	ShowCompanyDlg(SW_HIDE);
	ShowCaculateDlg(SW_HIDE);
}

void CERPProgramDlg::CreateInventoryDlg()
{
	m_pInventoryDlg = new InventoryDlg;
	m_pInventoryDlg->Create(InventoryDlg::IDD, this);

	ShowInventoryDlg(SW_HIDE);
}

void CERPProgramDlg::CreateCompanyDlg()
{
	m_pCompanyDlg = new CompanyDlg;
	m_pCompanyDlg->Create(CompanyDlg::IDD, this);

	ShowCompanyDlg(SW_HIDE);
}

void CERPProgramDlg::CreateCalculateDlg()
{
	m_pCalculateDlg = new CalculateDlg;
	m_pCalculateDlg->Create(CalculateDlg::IDD, this);

	ShowCaculateDlg(SW_HIDE);
}

void CERPProgramDlg::CreateSaleDlg()
{
	m_pSaleDlg = new SaleDlg;
	m_pSaleDlg->Create(SaleDlg::IDD, this);

	ShowSaleDlg(SW_HIDE);
}

void CERPProgramDlg::ShowInventoryDlg(int nShowOrHide)
{
	m_pInventoryDlg->ShowWindow(nShowOrHide);
}

void CERPProgramDlg::ShowCompanyDlg(int nShowOrHide)
{
	m_pCompanyDlg->ShowWindow(nShowOrHide);
}

void CERPProgramDlg::ShowCaculateDlg(int nShowOrHide)
{
	m_pCalculateDlg->ShowWindow(nShowOrHide);
}

void CERPProgramDlg::ShowSaleDlg(int nShowOrHide)
{
	m_pSaleDlg->ShowWindow(nShowOrHide);
}