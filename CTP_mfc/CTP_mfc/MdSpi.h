#ifndef MDSPI_H
#define MDSPI_H
#include "ThostFtdcMdApi.h"
#include <map>
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include"ThostFtdcUserApiStruct.h"
#include "ThostFtdcTraderApi.h"
#include "kserial.h"
#include <vector>
#define WM_MY_MESSAGE WM_USER+100 
#define WM_MY_count WM_USER+101 
#define WM_MY_bl WM_USER+102
#define DEBUG

using namespace std;
typedef enum �ṹ { ��, ��, �м�, ��� }jg;
typedef struct ��
{
	double high;
	double low;
	double o;
	bar ba;
	jg zd;
	int index;
};
typedef vector<��*> blist;
typedef vector<bar *> barvect;
typedef struct scp
{
	bar_list *bs;
	blist bl;
	barvect tmpbs;
};
class Pzid
{
public:
	Pzid(char *pzid);
	void makek();
	void k_write();

	HWND mainh;
	void make_k(const mytick *tick);
	void make_b(CThostFtdcDepthMarketDataField *tick);
	int js_tick(mytick *tick);
	int split(char dst[][3], char* str, const char* spl);
	int c_h, c_m;//Сʱ�ͷ���
	double k_h;//
	double k_l;
	int c_vol;//k��
	double c_je;//�˽��
	bar * p_bar;
	bar_vol *p_bv;
	tick_list *ts;//tick��list
	bar_list *bs;//k_Bar list
	blist bl;//
	barvect tmpbs;//
	jg_list *jl; //
	bool wed;
	
	char tik[38];//�ļ���
	char tik_f[38];//csv
	mytick *pretick;//ǰһtick
	char id[6];

	static DWORD WINAPI  ����(LPVOID lParam);
	static tick_ptr *wp;//��̬tuckͷ
	static DWORD WINAPI ��������(scp * t);
	//	static DWORD WINAPI  w(LPVOID lParam);
	int askv;
	int bibv;
	void writed();
private:
	void process(mytick  *tick);
	void of_p(char *pzid);
	HANDLE sch;
	ofstream fk;
	ofstream ck;
	ofstream fb;
	void gettick();
	void getbar(char* str);
	ifstream itick, ibar;

};
class MdSpi :public CThostFtdcMdSpi{
public:
	MdSpi(CThostFtdcMdApi *mdapi);
	//��������ʱ����
	void OnFrontConnected();
	///��¼������Ӧ
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo,
		int nRequestID, bool bIsLast);
	///�ǳ�������Ӧ
	void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo,
		int nRequestID, bool bIsLast);
	///��������Ӧ��
	void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo,
		int nRequestID, bool bIsLast);
	///ȡ����������Ӧ��
	void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo,
		int nRequestID, bool bIsLast);
	///�������֪ͨ
	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

	///���ɷ�����
	void trading(int ss, int zz);
	CThostFtdcTraderApi *tdapi;
	HWND mainh;
	Pzid *pi[20];
private:
	CThostFtdcMdApi *mdapi;
	CThostFtdcReqUserLoginField *loginField;
	int loginRequestID;

};

#endif