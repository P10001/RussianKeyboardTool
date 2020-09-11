
// NotAIMEDlg.h: 头文件
//

#pragma once

#include <string>
// CNotAIMEDlg 对话框
class CNotAIMEDlg : public CDialogEx
{
// 构造
public:
	CNotAIMEDlg(CWnd* pParent = nullptr);	// 标准构造函数
public:
	enum State
	{
		no_pre,
		after_consonant,
		after_vowel
	};
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NOTAIME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	//状态变量
	bool _focus_flag;//置顶
	bool _del_msg_flag;
	//待处理数据
	CString _wstr;
	int _input_count;
private:
	void string_convert();
	void string_process();
	wchar_t single_char_table(wchar_t wch);
public:
	//父类消息处理虚函数重写
	BOOL PreTranslateMessage(MSG* pmsg);
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnEnChangeEdit1();

	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit2();
};
