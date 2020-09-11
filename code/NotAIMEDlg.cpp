
// NotAIMEDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "NotAIME.h"
#include "NotAIMEDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CNotAIMEDlg 对话框



CNotAIMEDlg::CNotAIMEDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NOTAIME_DIALOG, pParent),
	_input_count(0),
	_focus_flag(false),
	_del_msg_flag(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNotAIMEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNotAIMEDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK1, &CNotAIMEDlg::OnBnClickedCheck1)
	ON_EN_CHANGE(IDC_EDIT1, &CNotAIMEDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CNotAIMEDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT2, &CNotAIMEDlg::OnEnChangeEdit2)
END_MESSAGE_MAP()


// CNotAIMEDlg 消息处理程序

BOOL CNotAIMEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNotAIMEDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNotAIMEDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNotAIMEDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNotAIMEDlg::OnBnClickedCheck1()
{
	_focus_flag = !_focus_flag;
	if (_focus_flag)
	{
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}
	else
	{
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}
}


void CNotAIMEDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if(!_del_msg_flag)
		++_input_count;
	((CEdit*)GetDlgItem(IDC_EDIT1))->GetWindowText(_wstr);
}
BOOL CNotAIMEDlg::PreTranslateMessage(MSG * pmsg)
{
	
	if (pmsg->message == WM_KEYDOWN && GetFocus()->GetDlgCtrlID()== IDC_EDIT1)
	{
		_del_msg_flag = false;
		if (pmsg->wParam == VK_RETURN)
		{
			this->OnBnClickedButton1();
			return TRUE;
		}
		else if (pmsg->wParam == VK_SPACE)
		{
			
			if (_input_count != 0)
			{
				--_input_count;
				string_process();
			}
			else
				return CDialog::PreTranslateMessage(pmsg);
		}
		else if (pmsg->wParam == VK_BACK)
		{
			_del_msg_flag = true;
			if (_input_count == 0)
			{
				return CDialog::PreTranslateMessage(pmsg);
			}
			else
			{
				--_input_count;
				return CDialog::PreTranslateMessage(pmsg);
			}
		}
		else
			return CDialog::PreTranslateMessage(pmsg);
	}
	else
		return CDialogEx::PreTranslateMessage(pmsg);
}
void CNotAIMEDlg::string_process()
{
	std::wstring ws1 = _wstr;
	std::wstring ws2 = ws1;
	size_t i = ws1.size() - _input_count-1;
	wchar_t pre = 0;
	bool pre_flag = false;
	for (size_t j=i; i < ws1.size(); ++j,++i)
	{
		bool mark = false;
		if (pre_flag)
		{
			switch (ws1[i])
			{
			case L'j':case L'k':case L't':case L'f':case L'v':
			case L'm':case L'n':case L'l':case L'z':
			case L'd':case L'g':case L'r':case L'b':case L'p':
				ws2[j] = single_char_table(ws1[i]);
				break;
			case L'a':
				switch (pre) {
				case L'j':
					ws2[j] = _T('я');
					mark = true;
					break;
				default:
					mark = false;
					break;
				}
				break;
			case L'e':
				switch (pre) {
				case L'j':
					ws2[j] = _T('е');
					mark = true;
					break;
				default:
					ws2[j] = single_char_table(ws1[i]);
					break;
				}
				break;
			case L'u':
				switch (pre) {
				case L'j':
					ws2[j] = _T('ю');
					mark = true;
					break;
				default:
					ws2[j] = single_char_table(ws1[i]);
					break;
				}
				break;
			case L'o':
				switch (pre) {
				case L'j':
					ws2[j] = _T('ё');
					mark = true;
					break;
				default:
					ws2[j] = single_char_table(ws1[i]);
					break;
				}
				break;
			//复元音结束

			case L's':
				switch (pre) {
				case L't':
					ws2[j] = _T('ц');
					mark = true;
					break;
				case L'd':
					ws2[j] = _T('з');
					mark = true;
					break;
				default:
					ws2[j] = single_char_table(ws1[i]);
					break;
				}
				break;
			case L'h':
				switch (pre) {
				case L'c':
					ws2[j] = _T('ч');
					mark = true;
					break;
				case L'z':
					ws2[j] = _T('ж');
					mark = true;
					break;
				case L's':
					ws2[j] = _T('ш');
					mark = true;
					break;
				case L'x':
					ws2[j] = _T('щ');
					mark = true;
					break;
				default:
					ws2[j] = single_char_table(ws1[i]);
					break;
				}
				break;
			case L'i':
				switch (pre)
				{
				case 'e':
					ws2[j] = _T('ы');
					mark = true;
					break;
				default:
					ws2[j] = single_char_table(ws1[i]);
					break;
				}
				break;
			default:
				ws2[j] = single_char_table(ws1[i]);
				break;
			}

		}
		else
		{
			ws2[j] = single_char_table(ws1[i]);
		}
		if (!mark)
		{
			pre = ws1[i];
			pre_flag = true;
		}
		else
		{
			pre_flag = false;
			ws2[j - 1] = 0;
		}
	}
	CString res;
	for (auto i = ws2.begin(); i != ws2.end(); i++)
	{
		if (*i != 0)
			res.AppendChar(*i);
	}
	((CEdit*)GetDlgItem(IDC_EDIT1))->SetWindowText(res);
	size_t len = res.GetLength();
	((CEdit*)GetDlgItem(IDC_EDIT1))->SetSel(len, len, false);
	_input_count = 0;
}
void CNotAIMEDlg::OnBnClickedButton1()
{

	this->string_convert();
	((CEdit*)GetDlgItem(IDC_EDIT2))->SetWindowText(_wstr);
}
wchar_t CNotAIMEDlg::single_char_table(wchar_t wch)
{
	switch (wch)
	{
	case L'j':
	    return _T('й');
	case L'k':
	    return _T('к');
	case L'g':
	    return _T('г');
	case L'n':
	    return _T('н');
	case L'e':
	    return _T('э');
	case L'h':
	    return _T('х');
	case L'[':
	    return _T('ъ');
	case L'f':
	    return _T('ф');
	case L']':
	    return _T('ь');
	case L'v':
	    return _T('в');
	case L'p':
	    return _T('п');
	case L'r':
	    return _T('р');
	case L'l':
	    return _T('л');
	case L'd':
	    return _T('д');
	case L's':
	    return _T('с');
	case L'm':
	    return _T('м');
	case L'i':
	    return _T('и');
	case L't':
	    return _T('т');
	case L'b':
	    return _T('б');
	case L'a':
		return _T('а');
	case L'o':
		return _T('о');
	case L'u':
		return _T('у');
	case L'c':
		return _T('ц');
	case L'z':
		return _T('з');
	}
}
void CNotAIMEDlg::string_convert()
{
	State s=State::no_pre;
	wchar_t pre=L'\0';
	std::wstring buff;
	wchar_t this_one;
	for (auto i = 0; i < _wstr.GetLength(); i++)
	{
		this_one = _wstr[i];
		switch (s)
		{
		case State::no_pre:
			this_one = single_char_table(this_one);
			break;
		case State::after_vowel:
			switch (_wstr[i]) {
			default:
				this_one = single_char_table(this_one);
				break;
			}
		case State::after_consonant:
			switch (_wstr[i]) {
			case 'a':
				switch (pre) {
				case 'j':
					this_one = 'я';
					break;
				default:
					this_one = single_char_table(this_one);
					break;
				}
				break;
			case 'u':
				switch (pre) {
				case'j':
					this_one = 'ю';
					break;
				default:
					this_one = single_char_table(this_one);
					break;
				}
			case 's':
				switch (pre) {
				case't':
					this_one = 'ц';
					break;
				default:
					this_one = single_char_table(this_one);
					break;
				}
			}
		}
		exit_point:
		buff.push_back(this_one);
	}
	_wstr = buff.c_str();
}
void CNotAIMEDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
