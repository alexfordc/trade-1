
// CTP_mfcDlg.h : ͷ�ļ�
//
#include "MdSpi.h"
#include "TdSpi.h"
#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#pragma once
#include "afxwin.h"
#define WM_MY_MESSAGE WM_USER+100 

// CCTP_mfcDlg �Ի���
class CCTP_mfcDlg : public CDialogEx
{
// ����
public:
	CCTP_mfcDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CTP_MFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	afx_msg LRESULT MyMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT Mycount(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT blcount(WPARAM wParam, LPARAM lParam);
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	HWND hwnd;
	int  split(char dst[][3], char* str, const char* spl);
	afx_msg void OnBnClickedOk();
	static DWORD WINAPI  quotethread(LPVOID lParam);
	static  MdSpi *msp;
	
//	DWORD WINAPI  quotethread();
	static DWORD WINAPI order(LPVOID lParam);
	static MdSpi *md_op;
	static CThostFtdcTraderApi *tdapi;
	void OnTimer(UINT_PTR nIDEvent);
//	void OnClose();
	CEdit mask;
	CEdit l_cou;
	afx_msg void OnBnClickedButton1();
	CEdit edit_bl;
	HANDLE mThread = NULL;
	HANDLE tThread = NULL;
	bool thread_stat;
	CButton cbu;
	tick_list *ts;
	bool wt;
	CComboBox run_msg;
};
