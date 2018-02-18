
// CTP_mfcDlg.cpp : ʵ���ļ�
//

#include "MdSpi.h"
#include "TdSpi.h"
#include <stdio.h>
#include <direct.h>
#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include <iostream>
#include <sstream>
#include "stdafx.h"
#include "CTP_mfc.h"
#include "CTP_mfcDlg.h"
#include "afxdialogex.h"
#pragma comment(lib,"thostmduserapi.lib")
#pragma comment(lib,"thosttraderapi.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCTP_mfcDlg �Ի���



CCTP_mfcDlg::CCTP_mfcDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CCTP_mfcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
MdSpi *CCTP_mfcDlg::msp = NULL;
void CCTP_mfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mask);
	DDX_Control(pDX, IDC_EDIT2, l_cou);
	DDX_Control(pDX, IDC_EDIT3, edit_bl);
	DDX_Control(pDX, IDOK, cbu);
	DDX_Control(pDX, IDC_COMBO1, run_msg);
}

BEGIN_MESSAGE_MAP(CCTP_mfcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	//	ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_MY_MESSAGE, MyMessage)
	ON_MESSAGE(WM_MY_count, Mycount)
	ON_MESSAGE(WM_MY_bl, blcount)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CCTP_mfcDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CCTP_mfcDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


int CaculateWeekDay(int y, int m, int d)
{
	int week = 0;
	if (m == 1){ m = 13; y--; }
	if (m == 2) { m = 14; y--; }
	week = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7; //1752��9��3��֮��Ĺ�ʽ
	int weekstr = 0;
	switch (week)
	{
	case 0: {weekstr = 1; break; }
	case 1: {weekstr = 2; break; }
	case 2: {weekstr = 3; break; }
	case 3: {weekstr = 4; break; }
	case 4: {weekstr = 5; break; }
	case 5: {weekstr = 6; break; }
	case 6: {weekstr = 7; break; }
	}
	return weekstr;
}
// CCTP_mfcDlg ��Ϣ�������
void CCTP_mfcDlg::OnTimer(UINT_PTR nIDEvent)
{
	SYSTEMTIME st;
	CString strDate, strTime;
	GetLocalTime(&st);
	int d = CaculateWeekDay(st.wYear, st.wMonth, st.wDay);
	int s = st.wHour * 60 + st.wMinute;
	bool jy = false;

	if ((s > 166 && s<520) || (s>920 && s < 1150) || (s>690 && s<800)) jy = false; else jy = true;
	if (!jy || d>5)
	{
		if (s == 692 || s == 922 || s == 168)
		{
			if (msp != NULL && !wt)
			{
				for (int i = 0; i < 20; i++)
				{
					msp->pi[i]->ts->write(msp->pi[i]->tik, msp->pi[i]->tik_f);
				}
				wt = true;
			}
		}
		if ((s > 170 && s<520) || (s>924 && s < 1250) || (s>694 && s < 800))
			AfxGetMainWnd()->SendMessage(WM_CLOSE);
		/*	if (thread_stat)
			{
			//SuspendThread(hThread);

			TerminateThread(hThread, 0);
			thread_stat = false;
			hThread = NULL;
			}*/
	}
	else
	{
		//quotethread();
		//	order();
		if (mThread == NULL)
		{
			mThread = CreateThread(NULL, 0, quotethread, this, 0, NULL);
			//	tThread = CreateThread(NULL, 0,order, this, 0, NULL);
			thread_stat = true;
			wt = false;
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}
BOOL CCTP_mfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	SetTimer(1, 10000, NULL);
	cbu.EnableWindow(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCTP_mfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCTP_mfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCTP_mfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCTP_mfcDlg::OnBnClickedOk()
{

}
MdSpi *CCTP_mfcDlg::md_op = NULL;
CThostFtdcTraderApi *CCTP_mfcDlg::tdapi = NULL;
DWORD WINAPI  CCTP_mfcDlg::quotethread(LPVOID lParam)
{
	HWND hw = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	CThostFtdcMdApi *mdapi = CThostFtdcMdApi::CreateFtdcMdApi();
	MdSpi *mdspi = new MdSpi(mdapi);
	md_op = mdspi;
	msp = mdspi;
	mdspi->mainh = hw;
	//ע���¼��������
	mdapi->RegisterSpi(mdspi);
	////��ǰ�û�����
	mdapi->RegisterFront("tcp://116.236.239.136:41213");
	mdapi->Init();
	mdapi->Join();
	return 1;
}
//	mdapi->RegisterFront("tcp://180.168.146.187:10010");

DWORD WINAPI  CCTP_mfcDlg::order(LPVOID lParam)
{
	tdapi = CThostFtdcTraderApi::CreateFtdcTraderApi();
	TdSpi *tdspi = new TdSpi(tdapi);
	HWND hw = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	//ע���¼��������
	tdapi->RegisterSpi(tdspi);
	//���Ĺ�������˽����
	tdspi->mainh = hw;
	tdapi->SubscribePublicTopic(THOST_TERT_RESTART);
	tdapi->SubscribePrivateTopic(THOST_TERT_RESTART);
	//ע��ǰ�û�
	tdapi->RegisterFront("tcp://180.168.146.187:10000");	//ģ��
	//��ǰ�û�����
	tdapi->Init();
	tdapi->Join();
	return 0;
}
int  CCTP_mfcDlg::split(char dst[][3], char* str, const char* spl)
{
	int n = 0;
	char *result = NULL;
	result = strtok(str, spl);
	while (result != NULL)
	{
		strcpy(dst[n++], result);
		result = strtok(NULL, spl);
	}
	return n;
}

LRESULT  CCTP_mfcDlg::MyMessage(WPARAM wParam, LPARAM lParam)
{
	CString str;
	CThostFtdcDepthMarketDataField *info;
	info = (CThostFtdcDepthMarketDataField *)wParam;
	CString clog;
	int h, m, s;
	char t[3][3];
	for (int v = 0; v < 3; v++){
		for (int c = 0; c < 3; c++)
		{
			t[v][c] = info->UpdateTime[v * 3 + c];
		}
	}
	//	mask.GetWindowTextW(clog);
	clog = "";
	clog += info->InstrumentID;
	str.Format(_T("%d"), info->Volume);
	clog += "�ɽ�����";
	clog += str;
	clog += "\r\n";
	str.Format(_T("%.2f"), info->OpenInterest);
	clog += "�ֲ�����";
	clog += str;
	clog += "\r\n";
	str.Format(_T("%.2f"), info->LastPrice);
	clog += "��  �ۣ�";
	clog += str;
	clog += "\r\n";
	str.Format(_T("%.2f"), info->BidPrice1);
	clog += "��  �ۣ�";
	clog += str;
	clog += "\r\n";
	str.Format(_T("%.2f"), info->AskPrice1);
	clog += "��  �ۣ�";
	clog += str;
	clog += "\r\n";
	str.Format(_T("%d"), info->BidVolume1);
	clog += "ί������";
	clog += str;
	clog += "\r\n";
	str.Format(_T("%d"), info->AskVolume1);
	clog += "��������";
	clog += str;
	clog += "\r\n";
	clog += info->ActionDay;
	clog += "\r\n";
	clog += t[0];
	clog += ":";
	clog += t[1];
	clog += ":";
	clog += t[2];
	clog += "\r\n";
	str.Format(_T("%d"), info->UpdateMillisec);
	clog += str;
	clog += "\r\n";
	SYSTEMTIME st;
	CString strDate, strTime;
	GetLocalTime(&st);
	char year[5], mon[5], day[5], mi[5];
	char datec[28] = "";
	sprintf(year, "%d", st.wHour);
	sprintf(mon, "%d", st.wMinute);
	sprintf(day, "%d", st.wSecond);
	sprintf(mi, "%d", st.wMilliseconds);
	strcat(datec, "h:");
	strcat(datec, year);
	strcat(datec, "m:");
	strcat(datec, mon);
	strcat(datec, "s:");
	strcat(datec, day);
	strcat(datec, "mi:");
	strcat(datec, mi);
	clog += datec;
	mask.SetWindowTextW(clog);
	return 0;
}
LRESULT  CCTP_mfcDlg::Mycount(WPARAM wParam, LPARAM lParam)
{
	CString str;
	str.Format(_T("%d"), wParam);
	run_msg.SetWindowTextW(str);
	return 0;
}
LRESULT  CCTP_mfcDlg::blcount(WPARAM wParam, LPARAM lParam)
{
	return 0;
}
void CCTP_mfcDlg::OnBnClickedButton1()
{
}
