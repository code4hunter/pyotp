#ifndef _md_wrapper_h_
#define _md_wrapper_h_

#include <Python.h>
#include <string>
#include "KSOTPMdApi.h"

using namespace KingstarAPI;

class md_imp: public CKSOTPMdSpi
{
	PyObject * _spi;
public:
	md_imp(PyObject * spi)
	{
		_spi = spi;
 		Py_INCREF(_spi);
	}

	~md_imp()
	{
		Py_DECREF(_spi);
	}

	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。

	virtual void OnFrontConnected()
	{
		PyGILState_STATE gstate;
  		gstate=PyGILState_Ensure();

		if (!PyObject_CallMethod(_spi, (char*)"on_front_connected", NULL))
		{
		    PyErr_Print();
		}

		PyGILState_Release(gstate);
	};
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，客户端需要做重连处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason)
	{
		PyGILState_STATE gstate;
		gstate=PyGILState_Ensure();

		std::string reason;
		switch(nReason)
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
		if (!PyObject_CallMethod(_spi, (char*)"on_front_disconnected", (char*)"is", nReason,reason.c_str()))
		{
			PyErr_Print();
		}

		PyGILState_Release(gstate);
	};	

	///登录请求响应
	virtual void OnRspUserLogin(CKSOTPRspUserLoginField *pRspUserLogin, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{
		PyGILState_STATE gstate;
		gstate=PyGILState_Ensure();

		PyObject *dict = PyDict_New();
		if (pRspUserLogin != NULL)
		{
			PyDict_SetItemString(dict, "BrokerID", Py_BuildValue("s", pRspUserLogin->BrokerID));
			PyDict_SetItemString(dict, "TradingDay", Py_BuildValue("s", pRspUserLogin->TradingDay));
			PyDict_SetItemString(dict, "LoginTime", Py_BuildValue("s", pRspUserLogin->LoginTime));
			PyDict_SetItemString(dict, "UserID", Py_BuildValue("s", pRspUserLogin->UserID));
			PyDict_SetItemString(dict, "SystemName", Py_BuildValue("s", pRspUserLogin->SystemName));
			PyDict_SetItemString(dict, "FrontID", Py_BuildValue("i", pRspUserLogin->FrontID));
			PyDict_SetItemString(dict, "SessionID", Py_BuildValue("i", pRspUserLogin->SessionID));
			PyDict_SetItemString(dict, "MaxOrderRef", Py_BuildValue("s", pRspUserLogin->MaxOrderRef));
			PyDict_SetItemString(dict, "SSETime", Py_BuildValue("s", pRspUserLogin->SSETime));
		}
		if (!PyObject_CallMethod(_spi, (char*)"on_rsp_user_login", (char*)"Nisib",dict,
				pRspInfo->ErrorID,pRspInfo->ErrorMsg,nRequestID,bIsLast))
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
		gstate=PyGILState_Ensure();

		PyObject *dict = PyDict_New();
		if (pUserLogout != NULL)
		{
			PyDict_SetItemString(dict, "BrokerID", Py_BuildValue("s", pUserLogout->BrokerID));
			PyDict_SetItemString(dict, "UserID", Py_BuildValue("s", pUserLogout->UserID));
		}
		if (!PyObject_CallMethod(_spi, (char*)"on_rsp_user_logout", (char*)"Nisib",
				pRspInfo->ErrorID,pRspInfo->ErrorMsg,nRequestID,bIsLast))
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
		gstate=PyGILState_Ensure();

		if (!PyObject_CallMethod(_spi, (char*)"on_rsp_error", (char*)"isib",
				pRspInfo->ErrorID,pRspInfo->ErrorMsg,nRequestID,bIsLast))
		{
			PyErr_Print();
		}

		PyGILState_Release(gstate);
	};

	///订阅行情应答
	virtual void OnRspSubMarketData(CKSOTPSpecificInstrumentField *pSpecificInstrument, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{
		PyGILState_STATE gstate;
		gstate=PyGILState_Ensure();

		if (!PyObject_CallMethod(_spi, (char*)"on_rsp_sub_market_data", (char*)"sisib",pSpecificInstrument->InstrumentID,
				pRspInfo->ErrorID,pRspInfo->ErrorMsg,nRequestID,bIsLast))
		{
			PyErr_Print();
		}

		PyGILState_Release(gstate);
	};

	///取消订阅行情应答
	virtual void OnRspUnSubMarketData(CKSOTPSpecificInstrumentField *pSpecificInstrument, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{
		PyGILState_STATE gstate;
		gstate=PyGILState_Ensure();

		if (!PyObject_CallMethod(_spi, (char*)"on_rsp_unsub_market_data", (char*)"sisib",pSpecificInstrument->InstrumentID,
				pRspInfo->ErrorID,pRspInfo->ErrorMsg,nRequestID,bIsLast))
		{
			PyErr_Print();
		}

		PyGILState_Release(gstate);
	};

	///深度行情通知
	virtual void OnRtnDepthMarketData(CKSOTPDepthMarketDataField *pDepthMarketData) 
	{
		PyGILState_STATE gstate;
		gstate=PyGILState_Ensure();

		PyObject *dict = PyDict_New();
		if (pDepthMarketData != NULL)
		{

			PyDict_SetItemString(dict, "TradingDay", Py_BuildValue("s", pDepthMarketData->TradingDay));
			PyDict_SetItemString(dict, "InstrumentID", Py_BuildValue("s", pDepthMarketData->InstrumentID));
			PyDict_SetItemString(dict, "ExchangeID", Py_BuildValue("s", pDepthMarketData->ExchangeID));
			PyDict_SetItemString(dict, "ExchangeInstID", Py_BuildValue("s", pDepthMarketData->ExchangeInstID));
			PyDict_SetItemString(dict, "LastPrice", Py_BuildValue("d", pDepthMarketData->LastPrice));
			PyDict_SetItemString(dict, "PreSettlementPrice", Py_BuildValue("d", pDepthMarketData->PreSettlementPrice));
			PyDict_SetItemString(dict, "PreClosePrice", Py_BuildValue("d", pDepthMarketData->PreClosePrice));
			PyDict_SetItemString(dict, "PreOpenInterest", Py_BuildValue("d", pDepthMarketData->PreOpenInterest));
			PyDict_SetItemString(dict, "OpenPrice", Py_BuildValue("d", pDepthMarketData->OpenPrice));
			PyDict_SetItemString(dict, "HighestPrice", Py_BuildValue("d", pDepthMarketData->HighestPrice));
			PyDict_SetItemString(dict, "LowestPrice", Py_BuildValue("d", pDepthMarketData->LowestPrice));
			PyDict_SetItemString(dict, "Volume", Py_BuildValue("i", pDepthMarketData->Volume));
			PyDict_SetItemString(dict, "Turnover", Py_BuildValue("d", pDepthMarketData->Turnover));
			PyDict_SetItemString(dict, "OpenInterest", Py_BuildValue("d", pDepthMarketData->OpenInterest));
			PyDict_SetItemString(dict, "ClosePrice", Py_BuildValue("d", pDepthMarketData->ClosePrice));
			PyDict_SetItemString(dict, "SettlementPrice", Py_BuildValue("d", pDepthMarketData->SettlementPrice));
			PyDict_SetItemString(dict, "UpperLimitPrice", Py_BuildValue("d", pDepthMarketData->UpperLimitPrice));
			PyDict_SetItemString(dict, "LowerLimitPrice", Py_BuildValue("d", pDepthMarketData->LowerLimitPrice));
			PyDict_SetItemString(dict, "PreDelta", Py_BuildValue("d", pDepthMarketData->PreDelta));
			PyDict_SetItemString(dict, "CurrDelta", Py_BuildValue("d", pDepthMarketData->CurrDelta));
			PyDict_SetItemString(dict, "UpdateTime", Py_BuildValue("s", pDepthMarketData->UpdateTime));
			PyDict_SetItemString(dict, "UpdateMillisec", Py_BuildValue("i", pDepthMarketData->UpdateMillisec));

			PyDict_SetItemString(dict, "BidPrice1", Py_BuildValue("d", pDepthMarketData->BidPrice1));
			PyDict_SetItemString(dict, "BidVolume1", Py_BuildValue("i", pDepthMarketData->BidVolume1));
			PyDict_SetItemString(dict, "AskPrice1", Py_BuildValue("d", pDepthMarketData->AskPrice1));
			PyDict_SetItemString(dict, "AskVolume1", Py_BuildValue("i", pDepthMarketData->AskVolume1));

			PyDict_SetItemString(dict, "BidPrice2", Py_BuildValue("d", pDepthMarketData->BidPrice2));
			PyDict_SetItemString(dict, "BidVolume2", Py_BuildValue("i", pDepthMarketData->BidVolume2));
			PyDict_SetItemString(dict, "AskPrice2", Py_BuildValue("d", pDepthMarketData->AskPrice2));
			PyDict_SetItemString(dict, "AskVolume2", Py_BuildValue("i", pDepthMarketData->AskVolume2));

			PyDict_SetItemString(dict, "BidPrice3", Py_BuildValue("d", pDepthMarketData->BidPrice3));
			PyDict_SetItemString(dict, "BidVolume3", Py_BuildValue("i", pDepthMarketData->BidVolume3));
			PyDict_SetItemString(dict, "AskPrice3", Py_BuildValue("d", pDepthMarketData->AskPrice3));
			PyDict_SetItemString(dict, "AskVolume3", Py_BuildValue("i", pDepthMarketData->AskVolume3));

			PyDict_SetItemString(dict, "BidPrice4", Py_BuildValue("d", pDepthMarketData->BidPrice4));
			PyDict_SetItemString(dict, "BidVolume4", Py_BuildValue("i", pDepthMarketData->BidVolume4));
			PyDict_SetItemString(dict, "AskPrice4", Py_BuildValue("d", pDepthMarketData->AskPrice4));
			PyDict_SetItemString(dict, "AskVolume4", Py_BuildValue("i", pDepthMarketData->AskVolume4));

			PyDict_SetItemString(dict, "BidPrice5", Py_BuildValue("d", pDepthMarketData->BidPrice5));
			PyDict_SetItemString(dict, "BidVolume5", Py_BuildValue("i", pDepthMarketData->BidVolume5));
			PyDict_SetItemString(dict, "AskPrice5", Py_BuildValue("d", pDepthMarketData->AskPrice5));
			PyDict_SetItemString(dict, "AskVolume5", Py_BuildValue("i", pDepthMarketData->AskVolume5));

			PyDict_SetItemString(dict, "AveragePrice", Py_BuildValue("d", pDepthMarketData->AveragePrice));
			PyDict_SetItemString(dict, "ActionDay", Py_BuildValue("s", pDepthMarketData->ActionDay));
		}
		if (!PyObject_CallMethod(_spi, (char*)"on_rtn_depth_market_data", (char*)"N", dict))
		{
			PyErr_Print();
		}
		Py_XDECREF(dict);
		PyGILState_Release(gstate);
	};
};

#endif