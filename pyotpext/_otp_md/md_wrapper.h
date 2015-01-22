#ifndef _md_wrapper_h_
#define _md_wrapper_h_

#include <Python.h>
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

	};	

	///登录请求响应
	virtual void OnRspUserLogin(CKSOTPRspUserLoginField *pRspUserLogin, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{

	};

	///登出请求响应
	virtual void OnRspUserLogout(CKSOTPUserLogoutField *pUserLogout, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{

	};

	///错误应答
	virtual void OnRspError(CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{

	};

	///订阅行情应答
	virtual void OnRspSubMarketData(CKSOTPSpecificInstrumentField *pSpecificInstrument, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{

	};

	///取消订阅行情应答
	virtual void OnRspUnSubMarketData(CKSOTPSpecificInstrumentField *pSpecificInstrument, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{

	};

	///深度行情通知
	virtual void OnRtnDepthMarketData(CKSOTPDepthMarketDataField *pDepthMarketData) 
	{

	};
};

#endif