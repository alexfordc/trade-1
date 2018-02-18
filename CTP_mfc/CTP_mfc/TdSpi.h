#ifndef TDSPI_H
#define TDSPI_H

#include "ThostFtdcTraderApi.h"
#include "ThostFtdcUserApiStruct.h"
using namespace std;
#define USER_ID ("035135");
#define PASS ("625117");
#define  BROKER ("9999)";
#define WM_MY_MESSAGE WM_USER+100 
#define WM_MY_count WM_USER+101 
#define WM_MY_bl WM_USER+102
#define DEBUG
class TdSpi :public CThostFtdcTraderSpi{
public:
	string tradingDate;
	//���캯��
	TdSpi(CThostFtdcTraderApi *tdapi);

	//���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	void OnFrontConnected();

	///��¼������Ӧ
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, 
			CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�ǳ�������Ӧ
	void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, 
			CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//�����ѯ������Ϣȷ����Ӧ
	void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm,
			CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	//�����ѯͶ���߽�������Ӧ
	void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo,
		CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	//Ͷ���߽�����ȷ����Ӧ
	void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm,
		CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	///�û��������������Ӧ
	void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, 
			CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ������Ӧ
	void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, 
		CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//�����ѯͶ���ֲ߳���Ӧ
	void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition,
		CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	///�����ѯ�ɽ���Ӧ
	void OnRspQryTrade(CThostFtdcTradeField *pTrade, 
				CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	//��ѯ�ʽ��ʻ���Ӧ
	void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount,
		CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
HWND mainh;
private:
	CThostFtdcTraderApi *tdapi;
	CThostFtdcReqUserLoginField *loginField;
	CThostFtdcReqAuthenticateField *authField;
	
	
};

#endif