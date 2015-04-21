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
	virtual void OnFrontConnected()
	{
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure();

		if (!PyObject_CallMethod(_spi, (char*)"OnFrontConnected", NULL))
		{
			PyErr_Print();
		}

		PyGILState_Release(gstate);
	};

	///当客户端与交易后台通信连接断开时，该方法被调用.
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	///        0x2004 服务器主动断开
	virtual void OnFrontDisconnected(int nReason)
	{
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure();

		std::string reason;
		switch (nReason)
		{
		case 0x1001:
		{
			reason = "Network read fault";
			break;
		}
		case 0x1002:
		{
			reason = "Network write fault";
			break;
		}
		case 0x2001:
		{
			reason = "Recevie heartbeat timeout";
			break;
		}
		case 0x2002:
		{
			reason = "Send heartbeat fault";
			break;
		}
		case 0x2003:
		{
			reason = "Receive data error";
			break;
		}
		}
		if (!PyObject_CallMethod(_spi, (char*)"OnFrontDisconnected", (char*)"is", nReason, reason.c_str()))
		{
			PyErr_Print();
		}

		PyGILState_Release(gstate);
	};

	///登录请求响应
	virtual void OnRspUserLogin(CKSOTPRspUserLoginField *pRspUserLogin, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure();

		PyObject *dict = PyDict_New();
		PyDict_SetItemString(dict, "BrokerID", Py_BuildValue("s", pRspUserLogin->BrokerID));
		PyDict_SetItemString(dict, "TradingDay", Py_BuildValue("s", pRspUserLogin->TradingDay));
		PyDict_SetItemString(dict, "LoginTime", Py_BuildValue("s", pRspUserLogin->LoginTime));
		PyDict_SetItemString(dict, "UserID", Py_BuildValue("s", pRspUserLogin->UserID));
		PyDict_SetItemString(dict, "SystemName", Py_BuildValue("s", pRspUserLogin->SystemName));
		PyDict_SetItemString(dict, "FrontID", Py_BuildValue("i", pRspUserLogin->FrontID));
		PyDict_SetItemString(dict, "SessionID", Py_BuildValue("i", pRspUserLogin->SessionID));
		PyDict_SetItemString(dict, "MaxOrderRef", Py_BuildValue("s", pRspUserLogin->MaxOrderRef));
		PyDict_SetItemString(dict, "SSETime", Py_BuildValue("s", pRspUserLogin->SSETime));

		if (!PyObject_CallMethod(_spi, (char*)"OnRspUserLogin", (char*)"Nisib", dict,
			pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast))
		{
			PyErr_Print();
		}
		Py_XDECREF(dict);

		PyGILState_Release(gstate);
	};

	///登出请求响应
	virtual void OnRspUserLogout(CKSOTPUserLogoutField *pUserLogout, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure();

		PyObject *dict = PyDict_New();
		PyDict_SetItemString(dict, "BrokerID", Py_BuildValue("s", pUserLogout->BrokerID));
		PyDict_SetItemString(dict, "UserID", Py_BuildValue("s", pUserLogout->UserID));

		if (!PyObject_CallMethod(_spi, (char*)"OnRspUserLogout", (char*)"Nisib",
			pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast))
		{
			PyErr_Print();
		}
		Py_XDECREF(dict);

		PyGILState_Release(gstate);
	};

	///报单录入请求响应
	virtual void OnRspOrderInsert(CKSOTPInputOrderField *pInputOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure();

		PyObject *dict = PyDict_New();
		PyDict_SetItemString(dict, "BrokerID", Py_BuildValue("s", pInputOrder->BrokerID));
		PyDict_SetItemString(dict, "InvestorID", Py_BuildValue("s", pInputOrder->InvestorID));
		PyDict_SetItemString(dict, "InstrumentID", Py_BuildValue("s", pInputOrder->InstrumentID));
		PyDict_SetItemString(dict, "OrderRef", Py_BuildValue("s", pInputOrder->OrderRef));
		PyDict_SetItemString(dict, "UserID", Py_BuildValue("s", pInputOrder->UserID));
		PyDict_SetItemString(dict, "OrderPriceType", Py_BuildValue("c", pInputOrder->OrderPriceType));
		PyDict_SetItemString(dict, "Direction", Py_BuildValue("c", pInputOrder->Direction));
		PyDict_SetItemString(dict, "OffsetFlag", Py_BuildValue("c", pInputOrder->OffsetFlag));
		PyDict_SetItemString(dict, "HedgeFlag", Py_BuildValue("c", pInputOrder->HedgeFlag));
		PyDict_SetItemString(dict, "LimitPrice", Py_BuildValue("f", pInputOrder->LimitPrice));
		PyDict_SetItemString(dict, "VolumeTotalOriginal", Py_BuildValue("i", pInputOrder->VolumeTotalOriginal));
		PyDict_SetItemString(dict, "TimeCondition", Py_BuildValue("c", pInputOrder->TimeCondition));
		PyDict_SetItemString(dict, "GTDDate", Py_BuildValue("s", pInputOrder->GTDDate));
		PyDict_SetItemString(dict, "VolumeCondition", Py_BuildValue("c", pInputOrder->VolumeCondition));
		PyDict_SetItemString(dict, "MinVolume", Py_BuildValue("i", pInputOrder->MinVolume));
		PyDict_SetItemString(dict, "ContingentCondition", Py_BuildValue("c", pInputOrder->ContingentCondition));
		PyDict_SetItemString(dict, "StopPrice", Py_BuildValue("f", pInputOrder->StopPrice));
		PyDict_SetItemString(dict, "BusinessUnit", Py_BuildValue("s", pInputOrder->BusinessUnit));
		PyDict_SetItemString(dict, "RequestID", Py_BuildValue("i", pInputOrder->RequestID));

		if (!PyObject_CallMethod(_spi, (char*)"OnRspOrderInsert", (char*)"Nisib", dict,
			pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast))
		{
			PyErr_Print();
		}
		Py_XDECREF(dict);

		PyGILState_Release(gstate);
	};

	///报单操作请求响应
	virtual void OnRspOrderAction(CKSOTPInputOrderActionField *pInputOrderAction, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure();

		PyObject *dict = PyDict_New();
		PyDict_SetItemString(dict, "InvestorID", Py_BuildValue("s", pInputOrderAction->InvestorID));
		PyDict_SetItemString(dict, "OrderRef", Py_BuildValue("s", pInputOrderAction->OrderRef));
		PyDict_SetItemString(dict, "RequestID", Py_BuildValue("i", pInputOrderAction->RequestID));
		PyDict_SetItemString(dict, "FrontID", Py_BuildValue("i", pInputOrderAction->FrontID));
		PyDict_SetItemString(dict, "SessionID", Py_BuildValue("i", pInputOrderAction->SessionID));
		PyDict_SetItemString(dict, "ExchangeID", Py_BuildValue("s", pInputOrderAction->ExchangeID));
		PyDict_SetItemString(dict, "OrderSysID", Py_BuildValue("s", pInputOrderAction->OrderSysID));
		PyDict_SetItemString(dict, "ActionFlag", Py_BuildValue("c", pInputOrderAction->ActionFlag));
		PyDict_SetItemString(dict, "LimitPrice", Py_BuildValue("f", pInputOrderAction->LimitPrice));
		PyDict_SetItemString(dict, "VolumeChange", Py_BuildValue("i", pInputOrderAction->VolumeChange));
		PyDict_SetItemString(dict, "UserID", Py_BuildValue("s", pInputOrderAction->UserID));
		PyDict_SetItemString(dict, "InstrumentID", Py_BuildValue("s", pInputOrderAction->InstrumentID));

		if (!PyObject_CallMethod(_spi, (char*)"OnRspOrderAction", (char*)"Nisib", dict,
			pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast))
		{
			PyErr_Print();
		}
		Py_XDECREF(dict);

		PyGILState_Release(gstate);
	};

	///请求查询报单响应
	virtual void OnRspQryOrder(CKSOTPOrderField *pOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure();

		PyObject *dict = PyDict_New();
		PyDict_SetItemString(dict, "BrokerID", Py_BuildValue("s", pOrder->BrokerID));
		PyDict_SetItemString(dict, "InvestorID", Py_BuildValue("s", pOrder->InvestorID));
		PyDict_SetItemString(dict, "InstrumentID", Py_BuildValue("s", pOrder->InstrumentID));
		PyDict_SetItemString(dict, "OrderRef", Py_BuildValue("s", pOrder->OrderRef));
		PyDict_SetItemString(dict, "UserID", Py_BuildValue("s", pOrder->UserID));
		PyDict_SetItemString(dict, "OrderPriceType", Py_BuildValue("c", pOrder->OrderPriceType));
		PyDict_SetItemString(dict, "Direction", Py_BuildValue("c", pOrder->Direction));
		PyDict_SetItemString(dict, "OffsetFlag", Py_BuildValue("c", pOrder->OffsetFlag));
		PyDict_SetItemString(dict, "LimitPrice", Py_BuildValue("f", pOrder->LimitPrice));
		PyDict_SetItemString(dict, "HedgeFlag", Py_BuildValue("c", pOrder->HedgeFlag));
		PyDict_SetItemString(dict, "VolumeTotalOriginal", Py_BuildValue("i", pOrder->VolumeTotalOriginal));
		PyDict_SetItemString(dict, "TimeCondition", Py_BuildValue("c", pOrder->TimeCondition));
		PyDict_SetItemString(dict, "GTDDate", Py_BuildValue("s", pOrder->GTDDate));
		PyDict_SetItemString(dict, "VolumeCondition", Py_BuildValue("c", pOrder->VolumeCondition));
		PyDict_SetItemString(dict, "MinVolume", Py_BuildValue("i", pOrder->MinVolume));
		PyDict_SetItemString(dict, "ContingentCondition", Py_BuildValue("c", pOrder->ContingentCondition));
		PyDict_SetItemString(dict, "StopPrice", Py_BuildValue("f", pOrder->StopPrice));
		PyDict_SetItemString(dict, "ForceCloseReason", Py_BuildValue("c", pOrder->ForceCloseReason));
		PyDict_SetItemString(dict, "BusinessUnit", Py_BuildValue("s", pOrder->BusinessUnit));
		PyDict_SetItemString(dict, "RequestID", Py_BuildValue("i", pOrder->RequestID));
		PyDict_SetItemString(dict, "OrderLocalID", Py_BuildValue("s", pOrder->OrderLocalID));
		PyDict_SetItemString(dict, "ExchangeID", Py_BuildValue("s", pOrder->ExchangeID));
		PyDict_SetItemString(dict, "ParticipantID", Py_BuildValue("s", pOrder->ParticipantID));
		PyDict_SetItemString(dict, "ClientID", Py_BuildValue("s", pOrder->ClientID));
		PyDict_SetItemString(dict, "ExchangeInstID", Py_BuildValue("s", pOrder->ExchangeInstID));
		PyDict_SetItemString(dict, "TraderID", Py_BuildValue("s", pOrder->TraderID));
		PyDict_SetItemString(dict, "OrderSubmitStatus", Py_BuildValue("c", pOrder->OrderSubmitStatus));
		PyDict_SetItemString(dict, "NotifySequence", Py_BuildValue("i", pOrder->NotifySequence));
		PyDict_SetItemString(dict, "TradingDay", Py_BuildValue("s", pOrder->TradingDay));
		PyDict_SetItemString(dict, "SettlementID", Py_BuildValue("i", pOrder->SettlementID));
		PyDict_SetItemString(dict, "OrderSysID", Py_BuildValue("s", pOrder->OrderSysID));
		PyDict_SetItemString(dict, "OrderSource", Py_BuildValue("i", pOrder->OrderSource));
		PyDict_SetItemString(dict, "OrderStatus", Py_BuildValue("c", pOrder->OrderStatus));
		PyDict_SetItemString(dict, "OrderType", Py_BuildValue("c", pOrder->OrderType));
		PyDict_SetItemString(dict, "VolumeTraded", Py_BuildValue("i", pOrder->VolumeTraded));
		PyDict_SetItemString(dict, "VolumeTotal", Py_BuildValue("i", pOrder->VolumeTotal));
		PyDict_SetItemString(dict, "InsertDate", Py_BuildValue("s", pOrder->InsertDate));
		PyDict_SetItemString(dict, "InsertTime", Py_BuildValue("s", pOrder->InsertTime));
		PyDict_SetItemString(dict, "ActiveTime", Py_BuildValue("s", pOrder->ActiveTime));
		PyDict_SetItemString(dict, "UpdateTime", Py_BuildValue("s", pOrder->UpdateTime));
		PyDict_SetItemString(dict, "CancelTime", Py_BuildValue("s", pOrder->CancelTime));
		PyDict_SetItemString(dict, "SequenceNo", Py_BuildValue("i", pOrder->SequenceNo));
		PyDict_SetItemString(dict, "FrontID", Py_BuildValue("i", pOrder->FrontID));
		PyDict_SetItemString(dict, "SessionID", Py_BuildValue("i", pOrder->SessionID));
		PyDict_SetItemString(dict, "UserProductInfo", Py_BuildValue("s", pOrder->UserProductInfo));
		PyDict_SetItemString(dict, "StatusMsg", Py_BuildValue("s", pOrder->StatusMsg));
		PyDict_SetItemString(dict, "UserForceClose", Py_BuildValue("i", pOrder->UserForceClose));
		PyDict_SetItemString(dict, "ActiveUserID", Py_BuildValue("s", pOrder->ActiveUserID));
		PyDict_SetItemString(dict, "BrokerOrderSeq", Py_BuildValue("i", pOrder->BrokerOrderSeq));

		if (!PyObject_CallMethod(_spi, (char*)"OnRspQryOrder", (char*)"Nisib", dict,
			pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast))
		{
			PyErr_Print();
		}
		Py_XDECREF(dict);

		PyGILState_Release(gstate);
	};

	///请求查询成交响应
	virtual void OnRspQryTrade(CKSOTPTradeField *pTrade, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure();

		PyObject *dict = PyDict_New();
		PyDict_SetItemString(dict, "BrokerID", Py_BuildValue("s", pTrade->BrokerID));
		PyDict_SetItemString(dict, "InvestorID", Py_BuildValue("s", pTrade->InvestorID));
		PyDict_SetItemString(dict, "InstrumentID", Py_BuildValue("s", pTrade->InstrumentID));
		PyDict_SetItemString(dict, "OrderRef", Py_BuildValue("s", pTrade->OrderRef));
		PyDict_SetItemString(dict, "UserID", Py_BuildValue("s", pTrade->UserID));
		PyDict_SetItemString(dict, "ExchangeID", Py_BuildValue("s", pTrade->ExchangeID));
		PyDict_SetItemString(dict, "TradeID", Py_BuildValue("s", pTrade->TradeID));
		PyDict_SetItemString(dict, "Direction", Py_BuildValue("c", pTrade->Direction));
		PyDict_SetItemString(dict, "OrderSysID", Py_BuildValue("s", pTrade->OrderSysID));
		PyDict_SetItemString(dict, "ParticipantID", Py_BuildValue("s", pTrade->ParticipantID));
		PyDict_SetItemString(dict, "ClientID", Py_BuildValue("s", pTrade->ClientID));
		PyDict_SetItemString(dict, "TradingRole", Py_BuildValue("c", pTrade->TradingRole));
		PyDict_SetItemString(dict, "ExchangeInstID", Py_BuildValue("s", pTrade->ExchangeInstID));
		PyDict_SetItemString(dict, "OffsetFlag", Py_BuildValue("c", pTrade->OffsetFlag));
		PyDict_SetItemString(dict, "HedgeFlag", Py_BuildValue("c", pTrade->HedgeFlag));
		PyDict_SetItemString(dict, "Price", Py_BuildValue("f", pTrade->Price));
		PyDict_SetItemString(dict, "Volume", Py_BuildValue("i", pTrade->Volume));
		PyDict_SetItemString(dict, "TradeDate", Py_BuildValue("s", pTrade->TradeDate));
		PyDict_SetItemString(dict, "TradeTime", Py_BuildValue("s", pTrade->TradeTime));
		PyDict_SetItemString(dict, "TradeType", Py_BuildValue("c", pTrade->TradeType));
		PyDict_SetItemString(dict, "PriceSource", Py_BuildValue("c", pTrade->PriceSource));
		PyDict_SetItemString(dict, "TraderID", Py_BuildValue("s", pTrade->TraderID));
		PyDict_SetItemString(dict, "OrderLocalID", Py_BuildValue("s", pTrade->OrderLocalID));
		PyDict_SetItemString(dict, "ClearingPartID", Py_BuildValue("s", pTrade->ClearingPartID));
		PyDict_SetItemString(dict, "BusinessUnit", Py_BuildValue("s", pTrade->BusinessUnit));
		PyDict_SetItemString(dict, "SequenceNo", Py_BuildValue("i", pTrade->SequenceNo));
		PyDict_SetItemString(dict, "TradingDay", Py_BuildValue("s", pTrade->TradingDay));
		PyDict_SetItemString(dict, "BrokerOrderSeq", Py_BuildValue("i", pTrade->BrokerOrderSeq));
		PyDict_SetItemString(dict, "TradeSource", Py_BuildValue("c", pTrade->TradeSource));
		if (!PyObject_CallMethod(_spi, (char*)"OnRspQryTrade", (char*)"Nisib", dict,
			pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast))
		{
			PyErr_Print();
		}
		Py_XDECREF(dict);

		PyGILState_Release(gstate);
	};

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CKSOTPInvestorPositionField *pInvestorPosition, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure();

		PyObject *dict = PyDict_New();
		PyDict_SetItemString(dict, "InstrumentID", Py_BuildValue("s", pInvestorPosition->InstrumentID));
		PyDict_SetItemString(dict, "BrokerID", Py_BuildValue("s", pInvestorPosition->BrokerID));
		PyDict_SetItemString(dict, "InvestorID", Py_BuildValue("s", pInvestorPosition->InvestorID));
		PyDict_SetItemString(dict, "PosiDirection", Py_BuildValue("c", pInvestorPosition->PosiDirection));
		PyDict_SetItemString(dict, "HedgeFlag", Py_BuildValue("c", pInvestorPosition->HedgeFlag));
		PyDict_SetItemString(dict, "PositionDate", Py_BuildValue("s", pInvestorPosition->PositionDate));
		PyDict_SetItemString(dict, "YdPosition", Py_BuildValue("i", pInvestorPosition->YdPosition));
		PyDict_SetItemString(dict, "Position", Py_BuildValue("i", pInvestorPosition->Position));
		PyDict_SetItemString(dict, "LongFrozen", Py_BuildValue("i", pInvestorPosition->LongFrozen));
		PyDict_SetItemString(dict, "ShortFrozen", Py_BuildValue("i", pInvestorPosition->ShortFrozen));
		PyDict_SetItemString(dict, "LongFrozenAmount", Py_BuildValue("f", pInvestorPosition->LongFrozenAmount));
		PyDict_SetItemString(dict, "ShortFrozenAmount", Py_BuildValue("f", pInvestorPosition->ShortFrozenAmount));
		PyDict_SetItemString(dict, "OpenVolume", Py_BuildValue("i", pInvestorPosition->OpenVolume));
		PyDict_SetItemString(dict, "OpenAmount", Py_BuildValue("f", pInvestorPosition->OpenAmount));
		PyDict_SetItemString(dict, "CloseAmount", Py_BuildValue("f", pInvestorPosition->CloseAmount));
		PyDict_SetItemString(dict, "PositionCost", Py_BuildValue("f", pInvestorPosition->PositionCost));
		PyDict_SetItemString(dict, "UseMargin", Py_BuildValue("f", pInvestorPosition->UseMargin));
		PyDict_SetItemString(dict, "FrozenMargin", Py_BuildValue("f", pInvestorPosition->FrozenMargin));
		PyDict_SetItemString(dict, "FrozenCash", Py_BuildValue("f", pInvestorPosition->FrozenCash));
		PyDict_SetItemString(dict, "FrozenCommission", Py_BuildValue("f", pInvestorPosition->FrozenCommission));
		PyDict_SetItemString(dict, "CashIn", Py_BuildValue("f", pInvestorPosition->CashIn));
		PyDict_SetItemString(dict, "Commission", Py_BuildValue("f", pInvestorPosition->Commission));
		PyDict_SetItemString(dict, "CloseProfit", Py_BuildValue("f", pInvestorPosition->CloseProfit));
		PyDict_SetItemString(dict, "PositionProfit", Py_BuildValue("f", pInvestorPosition->PositionProfit));
		PyDict_SetItemString(dict, "PreSettlementPrice", Py_BuildValue("f", pInvestorPosition->PreSettlementPrice));
		PyDict_SetItemString(dict, "SettlementPrice", Py_BuildValue("f", pInvestorPosition->SettlementPrice));
		PyDict_SetItemString(dict, "TradingDay", Py_BuildValue("s", pInvestorPosition->TradingDay));
		PyDict_SetItemString(dict, "SettlementID", Py_BuildValue("i", pInvestorPosition->SettlementID));
		PyDict_SetItemString(dict, "OpenCost", Py_BuildValue("f", pInvestorPosition->OpenCost));
		PyDict_SetItemString(dict, "ExchangeMargin", Py_BuildValue("f", pInvestorPosition->ExchangeMargin));
		PyDict_SetItemString(dict, "CloseProfitByDate", Py_BuildValue("f", pInvestorPosition->CloseProfitByDate));
		PyDict_SetItemString(dict, "TodayPosition", Py_BuildValue("i", pInvestorPosition->TodayPosition));
		PyDict_SetItemString(dict, "MarginRateByMoney", Py_BuildValue("f", pInvestorPosition->MarginRateByMoney));
		PyDict_SetItemString(dict, "MarginRateByVolume", Py_BuildValue("f", pInvestorPosition->MarginRateByVolume));
		PyDict_SetItemString(dict, "StrikeFrozen", Py_BuildValue("i", pInvestorPosition->StrikeFrozen));
		PyDict_SetItemString(dict, "StrikeFrozenAmount", Py_BuildValue("f", pInvestorPosition->StrikeFrozenAmount));

		if (!PyObject_CallMethod(_spi, (char*)"OnRspQryInvestorPosition", (char*)"Nisib", dict,
			pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast))
		{
			PyErr_Print();
		}
		Py_XDECREF(dict);

		PyGILState_Release(gstate);
	};

	///请求查询资金账户响应
	virtual void OnRspQryTradingAccount(CKSOTPTradingAccountField *pTradingAccount, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure();

		PyObject *dict = PyDict_New();
		PyDict_SetItemString(dict, "BrokerID", Py_BuildValue("s", pTradingAccount->BrokerID));
		PyDict_SetItemString(dict, "AccountID", Py_BuildValue("s", pTradingAccount->AccountID));
		PyDict_SetItemString(dict, "PreBalance", Py_BuildValue("f", pTradingAccount->PreBalance));
		PyDict_SetItemString(dict, "PreMargin", Py_BuildValue("f", pTradingAccount->PreMargin));
		PyDict_SetItemString(dict, "Deposit", Py_BuildValue("f", pTradingAccount->Deposit));
		PyDict_SetItemString(dict, "Withdraw", Py_BuildValue("f", pTradingAccount->Withdraw));
		PyDict_SetItemString(dict, "FrozenMargin", Py_BuildValue("f", pTradingAccount->FrozenMargin));
		PyDict_SetItemString(dict, "FrozenCash", Py_BuildValue("f", pTradingAccount->FrozenCash));
		PyDict_SetItemString(dict, "FrozenCommission", Py_BuildValue("f", pTradingAccount->FrozenCommission));
		PyDict_SetItemString(dict, "CurrMargin", Py_BuildValue("f", pTradingAccount->CurrMargin));
		PyDict_SetItemString(dict, "CashIn", Py_BuildValue("f", pTradingAccount->CashIn));
		PyDict_SetItemString(dict, "Commission", Py_BuildValue("f", pTradingAccount->Commission));
		PyDict_SetItemString(dict, "CloseProfit", Py_BuildValue("f", pTradingAccount->CloseProfit));
		PyDict_SetItemString(dict, "PositionProfit", Py_BuildValue("f", pTradingAccount->PositionProfit));
		PyDict_SetItemString(dict, "Balance", Py_BuildValue("f", pTradingAccount->Balance));
		PyDict_SetItemString(dict, "Available", Py_BuildValue("f", pTradingAccount->Available));
		PyDict_SetItemString(dict, "WithdrawQuota", Py_BuildValue("f", pTradingAccount->WithdrawQuota));
		PyDict_SetItemString(dict, "Reserve", Py_BuildValue("f", pTradingAccount->Reserve));
		PyDict_SetItemString(dict, "TradingDay", Py_BuildValue("s", pTradingAccount->TradingDay));
		PyDict_SetItemString(dict, "SettlementID", Py_BuildValue("i", pTradingAccount->SettlementID));
		PyDict_SetItemString(dict, "Credit", Py_BuildValue("f", pTradingAccount->Credit));
		PyDict_SetItemString(dict, "Mortgage", Py_BuildValue("f", pTradingAccount->Mortgage));
		PyDict_SetItemString(dict, "ExchangeMargin", Py_BuildValue("f", pTradingAccount->ExchangeMargin));
		PyDict_SetItemString(dict, "DeliveryMargin", Py_BuildValue("f", pTradingAccount->DeliveryMargin));
		PyDict_SetItemString(dict, "ExchangeDeliveryMargin", Py_BuildValue("f", pTradingAccount->ExchangeDeliveryMargin));

		if (!PyObject_CallMethod(_spi, (char*)"OnRspQryTradingAccount", (char*)"Nisib", dict,
			pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast))
		{
			PyErr_Print();
		}
		Py_XDECREF(dict);

		PyGILState_Release(gstate);
	};

	///请求查询投资者响应
	virtual void OnRspQryInvestor(CKSOTPInvestorField *pInvestor, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure();

		PyObject *dict = PyDict_New();
		PyDict_SetItemString(dict, "InvestorID", Py_BuildValue("s", pInvestor->InvestorID));
		PyDict_SetItemString(dict, "BrokerID", Py_BuildValue("s", pInvestor->BrokerID));
		PyDict_SetItemString(dict, "InvestorName", Py_BuildValue("s", pInvestor->InvestorName));
		PyDict_SetItemString(dict, "IdentifiedCardType", Py_BuildValue("c", pInvestor->IdentifiedCardType));
		PyDict_SetItemString(dict, "IdentifiedCardNo", Py_BuildValue("s", pInvestor->IdentifiedCardNo));
		PyDict_SetItemString(dict, "IsActive", Py_BuildValue("i", pInvestor->IsActive));
		PyDict_SetItemString(dict, "Telephone", Py_BuildValue("s", pInvestor->Telephone));
		PyDict_SetItemString(dict, "Address", Py_BuildValue("s", pInvestor->Address));
		PyDict_SetItemString(dict, "OpenDate", Py_BuildValue("s", pInvestor->OpenDate));
		PyDict_SetItemString(dict, "Mobile", Py_BuildValue("s", pInvestor->Mobile));

		if (!PyObject_CallMethod(_spi, (char*)"OnRspQryInvestor", (char*)"Nisib", dict,
			pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast))
		{
			PyErr_Print();
		}
		Py_XDECREF(dict);

		PyGILState_Release(gstate);
	};

	///请求查询合约响应
	virtual void OnRspQryInstrument(CKSOTPInstrumentField *pInstrument, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure();

		PyObject *dict = PyDict_New();
		PyDict_SetItemString(dict, "InstrumentID", Py_BuildValue("s", pInstrument->InstrumentID));
		PyDict_SetItemString(dict, "ExchangeID", Py_BuildValue("s", pInstrument->ExchangeID));
		PyDict_SetItemString(dict, "InstrumentName", Py_BuildValue("s", pInstrument->InstrumentName));
		PyDict_SetItemString(dict, "ExchangeInstID", Py_BuildValue("s", pInstrument->ExchangeInstID));
		PyDict_SetItemString(dict, "ProductID", Py_BuildValue("s", pInstrument->ProductID));
		PyDict_SetItemString(dict, "ProductClass", Py_BuildValue("c", pInstrument->ProductClass));
		PyDict_SetItemString(dict, "DeliveryYear", Py_BuildValue("i", pInstrument->DeliveryYear));
		PyDict_SetItemString(dict, "DeliveryMonth", Py_BuildValue("i", pInstrument->DeliveryMonth));
		PyDict_SetItemString(dict, "MaxMarketOrderVolume", Py_BuildValue("i", pInstrument->MaxMarketOrderVolume));
		PyDict_SetItemString(dict, "MinMarketOrderVolume", Py_BuildValue("i", pInstrument->MinMarketOrderVolume));
		PyDict_SetItemString(dict, "MaxLimitOrderVolume", Py_BuildValue("i", pInstrument->MaxLimitOrderVolume));
		PyDict_SetItemString(dict, "MinLimitOrderVolume", Py_BuildValue("i", pInstrument->MinLimitOrderVolume));
		PyDict_SetItemString(dict, "VolumeMultiple", Py_BuildValue("i", pInstrument->VolumeMultiple));
		PyDict_SetItemString(dict, "PriceTick", Py_BuildValue("f", pInstrument->PriceTick));
		PyDict_SetItemString(dict, "CreateDate", Py_BuildValue("s", pInstrument->CreateDate));
		PyDict_SetItemString(dict, "OpenDate", Py_BuildValue("s", pInstrument->OpenDate));
		PyDict_SetItemString(dict, "ExpireDate", Py_BuildValue("s", pInstrument->ExpireDate));
		PyDict_SetItemString(dict, "StartDelivDate", Py_BuildValue("s", pInstrument->StartDelivDate));
		PyDict_SetItemString(dict, "EndDelivDate", Py_BuildValue("s", pInstrument->EndDelivDate));
		PyDict_SetItemString(dict, "InstLifePhase", Py_BuildValue("c", pInstrument->InstLifePhase));
		PyDict_SetItemString(dict, "IsTrading", Py_BuildValue("i", pInstrument->IsTrading));
		PyDict_SetItemString(dict, "PositionType", Py_BuildValue("c", pInstrument->PositionType));
		PyDict_SetItemString(dict, "PositionDateType", Py_BuildValue("c", pInstrument->PositionDateType));
		PyDict_SetItemString(dict, "LongMarginRatio", Py_BuildValue("f", pInstrument->LongMarginRatio));
		PyDict_SetItemString(dict, "ShortMarginRatio", Py_BuildValue("f", pInstrument->ShortMarginRatio));
		PyDict_SetItemString(dict, "UnderlyingInstrID", Py_BuildValue("s", pInstrument->UnderlyingInstrID));
		PyDict_SetItemString(dict, "StrikePrice", Py_BuildValue("f", pInstrument->StrikePrice));
		PyDict_SetItemString(dict, "OptionsType", Py_BuildValue("c", pInstrument->OptionsType));
		PyDict_SetItemString(dict, "InstrumentIdSerial", Py_BuildValue("s", pInstrument->InstrumentIdSerial));

		if (!PyObject_CallMethod(_spi, (char*)"OnRspQryInstrument", (char*)"Nisib", dict,
			pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast))
		{
			PyErr_Print();
		}
		Py_XDECREF(dict);

		PyGILState_Release(gstate);
	};

	///请求查询投资者持仓明细响应
	virtual void OnRspQryInvestorPositionDetail(CKSOTPInvestorPositionDetailField *pInvestorPositionDetail, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure();

		PyObject *dict = PyDict_New();
		PyDict_SetItemString(dict, "InstrumentID", Py_BuildValue("s", pInvestorPositionDetail->InstrumentID));
		PyDict_SetItemString(dict, "BrokerID", Py_BuildValue("s", pInvestorPositionDetail->BrokerID));
		PyDict_SetItemString(dict, "InvestorID", Py_BuildValue("s", pInvestorPositionDetail->InvestorID));
		PyDict_SetItemString(dict, "HedgeFlag", Py_BuildValue("c", pInvestorPositionDetail->HedgeFlag));
		PyDict_SetItemString(dict, "Direction", Py_BuildValue("c", pInvestorPositionDetail->Direction));
		PyDict_SetItemString(dict, "OpenDate", Py_BuildValue("s", pInvestorPositionDetail->OpenDate));
		PyDict_SetItemString(dict, "TradeID", Py_BuildValue("s", pInvestorPositionDetail->TradeID));
		PyDict_SetItemString(dict, "Volume", Py_BuildValue("i", pInvestorPositionDetail->Volume));
		PyDict_SetItemString(dict, "OpenPrice", Py_BuildValue("f", pInvestorPositionDetail->OpenPrice));
		PyDict_SetItemString(dict, "TradingDay", Py_BuildValue("s", pInvestorPositionDetail->TradingDay));
		PyDict_SetItemString(dict, "SettlementID", Py_BuildValue("i", pInvestorPositionDetail->SettlementID));
		PyDict_SetItemString(dict, "TradeType", Py_BuildValue("c", pInvestorPositionDetail->TradeType));
		PyDict_SetItemString(dict, "ExchangeID", Py_BuildValue("s", pInvestorPositionDetail->ExchangeID));
		PyDict_SetItemString(dict, "CloseProfitByDate", Py_BuildValue("f", pInvestorPositionDetail->CloseProfitByDate));
		PyDict_SetItemString(dict, "CloseProfitByTrade", Py_BuildValue("f", pInvestorPositionDetail->CloseProfitByTrade));
		PyDict_SetItemString(dict, "PositionProfitByDate", Py_BuildValue("f", pInvestorPositionDetail->PositionProfitByDate));
		PyDict_SetItemString(dict, "PositionProfitByTrade", Py_BuildValue("f", pInvestorPositionDetail->PositionProfitByTrade));
		PyDict_SetItemString(dict, "Margin", Py_BuildValue("f", pInvestorPositionDetail->Margin));
		PyDict_SetItemString(dict, "ExchMargin", Py_BuildValue("f", pInvestorPositionDetail->ExchMargin));
		PyDict_SetItemString(dict, "MarginRateByMoney", Py_BuildValue("f", pInvestorPositionDetail->MarginRateByMoney));
		PyDict_SetItemString(dict, "MarginRateByVolume", Py_BuildValue("f", pInvestorPositionDetail->MarginRateByVolume));
		PyDict_SetItemString(dict, "LastSettlementPrice", Py_BuildValue("f", pInvestorPositionDetail->LastSettlementPrice));
		PyDict_SetItemString(dict, "SettlementPrice", Py_BuildValue("f", pInvestorPositionDetail->SettlementPrice));
		PyDict_SetItemString(dict, "BrokerID", Py_BuildValue("s", pInvestorPositionDetail->BrokerID));
		PyDict_SetItemString(dict, "BrokerID", Py_BuildValue("s", pInvestorPositionDetail->BrokerID));
		PyDict_SetItemString(dict, "BrokerID", Py_BuildValue("s", pInvestorPositionDetail->BrokerID));
		PyDict_SetItemString(dict, "BrokerID", Py_BuildValue("s", pInvestorPositionDetail->BrokerID));

		if (!PyObject_CallMethod(_spi, (char*)"OnRspQryInvestorPositionDetail", (char*)"Nisib", dict,
			pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast))
		{
			PyErr_Print();
		}
		Py_XDECREF(dict);

		PyGILState_Release(gstate);
	};

	///查询客户交易级别响应
	virtual void OnRspQryInvestorTradeLevel(CKSOTPInvestorTradeLevelField *pInvestorTradeLevel, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
	{
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure();

		PyObject *dict = PyDict_New();
		PyDict_SetItemString(dict, "BrokerID", Py_BuildValue("s", pInvestorTradeLevel->BrokerID));
		PyDict_SetItemString(dict, "InvestorID", Py_BuildValue("s", pInvestorTradeLevel->InvestorID));
		PyDict_SetItemString(dict, "ExchangeID", Py_BuildValue("s", pInvestorTradeLevel->ExchangeID));
		PyDict_SetItemString(dict, "ProductID", Py_BuildValue("s", pInvestorTradeLevel->ProductID));
		PyDict_SetItemString(dict, "TradeLevel", Py_BuildValue("c", pInvestorTradeLevel->TradeLevel));

		if (!PyObject_CallMethod(_spi, (char*)"OnRspQryInvestorTradeLevel", (char*)"Nisib", dict,
			pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast))
		{
			PyErr_Print();
		}
		Py_XDECREF(dict);

		PyGILState_Release(gstate);
	};

	///错误应答
	virtual void OnRspError(CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure();

		if (!PyObject_CallMethod(_spi, (char*)"OnRspError", (char*)"isib",
			pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast))
		{
			PyErr_Print();
		}

		PyGILState_Release(gstate);
	};

	///报单通知
	virtual void OnRtnOrder(CKSOTPOrderField *pOrder) 
	{
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure();

		PyObject *dict = PyDict_New();
		PyDict_SetItemString(dict, "BrokerID", Py_BuildValue("s", pOrder->BrokerID));
		PyDict_SetItemString(dict, "InvestorID", Py_BuildValue("s", pOrder->InvestorID));
		PyDict_SetItemString(dict, "InstrumentID", Py_BuildValue("s", pOrder->InstrumentID));
		PyDict_SetItemString(dict, "OrderRef", Py_BuildValue("s", pOrder->OrderRef));
		PyDict_SetItemString(dict, "UserID", Py_BuildValue("s", pOrder->UserID));
		PyDict_SetItemString(dict, "OrderPriceType", Py_BuildValue("c", pOrder->OrderPriceType));
		PyDict_SetItemString(dict, "Direction", Py_BuildValue("c", pOrder->Direction));
		PyDict_SetItemString(dict, "OffsetFlag", Py_BuildValue("c", pOrder->OffsetFlag));
		PyDict_SetItemString(dict, "LimitPrice", Py_BuildValue("f", pOrder->LimitPrice));
		PyDict_SetItemString(dict, "HedgeFlag", Py_BuildValue("c", pOrder->HedgeFlag));
		PyDict_SetItemString(dict, "VolumeTotalOriginal", Py_BuildValue("i", pOrder->VolumeTotalOriginal));
		PyDict_SetItemString(dict, "TimeCondition", Py_BuildValue("c", pOrder->TimeCondition));
		PyDict_SetItemString(dict, "GTDDate", Py_BuildValue("s", pOrder->GTDDate));
		PyDict_SetItemString(dict, "VolumeCondition", Py_BuildValue("c", pOrder->VolumeCondition));
		PyDict_SetItemString(dict, "MinVolume", Py_BuildValue("i", pOrder->MinVolume));
		PyDict_SetItemString(dict, "ContingentCondition", Py_BuildValue("c", pOrder->ContingentCondition));
		PyDict_SetItemString(dict, "StopPrice", Py_BuildValue("f", pOrder->StopPrice));
		PyDict_SetItemString(dict, "ForceCloseReason", Py_BuildValue("c", pOrder->ForceCloseReason));
		PyDict_SetItemString(dict, "BusinessUnit", Py_BuildValue("s", pOrder->BusinessUnit));
		PyDict_SetItemString(dict, "RequestID", Py_BuildValue("i", pOrder->RequestID));
		PyDict_SetItemString(dict, "OrderLocalID", Py_BuildValue("s", pOrder->OrderLocalID));
		PyDict_SetItemString(dict, "ExchangeID", Py_BuildValue("s", pOrder->ExchangeID));
		PyDict_SetItemString(dict, "ParticipantID", Py_BuildValue("s", pOrder->ParticipantID));
		PyDict_SetItemString(dict, "ClientID", Py_BuildValue("s", pOrder->ClientID));
		PyDict_SetItemString(dict, "ExchangeInstID", Py_BuildValue("s", pOrder->ExchangeInstID));
		PyDict_SetItemString(dict, "TraderID", Py_BuildValue("s", pOrder->TraderID));
		PyDict_SetItemString(dict, "OrderSubmitStatus", Py_BuildValue("c", pOrder->OrderSubmitStatus));
		PyDict_SetItemString(dict, "NotifySequence", Py_BuildValue("i", pOrder->NotifySequence));
		PyDict_SetItemString(dict, "TradingDay", Py_BuildValue("s", pOrder->TradingDay));
		PyDict_SetItemString(dict, "SettlementID", Py_BuildValue("i", pOrder->SettlementID));
		PyDict_SetItemString(dict, "OrderSysID", Py_BuildValue("s", pOrder->OrderSysID));
		PyDict_SetItemString(dict, "OrderSource", Py_BuildValue("i", pOrder->OrderSource));
		PyDict_SetItemString(dict, "OrderStatus", Py_BuildValue("c", pOrder->OrderStatus));
		PyDict_SetItemString(dict, "OrderType", Py_BuildValue("c", pOrder->OrderType));
		PyDict_SetItemString(dict, "VolumeTraded", Py_BuildValue("i", pOrder->VolumeTraded));
		PyDict_SetItemString(dict, "VolumeTotal", Py_BuildValue("i", pOrder->VolumeTotal));
		PyDict_SetItemString(dict, "InsertDate", Py_BuildValue("s", pOrder->InsertDate));
		PyDict_SetItemString(dict, "InsertTime", Py_BuildValue("s", pOrder->InsertTime));
		PyDict_SetItemString(dict, "ActiveTime", Py_BuildValue("s", pOrder->ActiveTime));
		PyDict_SetItemString(dict, "UpdateTime", Py_BuildValue("s", pOrder->UpdateTime));
		PyDict_SetItemString(dict, "CancelTime", Py_BuildValue("s", pOrder->CancelTime));
		PyDict_SetItemString(dict, "SequenceNo", Py_BuildValue("i", pOrder->SequenceNo));
		PyDict_SetItemString(dict, "FrontID", Py_BuildValue("i", pOrder->FrontID));
		PyDict_SetItemString(dict, "SessionID", Py_BuildValue("i", pOrder->SessionID));
		PyDict_SetItemString(dict, "UserProductInfo", Py_BuildValue("s", pOrder->UserProductInfo));
		PyDict_SetItemString(dict, "StatusMsg", Py_BuildValue("s", pOrder->StatusMsg));
		PyDict_SetItemString(dict, "UserForceClose", Py_BuildValue("i", pOrder->UserForceClose));
		PyDict_SetItemString(dict, "ActiveUserID", Py_BuildValue("s", pOrder->ActiveUserID));
		PyDict_SetItemString(dict, "BrokerOrderSeq", Py_BuildValue("i", pOrder->BrokerOrderSeq));

		if (!PyObject_CallMethod(_spi, (char*)"OnRtnOrder", (char*)"N", dict))
		{
			PyErr_Print();
		}
		Py_XDECREF(dict);

		PyGILState_Release(gstate);
	};

	///成交通知
	virtual void OnRtnTrade(CKSOTPTradeField *pTrade) 
	{
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure();

		PyObject *dict = PyDict_New();
		PyDict_SetItemString(dict, "BrokerID", Py_BuildValue("s", pTrade->BrokerID));
		PyDict_SetItemString(dict, "InvestorID", Py_BuildValue("s", pTrade->InvestorID));
		PyDict_SetItemString(dict, "InstrumentID", Py_BuildValue("s", pTrade->InstrumentID));
		PyDict_SetItemString(dict, "OrderRef", Py_BuildValue("s", pTrade->OrderRef));
		PyDict_SetItemString(dict, "UserID", Py_BuildValue("s", pTrade->UserID));
		PyDict_SetItemString(dict, "ExchangeID", Py_BuildValue("s", pTrade->ExchangeID));
		PyDict_SetItemString(dict, "TradeID", Py_BuildValue("s", pTrade->TradeID));
		PyDict_SetItemString(dict, "Direction", Py_BuildValue("c", pTrade->Direction));
		PyDict_SetItemString(dict, "OrderSysID", Py_BuildValue("s", pTrade->OrderSysID));
		PyDict_SetItemString(dict, "ParticipantID", Py_BuildValue("s", pTrade->ParticipantID));
		PyDict_SetItemString(dict, "ClientID", Py_BuildValue("s", pTrade->ClientID));
		PyDict_SetItemString(dict, "TradingRole", Py_BuildValue("c", pTrade->TradingRole));
		PyDict_SetItemString(dict, "ExchangeInstID", Py_BuildValue("s", pTrade->ExchangeInstID));
		PyDict_SetItemString(dict, "OffsetFlag", Py_BuildValue("c", pTrade->OffsetFlag));
		PyDict_SetItemString(dict, "HedgeFlag", Py_BuildValue("c", pTrade->HedgeFlag));
		PyDict_SetItemString(dict, "Price", Py_BuildValue("f", pTrade->Price));
		PyDict_SetItemString(dict, "Volume", Py_BuildValue("i", pTrade->Volume));
		PyDict_SetItemString(dict, "TradeDate", Py_BuildValue("s", pTrade->TradeDate));
		PyDict_SetItemString(dict, "TradeTime", Py_BuildValue("s", pTrade->TradeTime));
		PyDict_SetItemString(dict, "TradeType", Py_BuildValue("c", pTrade->TradeType));
		PyDict_SetItemString(dict, "PriceSource", Py_BuildValue("c", pTrade->PriceSource));
		PyDict_SetItemString(dict, "TraderID", Py_BuildValue("s", pTrade->TraderID));
		PyDict_SetItemString(dict, "OrderLocalID", Py_BuildValue("s", pTrade->OrderLocalID));
		PyDict_SetItemString(dict, "ClearingPartID", Py_BuildValue("s", pTrade->ClearingPartID));
		PyDict_SetItemString(dict, "BusinessUnit", Py_BuildValue("s", pTrade->BusinessUnit));
		PyDict_SetItemString(dict, "SequenceNo", Py_BuildValue("i", pTrade->SequenceNo));
		PyDict_SetItemString(dict, "TradingDay", Py_BuildValue("s", pTrade->TradingDay));
		PyDict_SetItemString(dict, "BrokerOrderSeq", Py_BuildValue("i", pTrade->BrokerOrderSeq));
		PyDict_SetItemString(dict, "TradeSource", Py_BuildValue("c", pTrade->TradeSource));


		if (!PyObject_CallMethod(_spi, (char*)"OnRtnTrade", (char*)"N", dict))
		{
			PyErr_Print();
		}
		Py_XDECREF(dict);

		PyGILState_Release(gstate);
	};

	///查询个股期权合约保证金率请求响应
	virtual void OnRspQryInstrumentMarginRate(CKSOTPInstrumentMarginRateField *pInstrumentMarginRate, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
	{
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure();

		PyObject *dict = PyDict_New();
		PyDict_SetItemString(dict, "InstrumentID", Py_BuildValue("s", pInstrumentMarginRate->InstrumentID));
		PyDict_SetItemString(dict, "InvestorRange", Py_BuildValue("s", pInstrumentMarginRate->InvestorRange));
		PyDict_SetItemString(dict, "BrokerID", Py_BuildValue("s", pInstrumentMarginRate->BrokerID));
		PyDict_SetItemString(dict, "InvestorID", Py_BuildValue("s", pInstrumentMarginRate->InvestorID));
		PyDict_SetItemString(dict, "HedgeFlag", Py_BuildValue("c", pInstrumentMarginRate->HedgeFlag));
		PyDict_SetItemString(dict, "LongMarginRatioByMoney", Py_BuildValue("f", pInstrumentMarginRate->LongMarginRatioByMoney));
		PyDict_SetItemString(dict, "LongMarginRatioByVolume", Py_BuildValue("f", pInstrumentMarginRate->LongMarginRatioByVolume));
		PyDict_SetItemString(dict, "ShortMarginRatioByMoney", Py_BuildValue("f", pInstrumentMarginRate->ShortMarginRatioByMoney));
		PyDict_SetItemString(dict, "ShortMarginRatioByVolume", Py_BuildValue("f", pInstrumentMarginRate->ShortMarginRatioByVolume));
		PyDict_SetItemString(dict, "IsRelative", Py_BuildValue("i", pInstrumentMarginRate->IsRelative));
		if (!PyObject_CallMethod(_spi, (char*)"OnRspQryInstrumentMarginRate", (char*)"Nisib", dict,
			pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast))
		{
			PyErr_Print();
		}
		Py_XDECREF(dict);

		PyGILState_Release(gstate);
	}
};

#endif