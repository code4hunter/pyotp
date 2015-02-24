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
	

	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用.
	virtual void OnFrontConnected(){};

	///当客户端与交易后台通信连接断开时，该方法被调用.
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	///        0x2004 服务器主动断开
	virtual void OnFrontDisconnected(int nReason){};

	///登录请求响应
	virtual void OnRspUserLogin(CKSOTPRspUserLoginField *pRspUserLogin, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///登出请求响应
	virtual void OnRspUserLogout(CKSOTPUserLogoutField *pUserLogout, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///用户口令更新请求响应
	virtual void OnRspUserPasswordUpdate(CKSOTPUserPasswordUpdateField *pUserPasswordUpdate, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///资金账户口令更新请求响应
	virtual void OnRspTradingAccountPasswordUpdate(CKSOTPTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单录入请求响应
	virtual void OnRspOrderInsert(CKSOTPInputOrderField *pInputOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单操作请求响应
	virtual void OnRspOrderAction(CKSOTPInputOrderActionField *pInputOrderAction, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询报单响应
	virtual void OnRspQryOrder(CKSOTPOrderField *pOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询成交响应
	virtual void OnRspQryTrade(CKSOTPTradeField *pTrade, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CKSOTPInvestorPositionField *pInvestorPosition, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询资金账户响应
	virtual void OnRspQryTradingAccount(CKSOTPTradingAccountField *pTradingAccount, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者响应
	virtual void OnRspQryInvestor(CKSOTPInvestorField *pInvestor, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询合约账号响应
	virtual void OnRspQryTradingCode(CKSOTPTradingCodeField *pTradingCode, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易所响应
	virtual void OnRspQryExchange(CKSOTPExchangeField *pExchange, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询合约响应
	virtual void OnRspQryInstrument(CKSOTPInstrumentField *pInstrument, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者持仓明细响应
	virtual void OnRspQryInvestorPositionDetail(CKSOTPInvestorPositionDetailField *pInvestorPositionDetail, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易通知响应
	virtual void OnRspQryTradingNotice(CKSOTPTradingNoticeField *pTradingNotice, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///非交易报单录入请求响应
	virtual void OnRspNonTradingOrderInsert(CKSOTPInputNonTradingOrderField *pInputNonTradingOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///非交易报单操作请求响应
	virtual void OnRspNonTradingOrderAction(CKSOTPInputNonTradingOrderActionField *pInputNonTradingOrderAction, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询非交易报单响应
	virtual void OnRspQryNonTradingOrder(CKSOTPNonTradingOrderField *pNonTradingOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///查询非交易报单量请求响应
	virtual void OnRspQryNonTradingOrderVolume(CKSOTPNonTradingOrderVolumeField *pNonTradingOrderVolume, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

	///请求查询标的券信息响应
	virtual void OnRspQryUnderlyingStockInfo(CKSOTPUnderlyingStockInfoField *pOTPUnderlyingStockInfo, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

	///查询个股期权手续费率请求响应
	virtual void OnRspQryOTPInsCommRate(CKSOTPOTPInsCommRateField *pOTPInsCommRate, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

	///查询个股期权保证金率请求响应
	virtual void OnRspQryOTPInsMarginRate(CKSOTPOTPInsMarginRateField *pOTPInsMarginRate, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

	///查询个股行权指派信息请求响应
	virtual void OnRspQryOTPAssignment(CKSOTPOTPAssignmentField *pOTPAssignment, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询行情响应
	virtual void OnRspQryDepthMarketData(CKSOTPDepthMarketDataField *pOTPDepthMarketData, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///发起银行资金转证券应答
	virtual void OnRspFromBankToStockByStock(CKSOTPReqTransferField *pReqTransfer, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///证券发起银行资金转证券通知
	virtual void OnRtnFromBankToStockByStock(CKSOTPRspTransferField *pRspTransfer) {};

	///证券发起证券资金转银行应答
	virtual void OnRspFromStockToBankByStock(CKSOTPReqTransferField *pReqTransfer, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///证券发起证券资金转银行通知
	virtual void OnRtnFromStockToBankByStock(CKSOTPRspTransferField *pRspTransfer) {};

	///证券发起查询银行余额通知
	virtual void OnRtnQueryBankBalanceByStock(CKSOTPNotifyQueryAccountField *pNotifyQueryAccount) {};

	///请求查询签约银行响应
	virtual void OnRspQryContractBank(CKSOTPContractBankField *pContractBank, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///证券发起查询银行余额应答
	virtual void OnRspQueryBankAccountMoneyByStock(CKSOTPReqQueryAccountField *pReqQueryAccount, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询转帐流水响应
	virtual void OnRspQryTransferSerial(CKSOTPTransferSerialField *pTransferSerial, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询结算信息确认响应
	virtual void OnRspQrySettlementInfoConfirm(CKSOTPSettlementInfoConfirmField *pSettlementInfoConfirm, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///投资者结算结果确认响应
	virtual void OnRspSettlementInfoConfirm(CKSOTPSettlementInfoConfirmField *pSettlementInfoConfirm, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者结算结果响应
	virtual void OnRspQrySettlementInfo(CKSOTPSettlementInfoField *pSettlementInfo, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///查询客户交易级别响应
	virtual void OnRspQryInvestorTradeLevel(CKSOTPInvestorTradeLevelField *pInvestorTradeLevel, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///查询个股限购额度响应
	virtual void OnRspQryPurchaseLimitAmt(CKSOTPPurchaseLimitAmtField *pPurchaseLimitAmt, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///查询个股限仓额度响应
	virtual void OnRspQryPositionLimitVol(CKSOTPPositionLimitVolField *pPositionLimitVol, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询历史报单响应
	virtual void OnRspQryHistoryOrder(CKSOTPHistoryOrderField *pHistoryOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询历史成交响应
	virtual void OnRspQryHistoryTrade(CKSOTPHistoryTradeField *pHistoryTrade, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询历史行权指派明细响应
	virtual int OnRspQryHistoryAssignment(CKSOTPHistoryAssignmentField *pHistoryAssignment, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询行权交割明细响应
	virtual int OnRspQryDelivDetail(CKSOTPDelivDetailField *pDelivDetail, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///自动行权执行操作响应
	virtual int OnRspAutoExecOrderAction(CKSOTPAutoExecOrderActionField *pAutoExecOrderAction, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///错误应答
	virtual void OnRspError(CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单通知
	virtual void OnRtnOrder(CKSOTPOrderField *pOrder) {};

	///成交通知
	virtual void OnRtnTrade(CKSOTPTradeField *pTrade) {};

	///非交易报单通知
	virtual void OnRtnNonTradingOrder(CKSOTPNonTradingOrderField *pNonTradingOrder) {};

	///合约交易状态通知
	virtual void OnRtnInstrumentStatus(CKSOTPInstrumentStatusField *pInstrumentStatus) {};

	///交易通知
	virtual void OnRtnTradingNotice(CKSOTPTradingNoticeInfoField *pTradingNoticeInfo) {};
};

#endif