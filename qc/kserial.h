#include "ThostFtdcMdApi.h"
#include <map>
#include <string>
#include <list>
#include <iostream>

#include"ThostFtdcUserApiStruct.h"


 struct mytick
{

	TThostFtdcPriceType	LastPrice;
	///�ϴν����
	TThostFtdcPriceType	PreSettlementPrice;
	///������
	TThostFtdcPriceType	PreClosePrice;
	///��ֲ���
	TThostFtdcLargeVolumeType	PreOpenInterest;
	///����
	TThostFtdcPriceType	OpenPrice;
	///��߼�
	TThostFtdcPriceType	HighestPrice;
	///��ͼ�
	TThostFtdcPriceType	LowestPrice;
	///����
	TThostFtdcVolumeType	Volume;
	///�ɽ����
	TThostFtdcMoneyType	Turnover;
	///�ֲ���
	TThostFtdcLargeVolumeType	OpenInterest;
	///������
	TThostFtdcPriceType	ClosePrice;

	///����޸�ʱ��
	TThostFtdcTimeType	UpdateTime;
	///����޸ĺ���
	TThostFtdcMillisecType	UpdateMillisec;
	///�����һ
	TThostFtdcPriceType	BidPrice1;
	///������һ
	TThostFtdcVolumeType	BidVolume1;
	///������һ
	TThostFtdcPriceType	AskPrice1;
	///������һ
	TThostFtdcVolumeType	AskVolume1;
	//TThostFtdcVolumeType	AskBidV;
	TThostFtdcInstrumentIDType	InstrumentID;
	///���վ���
	TThostFtdcPriceType	AveragePrice;
};

 struct bar
{
	char bar_date[9];
	char bar_time[9];
	double high;
	double low;
	double open;
	double close;
	int vol;
	int openinst;
	double je;
};
 struct bar_vol
{
	int df;
	int kf;
};
struct tick_ptr{
	mytick *tick;
	tick_ptr *next;
};
 struct list_p
{
	tick_ptr * h;
	FILE *fop;
	char tik_s[38];
	char tik_f[38];
};
 
class tick_list
{
private	:
	 tick_ptr *head;
public:
	static tick_ptr *wp;
	list_p * lp;
	tick_ptr * cou;
	FILE * tft;
	
	int n;
	tick_list();
	static char tik_s[38];
	static char tik_f[38];
	//static DWORD WINAPI w(LPVOID lParam);
	void add(mytick * tick);
	void write(char tik[38],char t[38]);
	double high();
	double low();
	double zf();
	double open();
	double close();
	double zd();
	
//	ofstream csv;
//	fstream _file;
//	ofstream ft;
};
struct bar_ptr //kָ��
{ 
	bar *b;
	bar_vol *bv;
	bar_ptr *next;
};
class k
{
	k();

};
class bar_list
{
public:
	bar_list();
	int n;
	int bar_count;
	bar_ptr * bars_h;
	bar_ptr * cou;
	bar_ptr * today;
	void add(bar *b, bar_vol *bv);
	int get_bar(int n);
	double ma(int n, int p);
	double mav(int n, int p);
	double macd_d(int a, int b, int c, int p);
	double macd_e(int a, int b, int c, int p);
	double vvh(int n, int p);
	double vvl(int n, int p);
};

