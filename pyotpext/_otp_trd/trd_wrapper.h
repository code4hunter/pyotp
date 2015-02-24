#ifndef _trd_wrapper_h_
#define _trd_wrapper_h_

#include <Python.h>
#include <string>
#include "KSOTPTraderApi.h"

using namespace KingstarAPI;

class trd_imp : public CKSOTPTraderSpi
{
	PyObject * _spi;

public:
	trd_imp(PyObject * spi)
	{
		_spi = spi;
 		Py_INCREF(_spi);
	}

	~trd_imp()
	{
		Py_DECREF(_spi);
	}
	

	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷���������.
	virtual void OnFrontConnected(){};

	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷���������.
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	///        0x2004 �����������Ͽ�
	virtual void OnFrontDisconnected(int nReason){};

	///��¼������Ӧ
	virtual void OnRspUserLogin(CKSOTPRspUserLoginField *pRspUserLogin, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�ǳ�������Ӧ
	virtual void OnRspUserLogout(CKSOTPUserLogoutField *pUserLogout, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�û��������������Ӧ
	virtual void OnRspUserPasswordUpdate(CKSOTPUserPasswordUpdateField *pUserPasswordUpdate, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�ʽ��˻��������������Ӧ
	virtual void OnRspTradingAccountPasswordUpdate(CKSOTPTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����¼��������Ӧ
	virtual void OnRspOrderInsert(CKSOTPInputOrderField *pInputOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��������������Ӧ
	virtual void OnRspOrderAction(CKSOTPInputOrderActionField *pInputOrderAction, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ������Ӧ
	virtual void OnRspQryOrder(CKSOTPOrderField *pOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ�ɽ���Ӧ
	virtual void OnRspQryTrade(CKSOTPTradeField *pTrade, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯͶ���ֲ߳���Ӧ
	virtual void OnRspQryInvestorPosition(CKSOTPInvestorPositionField *pInvestorPosition, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ�ʽ��˻���Ӧ
	virtual void OnRspQryTradingAccount(CKSOTPTradingAccountField *pTradingAccount, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯͶ������Ӧ
	virtual void OnRspQryInvestor(CKSOTPInvestorField *pInvestor, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��Լ�˺���Ӧ
	virtual void OnRspQryTradingCode(CKSOTPTradingCodeField *pTradingCode, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��������Ӧ
	virtual void OnRspQryExchange(CKSOTPExchangeField *pExchange, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��Լ��Ӧ
	virtual void OnRspQryInstrument(CKSOTPInstrumentField *pInstrument, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯͶ���ֲ߳���ϸ��Ӧ
	virtual void OnRspQryInvestorPositionDetail(CKSOTPInvestorPositionDetailField *pInvestorPositionDetail, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ����֪ͨ��Ӧ
	virtual void OnRspQryTradingNotice(CKSOTPTradingNoticeField *pTradingNotice, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�ǽ��ױ���¼��������Ӧ
	virtual void OnRspNonTradingOrderInsert(CKSOTPInputNonTradingOrderField *pInputNonTradingOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�ǽ��ױ�������������Ӧ
	virtual void OnRspNonTradingOrderAction(CKSOTPInputNonTradingOrderActionField *pInputNonTradingOrderAction, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ�ǽ��ױ�����Ӧ
	virtual void OnRspQryNonTradingOrder(CKSOTPNonTradingOrderField *pNonTradingOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��ѯ�ǽ��ױ�����������Ӧ
	virtual void OnRspQryNonTradingOrderVolume(CKSOTPNonTradingOrderVolumeField *pNonTradingOrderVolume, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

	///�����ѯ���ȯ��Ϣ��Ӧ
	virtual void OnRspQryUnderlyingStockInfo(CKSOTPUnderlyingStockInfoField *pOTPUnderlyingStockInfo, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

	///��ѯ������Ȩ��������������Ӧ
	virtual void OnRspQryOTPInsCommRate(CKSOTPOTPInsCommRateField *pOTPInsCommRate, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

	///��ѯ������Ȩ��֤����������Ӧ
	virtual void OnRspQryOTPInsMarginRate(CKSOTPOTPInsMarginRateField *pOTPInsMarginRate, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

	///��ѯ������Ȩָ����Ϣ������Ӧ
	virtual void OnRspQryOTPAssignment(CKSOTPOTPAssignmentField *pOTPAssignment, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ������Ӧ
	virtual void OnRspQryDepthMarketData(CKSOTPDepthMarketDataField *pOTPDepthMarketData, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///���������ʽ�ת֤ȯӦ��
	virtual void OnRspFromBankToStockByStock(CKSOTPReqTransferField *pReqTransfer, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///֤ȯ���������ʽ�ת֤ȯ֪ͨ
	virtual void OnRtnFromBankToStockByStock(CKSOTPRspTransferField *pRspTransfer) {};

	///֤ȯ����֤ȯ�ʽ�ת����Ӧ��
	virtual void OnRspFromStockToBankByStock(CKSOTPReqTransferField *pReqTransfer, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///֤ȯ����֤ȯ�ʽ�ת����֪ͨ
	virtual void OnRtnFromStockToBankByStock(CKSOTPRspTransferField *pRspTransfer) {};

	///֤ȯ�����ѯ�������֪ͨ
	virtual void OnRtnQueryBankBalanceByStock(CKSOTPNotifyQueryAccountField *pNotifyQueryAccount) {};

	///�����ѯǩԼ������Ӧ
	virtual void OnRspQryContractBank(CKSOTPContractBankField *pContractBank, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///֤ȯ�����ѯ�������Ӧ��
	virtual void OnRspQueryBankAccountMoneyByStock(CKSOTPReqQueryAccountField *pReqQueryAccount, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯת����ˮ��Ӧ
	virtual void OnRspQryTransferSerial(CKSOTPTransferSerialField *pTransferSerial, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ������Ϣȷ����Ӧ
	virtual void OnRspQrySettlementInfoConfirm(CKSOTPSettlementInfoConfirmField *pSettlementInfoConfirm, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Ͷ���߽�����ȷ����Ӧ
	virtual void OnRspSettlementInfoConfirm(CKSOTPSettlementInfoConfirmField *pSettlementInfoConfirm, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯͶ���߽�������Ӧ
	virtual void OnRspQrySettlementInfo(CKSOTPSettlementInfoField *pSettlementInfo, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��ѯ�ͻ����׼�����Ӧ
	virtual void OnRspQryInvestorTradeLevel(CKSOTPInvestorTradeLevelField *pInvestorTradeLevel, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��ѯ�����޹������Ӧ
	virtual void OnRspQryPurchaseLimitAmt(CKSOTPPurchaseLimitAmtField *pPurchaseLimitAmt, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��ѯ�����޲ֶ����Ӧ
	virtual void OnRspQryPositionLimitVol(CKSOTPPositionLimitVolField *pPositionLimitVol, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��ʷ������Ӧ
	virtual void OnRspQryHistoryOrder(CKSOTPHistoryOrderField *pHistoryOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��ʷ�ɽ���Ӧ
	virtual void OnRspQryHistoryTrade(CKSOTPHistoryTradeField *pHistoryTrade, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��ʷ��Ȩָ����ϸ��Ӧ
	virtual int OnRspQryHistoryAssignment(CKSOTPHistoryAssignmentField *pHistoryAssignment, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��Ȩ������ϸ��Ӧ
	virtual int OnRspQryDelivDetail(CKSOTPDelivDetailField *pDelivDetail, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�Զ���Ȩִ�в�����Ӧ
	virtual int OnRspAutoExecOrderAction(CKSOTPAutoExecOrderActionField *pAutoExecOrderAction, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����Ӧ��
	virtual void OnRspError(CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����֪ͨ
	virtual void OnRtnOrder(CKSOTPOrderField *pOrder) {};

	///�ɽ�֪ͨ
	virtual void OnRtnTrade(CKSOTPTradeField *pTrade) {};

	///�ǽ��ױ���֪ͨ
	virtual void OnRtnNonTradingOrder(CKSOTPNonTradingOrderField *pNonTradingOrder) {};

	///��Լ����״̬֪ͨ
	virtual void OnRtnInstrumentStatus(CKSOTPInstrumentStatusField *pInstrumentStatus) {};

	///����֪ͨ
	virtual void OnRtnTradingNotice(CKSOTPTradingNoticeInfoField *pTradingNoticeInfo) {};
};

#endif