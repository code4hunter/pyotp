#include "KSOTPTraderApi.h"
#include "trd_wrapper.h"

#include <Python.h>

using namespace KingstarAPI;

char _get_map_char(PyObject *map, const char *key)
{
	PyObject * v = PyDict_GetItemString(map, key);
	if (v == NULL) return '\0';
	char *s = PyString_AsString(v);
	if (s == NULL) return '\0';
	if (strlen(s) > 0) return s[0];
	else return '\0';
}

void _get_map_string(PyObject *map, const char *key, char *buf, int size)
{
	buf[0] = 0;
	PyObject * v = PyDict_GetItemString(map, key);
	if (v == NULL) return;
	char *s = PyString_AsString(v);
	if (s == NULL) return;
 	strncpy(buf, s, size - 1);
}

double _get_map_double(PyObject *map, const char *key)
{
	PyObject * v = PyDict_GetItemString(map, key);
	if (v == NULL) return 0;
	double ret = PyFloat_AsDouble(v);
	if (PyErr_Occurred() != NULL)
	{
		ret = 0;
	}
	return ret;
}

int _get_map_int(PyObject *map, const char *key)
{
	PyObject * v = PyDict_GetItemString(map, key);
	if (v == NULL) return 0;
	int ret =  PyLong_AsLong(v);
	if (PyErr_Occurred() != NULL)
	{
		ret = 0;
	}
	return ret;
}

///创建TraderApi
///@return 创建出的UserApi
///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
static PyObject* CreateTrdApi(PyObject* self, PyObject *args)
{
	char * pszFlowPath=NULL;
	PyArg_ParseTuple(args, "s", &pszFlowPath);
	CKSOTPTraderApi *p = CKSOTPTraderApi::CreateOTPTraderApi(pszFlowPath);
	return PyInt_FromLong((long)(void*)p);
}

///删除接口对象本身
///@remark 不再使用本接口对象时,调用该函数删除接口对象
static PyObject* Release(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *) PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	handle->Release();
	Py_INCREF(Py_None);
	return Py_None;
}

///初始化
///@remark 初始化运行环境,只有调用后,接口才开始工作
static PyObject* Init(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *) PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	handle->Init();
	Py_INCREF(Py_None);
	return Py_None;
}

///获取当前交易日
///@return 获取到的交易日
///@remark 只有登录成功后,才能得到正确的交易日
static PyObject* GetTradingDay(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *) PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * ret = Py_BuildValue("s", handle->GetTradingDay());
	return ret;
}

///注册前置机网络地址
///@param pszFrontAddress：前置机网络地址.
///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”. 
///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址.”17001”代表服务器端口号.
static PyObject* RegisterFront(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *) PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * py_pszFrontAddress = PyTuple_GET_ITEM(args, 1);
	char* pszFrontAddress = PyString_AsString(py_pszFrontAddress);
	handle->RegisterFront(pszFrontAddress);
	Py_INCREF(Py_None);
	return Py_None;
}

///注册回调接口
///@param pSpi 派生自回调接口类的实例
static PyObject* RegisterSpi(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *) PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * py_pSpi = PyTuple_GET_ITEM(args, 1);
	CKSOTPTraderSpi *imp = new trd_imp(py_pSpi); 
	handle->RegisterSpi(imp);
	Py_INCREF(Py_None);
	return Py_None;
}

///订阅私有流.
///@param nResumeType 私有流重传方式  
///        THOST_TERT_RESTART:从本交易日开始重传
///        THOST_TERT_RESUME:从上次收到的续传
///        THOST_TERT_QUICK:只传送登录后私有流的内容
///@remark 该方法要在Init方法前调用.若不调用则不会收到私有流的数据.
static PyObject* SubscribePrivateTopic(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	KSOTP_TE_RESUME_TYPE nResumeType = (KSOTP_TE_RESUME_TYPE)PyInt_AsLong(PyTuple_GET_ITEM(args, 1));
	handle->SubscribePrivateTopic(nResumeType);
	Py_INCREF(Py_None);
	return Py_None;
}

///订阅公共流.
///@param nResumeType 公共流重传方式  
///        THOST_TERT_RESTART:从本交易日开始重传
///        THOST_TERT_RESUME:从上次收到的续传
///        THOST_TERT_QUICK:只传送登录后公共流的内容
///@remark 该方法要在Init方法前调用.若不调用则不会收到公共流的数据.
static PyObject* SubscribePublicTopic(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	KSOTP_TE_RESUME_TYPE nResumeType = (KSOTP_TE_RESUME_TYPE)PyInt_AsLong(PyTuple_GET_ITEM(args, 1));
	handle->SubscribePublicTopic(nResumeType);
	Py_INCREF(Py_None);
	return Py_None;
}

///用户登录请求
static PyObject* ReqUserLogin(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * map = PyTuple_GET_ITEM(args, 1);
	CKSOTPReqUserLoginField req;

	_get_map_string(map, "BrokerID", req.BrokerID, sizeof(req.BrokerID));
	_get_map_string(map, "UserID", req.UserID, sizeof(req.UserID));
	_get_map_string(map, "Password", req.Password, sizeof(req.Password));
	_get_map_string(map, "UserProductInfo", req.UserProductInfo, sizeof(req.UserProductInfo));
	_get_map_string(map, "MacAddress", req.MacAddress, sizeof(req.MacAddress));
	_get_map_string(map, "ClientIPAddress", req.ClientIPAddress, sizeof(req.ClientIPAddress));

	PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
	int nRequestID = PyInt_AsLong(py_nRequestID);
	PyObject * ret = Py_BuildValue("i", handle->ReqUserLogin(&req, nRequestID));
	return ret;
}

///登出请求
static PyObject* ReqUserLogout(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * map = PyTuple_GET_ITEM(args, 1);
	CKSOTPUserLogoutField req = { 0 };
	_get_map_string(map, "BrokerID", req.BrokerID, sizeof(req.BrokerID));
	_get_map_string(map, "UserID", req.UserID, sizeof(req.UserID));

	PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
	int nRequestID = PyInt_AsLong(py_nRequestID);
	PyObject * ret = Py_BuildValue("i", handle->ReqUserLogout(&req, nRequestID));
	return ret;
}

///用户口令更新请求
//static PyObject* ReqUserPasswordUpdate(CKSOTPUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID){}

///资金账户口令更新请求
//static PyObject* ReqTradingAccountPasswordUpdate(CKSOTPTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, int nRequestID){}

///报单录入请求
static PyObject* ReqOrderInsert(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * map = PyTuple_GET_ITEM(args, 1);
	CKSOTPInputOrderField req = { 0 };
	_get_map_string(map, "BrokerID", req.BrokerID, sizeof(req.BrokerID));
	_get_map_string(map, "InvestorID", req.InvestorID, sizeof(req.InvestorID));
	_get_map_string(map, "InstrumentID", req.InstrumentID, sizeof(req.InstrumentID));
	_get_map_string(map, "OrderRef", req.OrderRef, sizeof(req.OrderRef));
	_get_map_string(map, "UserID", req.UserID, sizeof(req.UserID));
	_get_map_string(map, "GTDDate", req.GTDDate, sizeof(req.GTDDate));
	_get_map_string(map, "BusinessUnit", req.BusinessUnit, sizeof(req.BusinessUnit));

	req.OrderPriceType = _get_map_char(map, "OrderPriceType");
	req.OffsetFlag = _get_map_char(map, "OffsetFlag");
	req.HedgeFlag = _get_map_char(map, "HedgeFlag");
	req.TimeCondition = _get_map_char(map, "TimeCondition");
	req.VolumeCondition = _get_map_char(map, "VolumeCondition");
	req.ContingentCondition = _get_map_char(map, "ContingentCondition");

	req.LimitPrice = _get_map_double(map, "LimitPrice");
	req.StopPrice = _get_map_double(map, "StopPrice");
	req.VolumeTotalOriginal = _get_map_int(map, "VolumeTotalOriginal");
	req.MinVolume = _get_map_int(map, "MinVolume");
	req.RequestID = _get_map_int(map, "RequestID");

	PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
	int nRequestID = PyInt_AsLong(py_nRequestID);

	PyObject * ret = Py_BuildValue("i", handle->ReqOrderInsert(&req, nRequestID));
	return ret;
}

///报单操作请求
static PyObject* ReqOrderAction(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * map = PyTuple_GET_ITEM(args, 1);
	CKSOTPInputOrderActionField req = { 0 };

	_get_map_string(map, "BrokerID", req.BrokerID, sizeof(req.BrokerID));
	_get_map_string(map, "InvestorID", req.InvestorID, sizeof(req.InvestorID));
	_get_map_string(map, "OrderRef", req.OrderRef, sizeof(req.OrderRef));
	_get_map_string(map, "ExchangeID", req.ExchangeID, sizeof(req.ExchangeID));
	_get_map_string(map, "OrderSysID", req.OrderSysID, sizeof(req.OrderSysID));
	_get_map_string(map, "UserID", req.UserID, sizeof(req.UserID));
	_get_map_string(map, "InstrumentID", req.InstrumentID, sizeof(req.InstrumentID));

	req.RequestID = _get_map_int(map, "RequestID");
	req.FrontID = _get_map_int(map, "FrontID");
	req.SessionID = _get_map_int(map, "SessionID");
	req.VolumeChange = _get_map_int(map, "VolumeChange");
	
	req.ActionFlag = _get_map_char(map, "ActionFlag");
	req.LimitPrice = _get_map_double(map, "LimitPrice");

	PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
	int nRequestID = PyInt_AsLong(py_nRequestID);

	PyObject * ret = Py_BuildValue("i", handle->ReqOrderAction(&req, nRequestID));
	return ret;
}

///请求查询报单
static PyObject* ReqQryOrder(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * map = PyTuple_GET_ITEM(args, 1);
	CKSOTPQryOrderField req;

	_get_map_string(map, "BrokerID", req.BrokerID, sizeof(req.BrokerID));
	_get_map_string(map, "InvestorID", req.InvestorID, sizeof(req.InvestorID));
	_get_map_string(map, "ExchangeID", req.ExchangeID, sizeof(req.ExchangeID));
	_get_map_string(map, "OrderSysID", req.OrderSysID, sizeof(req.OrderSysID));
	_get_map_string(map, "InstrumentID", req.InstrumentID, sizeof(req.InstrumentID));

	PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
	int nRequestID = PyInt_AsLong(py_nRequestID);

	PyObject * ret = Py_BuildValue("i", handle->ReqQryOrder(&req, nRequestID));
	return ret;
}

///请求查询成交
static PyObject* ReqQryTrade(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * map = PyTuple_GET_ITEM(args, 1);
	CKSOTPQryTradeField req;

	_get_map_string(map, "BrokerID", req.BrokerID, sizeof(req.BrokerID));
	_get_map_string(map, "InvestorID", req.InvestorID, sizeof(req.InvestorID));
	_get_map_string(map, "ExchangeID", req.ExchangeID, sizeof(req.ExchangeID));
	_get_map_string(map, "InstrumentID", req.InstrumentID, sizeof(req.InstrumentID));
	_get_map_string(map, "TradeTimeStart", req.TradeTimeStart, sizeof(req.TradeTimeStart));
	_get_map_string(map, "TradeTimeEnd", req.TradeTimeEnd, sizeof(req.TradeTimeEnd));

	PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
	int nRequestID = PyInt_AsLong(py_nRequestID);

	PyObject * ret = Py_BuildValue("i", handle->ReqQryTrade(&req, nRequestID));
	return ret;
}

///请求查询投资者持仓
static PyObject* ReqQryInvestorPosition(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * map = PyTuple_GET_ITEM(args, 1);
	CKSOTPQryInvestorPositionField req;

	_get_map_string(map, "BrokerID", req.BrokerID, sizeof(req.BrokerID));
	_get_map_string(map, "InvestorID", req.InvestorID, sizeof(req.InvestorID));
	_get_map_string(map, "InstrumentID", req.InstrumentID, sizeof(req.InstrumentID));

	PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
	int nRequestID = PyInt_AsLong(py_nRequestID);

	PyObject * ret = Py_BuildValue("i", handle->ReqQryInvestorPosition(&req, nRequestID));
	return ret;
}

///请求查询资金账户
static PyObject* ReqQryTradingAccount(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * map = PyTuple_GET_ITEM(args, 1);
	CKSOTPQryTradingAccountField req;

	_get_map_string(map, "BrokerID", req.BrokerID, sizeof(req.BrokerID));
	_get_map_string(map, "InvestorID", req.InvestorID, sizeof(req.InvestorID));

	PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
	int nRequestID = PyInt_AsLong(py_nRequestID);

	PyObject * ret = Py_BuildValue("i", handle->ReqQryTradingAccount(&req, nRequestID));
	return ret;
}

///请求查询投资者
static PyObject* ReqQryInvestor(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * map = PyTuple_GET_ITEM(args, 1);
	CKSOTPQryInvestorField req;

	_get_map_string(map, "BrokerID", req.BrokerID, sizeof(req.BrokerID));
	_get_map_string(map, "InvestorID", req.InvestorID, sizeof(req.InvestorID));

	PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
	int nRequestID = PyInt_AsLong(py_nRequestID);

	PyObject * ret = Py_BuildValue("i", handle->ReqQryInvestor(&req, nRequestID));
	return ret;
}

///请求查询合约账号
//static PyObject* ReqQryTradingCode(CKSOTPQryTradingCodeField *pQryTradingCode, int nRequestID){}

///请求查询交易所
//static PyObject* ReqQryExchange(CKSOTPQryExchangeField *pQryExchange, int nRequestID){}

///请求查询合约
static PyObject* ReqQryInstrument(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * map = PyTuple_GET_ITEM(args, 1);
	CKSOTPQryInstrumentField req;

	_get_map_string(map, "ExchangeID", req.ExchangeID, sizeof(req.ExchangeID));
	_get_map_string(map, "InstrumentID", req.InstrumentID, sizeof(req.InstrumentID));

	PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
	int nRequestID = PyInt_AsLong(py_nRequestID);

	PyObject * ret = Py_BuildValue("i", handle->ReqQryInstrument(&req, nRequestID));
	return ret;
}

///请求查询投资者持仓明细
static PyObject* ReqQryInvestorPositionDetail(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * map = PyTuple_GET_ITEM(args, 1);
	CKSOTPQryInvestorPositionDetailField req;

	_get_map_string(map, "BrokerID", req.BrokerID, sizeof(req.BrokerID));
	_get_map_string(map, "InvestorID", req.InvestorID, sizeof(req.InvestorID));
	_get_map_string(map, "InstrumentID", req.InstrumentID, sizeof(req.InstrumentID));

	PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
	int nRequestID = PyInt_AsLong(py_nRequestID);

	PyObject * ret = Py_BuildValue("i", handle->ReqQryInvestorPositionDetail(&req, nRequestID));
	return ret;
}

///请求查询交易通知
//static PyObject* ReqQryTradingNotice(CKSOTPQryTradingNoticeField *pQryTradingNotice, int nRequestID){}

///非交易报单录入请求
//static PyObject* ReqNonTradingOrderInsert(CKSOTPInputNonTradingOrderField *pInputNonTradingOrder, int nRequestID){}

///非交易报单操作请求（仅针对行权单）
//static PyObject* ReqNonTradingOrderAction(CKSOTPInputNonTradingOrderActionField *pInputNonTradingOrderAction, int nRequestID){}

///请求查询非交易报单
//static PyObject* ReqQryNonTradingOrder(CKSOTPQryNonTradingOrderField *pQryNonTradingOrder, int nRequestID){}

///查询非交易报单量请求
//static PyObject* ReqQryNonTradingOrderVolume(CKSOTPQryNonTradingOrderVolumeField *pQryNonTradingOrderVolume, int nRequestID){}

///查询标的券信息请求
//static PyObject* ReqQryUnderlyingStockInfo(CKSOTPQryUnderlyingStockInfoField *pQryOTPOrderParams, int nRequestID){}

///查询个股期权手续费率请求
static PyObject* ReqQryOTPInsCommRate(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * map = PyTuple_GET_ITEM(args, 1);
	CKSOTPQryOTPInsCommRateField req;

	_get_map_string(map, "BrokerID", req.BrokerID, sizeof(req.BrokerID));
	_get_map_string(map, "InvestorID", req.InvestorID, sizeof(req.InvestorID));
	_get_map_string(map, "InstrumentID", req.InstrumentID, sizeof(req.InstrumentID));

	PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
	int nRequestID = PyInt_AsLong(py_nRequestID);

	PyObject * ret = Py_BuildValue("i", handle->ReqQryOTPInsCommRate(&req, nRequestID));
	return ret;
}

///查询个股期权保证金率请求
static PyObject* ReqQryOTPInsMarginRate(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * map = PyTuple_GET_ITEM(args, 1);
	CKSOTPQryOTPInsMarginRateField req;

	_get_map_string(map, "BrokerID", req.BrokerID, sizeof(req.BrokerID));
	_get_map_string(map, "InvestorID", req.InvestorID, sizeof(req.InvestorID));
	_get_map_string(map, "InstrumentID", req.InstrumentID, sizeof(req.InstrumentID));

	PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
	int nRequestID = PyInt_AsLong(py_nRequestID);

	PyObject * ret = Py_BuildValue("i", handle->ReqQryOTPInsMarginRate(&req, nRequestID));
	return ret;
}

///查询个股行权指派信息
//static PyObject* ReqQryOTPAssignment(CKSOTPQryOTPAssignmentField *pQryOTPAssignment, int nRequestID){}

///请求查询行情 
//static PyObject* ReqQryDepthMarketData(CKSOTPQryDepthMarketDataField *pQryOTPDepthMarketData, int nRequestID){}

///银行资金转个股请求
//static PyObject* ReqFromBankToStockByStock(CKSOTPReqTransferField *pReqTransfer, int nRequestID){}

///证券资金转银行请求
//static PyObject* ReqFromStockToBankByStock(CKSOTPReqTransferField *pReqTransfer, int nRequestID){}

///请求查询签约银行
//static PyObject* ReqQryContractBank(CKSOTPQryContractBankField *pQryContractBank, int nRequestID){}

///查询银行余额请求
//static PyObject* ReqQueryBankAccountMoneyByStock(CKSOTPReqQueryAccountField *pReqQueryAccount, int nRequestID){}

///请求查询转帐流水
//static PyObject* ReqQryTransferSerial(CKSOTPQryTransferSerialField *pQryTransferSerial, int nRequestID){}

///请求查询结算信息确认
//static PyObject* ReqQrySettlementInfoConfirm(CKSOTPQrySettlementInfoConfirmField *pQrySettlementInfoConfirm, int nRequestID){}

///投资者结算结果确认
//static PyObject* ReqSettlementInfoConfirm(CKSOTPSettlementInfoConfirmField *pSettlementInfoConfirm, int nRequestID){}

///请求查询投资者结算结果
//static PyObject* ReqQrySettlementInfo(CKSOTPQrySettlementInfoField *pQrySettlementInfo, int nRequestID){}

///查询客户交易级别
static PyObject* ReqQryInvestorTradeLevel(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * map = PyTuple_GET_ITEM(args, 1);
	CKSOTPQryInvestorTradeLevelField req;

	_get_map_string(map, "BrokerID", req.BrokerID, sizeof(req.BrokerID));
	_get_map_string(map, "ExchangeID", req.ExchangeID, sizeof(req.ExchangeID));
	_get_map_string(map, "ProductID", req.ProductID, sizeof(req.ProductID));

	PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
	int nRequestID = PyInt_AsLong(py_nRequestID);

	PyObject * ret = Py_BuildValue("i", handle->ReqQryInvestorTradeLevel(&req, nRequestID));
	return ret;
}

///查询个股限购额度
//static PyObject* ReqQryPurchaseLimitAmt(CKSOTPQryPurchaseLimitAmtField *pQryPurchaseLimitAmt, int nRequestID){}

///查询个股限仓额度
//static PyObject* ReqQryPositionLimitVol(CKSOTPQryPositionLimitVolField *pQryPositionLimitVol, int nRequestID){}

///请求查询历史报单
//static PyObject* ReqQryHistoryOrder(CKSOTPQryHistoryOrderField *pQryHistoryOrder, int nRequestID){}

///请求查询历史成交
//static PyObject* ReqQryHistoryTrade(CKSOTPQryHistoryTradeField *pQryHistoryTrade, int nRequestID){}

///请求查询历史行权指派明细
//static PyObject* ReqQryHistoryAssignment(CKSOTPQryHistoryAssignmentField *pQryHistoryAssignment, int nRequestID){}

///请求查询行权交割明细
//static PyObject* ReqQryDelivDetail(CKSOTPQryDelivDetailField *pQryDelivDetail, int nRequestID){}

///自动行权执行操作
//static PyObject* ReqAutoExecOrderAction(CKSOTPAutoExecOrderActionField *pAutoExecOrderAction, int nRequestID){}

extern "C" __declspec(dllexport) void init_otp_trd()
{
	static PyMethodDef mbMethods[] = {
		{ "CreateTrdApi", CreateTrdApi, METH_VARARGS },
		{ "GetTradingDay", GetTradingDay, METH_VARARGS },
		{ "Init", Init, METH_VARARGS },
		{ "RegisterFront", RegisterFront, METH_VARARGS },
		{ "RegisterSpi", RegisterSpi, METH_VARARGS },
		{ "Release", Release, METH_VARARGS },
		{ "ReqOrderAction", ReqOrderAction, METH_VARARGS },
		{ "ReqOrderInsert", ReqOrderInsert, METH_VARARGS },
		{ "ReqQryInstrument", ReqQryInstrument, METH_VARARGS },
		{ "ReqQryInvestor", ReqQryInvestor, METH_VARARGS },
		{ "ReqQryInvestorPosition", ReqQryInvestorPosition, METH_VARARGS },
		{ "ReqQryInvestorPositionDetail", ReqQryInvestorPositionDetail, METH_VARARGS },
		{ "ReqQryInvestorTradeLevel", ReqQryInvestorTradeLevel, METH_VARARGS },
		{ "ReqQryOrder", ReqQryOrder, METH_VARARGS },
		{ "ReqQryOTPInsCommRate", ReqQryOTPInsCommRate, METH_VARARGS },
		{ "ReqQryOTPInsMarginRate", ReqQryOTPInsMarginRate, METH_VARARGS },
		{ "ReqQryTrade", ReqQryTrade, METH_VARARGS },
		{ "ReqQryTradingAccount", ReqQryTradingAccount, METH_VARARGS },
		{ "ReqUserLogin", ReqUserLogin, METH_VARARGS },
		{ "ReqUserLogout", ReqUserLogout, METH_VARARGS },
		{ "SubscribePrivateTopic", SubscribePrivateTopic, METH_VARARGS },
		{ "SubscribePublicTopic", SubscribePublicTopic, METH_VARARGS },
		{ NULL, NULL, NULL }
	};

	PyObject *m = Py_InitModule("_otp_trd", mbMethods);

	PyEval_InitThreads();
}