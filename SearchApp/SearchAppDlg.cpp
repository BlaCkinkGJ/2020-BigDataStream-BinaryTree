
// SearchAppDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "SearchApp.h"
#include "SearchAppDlg.h"
#include "BST.h"
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


// CSearchAppDlg 대화 상자



CSearchAppDlg::CSearchAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEARCHAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSearchAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INSERT_EDIT, m_insertEdit);
	DDX_Control(pDX, IDC_LIST3, m_listBox);
	DDX_Control(pDX, IDC_PICTURE_BOX, m_pictureBox);
}

BEGIN_MESSAGE_MAP(CSearchAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INSERT_BUTTON, &CSearchAppDlg::OnBnClickedInsertButton)
	ON_BN_CLICKED(IDC_INSERT_BUTTON2, &CSearchAppDlg::OnBnClickedInsertButton2)
END_MESSAGE_MAP()


// CSearchAppDlg 메시지 처리기

BOOL CSearchAppDlg::OnInitDialog()
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSearchAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSearchAppDlg::OnPaint()
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
HCURSOR CSearchAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSearchAppDlg::OnBnClickedInsertButton()
{
	CString strData;
	int data;

	m_insertEdit.GetWindowTextW(strData);
	if (strData.IsEmpty()) {
		return;
	}

	data = _ttoi(strData);

	tree.Insert(Element(data));
	tree.getTreePoints(keys);

	CRect rect;
	m_pictureBox.GetClientRect(&rect);
	CDC* pDC = m_pictureBox.GetWindowDC();
	pDC->SetWindowExt(100, 100);
	pDC->SetWindowExt(rect.Width(), rect.Height());
	pDC->FillSolidRect(&rect, RGB(255, 255, 255));
	for (const auto& _key : keys) {
		CString temp;
		int key = _key.first;
		int x = _key.second.second;
		int y = _key.second.first;
		temp.Format(_T("%d"), key);
		x = 30 * x;
		y = 20 * y;
		CRect bound(x - 1, y - 1, x + 31, y + 21);
		CRect textLocation(x, y, x + 30, y + 20);
		BstNode* _node = tree.Search(Element(key));
		int _leftKey = -1, _rightKey = -1;
		if (_node->LeftChild)
			_leftKey = tree.Search(Element(_node->LeftChild->data.key))->data.key;
		if (_node->RightChild)
			_rightKey = tree.Search(Element(_node->RightChild->data.key))->data.key;

		if (_leftKey != -1) {
			int _key = _leftKey;
			int key = keys.find(_key)->first;
			int toX = 30 * keys.find(_key)->second.second;
			int toY = 20 * keys.find(_key)->second.first;
			cout << x + 31 << ", " << y + 21 << " ==> " << toX - 1 << ", " << toY - 1 << endl;
			pDC->MoveTo(x + 31, y + 21);
			pDC->LineTo(toX - 1, toY - 1);
		}
		if (_rightKey != -1) {
			int _key = _rightKey;
			int key = keys.find(_key)->first;
			int toX = 30 * keys.find(_key)->second.second;
			int toY = 20 * keys.find(_key)->second.first;
			cout << x + 31 << ", " << y + 21 << " ==> " << toX - 1 << ", " << toY - 1 << endl;
			pDC->MoveTo(x + 31, y + 21);
			pDC->LineTo(toX - 1, toY - 1);

		}
		pDC->Rectangle(&bound);
		pDC->DrawText(temp, &textLocation, DT_CENTER);
	}
	m_pictureBox.ReleaseDC(pDC);
	UpdateWindow();
}

// TODO: display도 구현할 것!


void CSearchAppDlg::OnBnClickedInsertButton2()
{
	vector<CString> v;
	int i = 0;
	tree.display(v);
	m_listBox.ResetContent();
	for (const auto& value : v) {
		m_listBox.InsertString(i, value);
		i++;
	}
}
