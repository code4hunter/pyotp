#include "KSOTPTraderApi.h"
#include "trd_wrapper.h"

#include <Python.h>

using namespace KingstarAPI;

///创建TraderApi
///@return 创建出的UserApi
///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
static PyObject* createTrdApi(PyObject* self, PyObject *args)
{
	char * pszFlowPath=NULL;
	PyArg_ParseTuple(args, "s", &pszFlowPath);
	CKSOTPTraderApi *p = CKSOTPTraderApi::CreateOTPTraderApi(pszFlowPath);
	return PyInt_FromLong((void*)p);
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
static PyObject* RegisterSpi(CKSOTPTraderSpi *pSpi)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *) PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * py_pSpi = PyTuple_GET_ITEM(args, 1);
	CKSOTPTraderSpi *imp = new trd_imp(py_pSpi); 
	handle->RegisterSpi(pSpi);
	Py_INCREF(Py_None);
	return Py_None;
}

///订阅私有流.
///@param nResumeType 私有流重传方式  
///        THOST_TERT_RESTART:从本交易日开始重传
///        THOST_TERT_RESUME:从上次收到的续传
///        THOST_TERT_QUICK:只传送登录后私有流的内容
///@remark 该方法要在Init方法前调用.若不调用则不会收到私有流的数据.
static PyObject* SubscribePrivateTopic(KSOTP_TE_RESUME_TYPE nResumeType)
{

}

///订阅公共流.
///@param nResumeType 公共流重传方式  
///        THOST_TERT_RESTART:从本交易日开始重传
///        THOST_TERT_RESUME:从上次收到的续传
///        THOST_TERT_QUICK:只传送登录后公共流的内容
///@remark 该方法要在Init方法前调用.若不调用则不会收到公共流的数据.
static PyObject* SubscribePublicTopic(KSOTP_TE_RESUME_TYPE nResumeType)
{
	
}

///用户登录请求
static PyObject* ReqUserLogin(CKSOTPReqUserLoginField *pReqUserLoginField, int nRequestID){}

///登出请求
static PyObject* ReqUserLogout(CKSOTPUserLogoutField *pUserLogout, int nRequestID){}

///用户口令更新请求
static PyObject* ReqUserPasswordUpdate(CKSOTPUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID){}

///资金账户口令更新请求
static PyObject* ReqTradingAccountPasswordUpdate(CKSOTPTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, int nRequestID){}

///报单录入请求
static PyObject* ReqOrderInsert(CKSOTPInputOrderField *pInputOrder, int nRequestID){}

///报单操作请求
static PyObject* ReqOrderAction(CKSOTPInputOrderActionField *pInputOrderAction, int nRequestID){}

///请求查询报单
static PyObject* ReqQryOrder(CKSOTPQryOrderField *pQryOrder, int nRequestID){}

///请求查询成交
static PyObject* ReqQryTrade(CKSOTPQryTradeField *pQryTrade, int nRequestID){}

///请求查询投资者持仓
static PyObject* ReqQryInvestorPosition(CKSOTPQryInvestorPositionField *pQryInvestorPosition, int nRequestID){}

///请求查询资金账户
static PyObject* ReqQryTradingAccount(CKSOTPQryTradingAccountField *pQryTradingAccount, int nRequestID){}

///请求查询投资者
static PyObject* ReqQryInvestor(CKSOTPQryInvestorField *pQryInvestor, int nRequestID){}

///请求查询合约账号
static PyObject* ReqQryTradingCode(CKSOTPQryTradingCodeField *pQryTradingCode, int nRequestID){}

///请求查询交易所
static PyObject* ReqQryExchange(CKSOTPQryExchangeField *pQryExchange, int nRequestID){}

///请求查询合约
static PyObject* ReqQryInstrument(CKSOTPQryInstrumentField *pQryInstrument, int nRequestID){}

///请求查询投资者持仓明细
static PyObject* ReqQryInvestorPositionDetail(CKSOTPQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID){}

///请求查询交易通知
static PyObject* ReqQryTradingNotice(CKSOTPQryTradingNoticeField *pQryTradingNotice, int nRequestID){}

///非交易报单录入请求
static PyObject* ReqNonTradingOrderInsert(CKSOTPInputNonTradingOrderField *pInputNonTradingOrder, int nRequestID){}

///非交易报单操作请求（仅针对行权单）
static PyObject* ReqNonTradingOrderAction(CKSOTPInputNonTradingOrderActionField *pInputNonTradingOrderAction, int nRequestID){}

///请求查询非交易报单
static PyObject* ReqQryNonTradingOrder(CKSOTPQryNonTradingOrderField *pQryNonTradingOrder, int nRequestID){}

///查询非交易报单量请求
static PyObject* ReqQryNonTradingOrderVolume(CKSOTPQryNonTradingOrderVolumeField *pQryNonTradingOrderVolume, int nRequestID){}

///查询标的券信息请求
static PyObject* ReqQryUnderlyingStockInfo(CKSOTPQryUnderlyingStockInfoField *pQryOTPOrderParams, int nRequestID){}

///查询个股期权手续费率请求
static PyObject* ReqQryOTPInsCommRate(CKSOTPQryOTPInsCommRateField *pQryOTPInsCommRate, int nRequestID){}

///查询个股期权保证金率请求
static PyObject* ReqQryOTPInsMarginRate(CKSOTPQryOTPInsMarginRateField *pQryOTPInsMarginRate, int nRequestID){}

///查询个股行权指派信息
static PyObject* ReqQryOTPAssignment(CKSOTPQryOTPAssignmentField *pQryOTPAssignment, int nRequestID){}

///请求查询行情 
static PyObject* ReqQryDepthMarketData(CKSOTPQryDepthMarketDataField *pQryOTPDepthMarketData, int nRequestID){}

///银行资金转个股请求
static PyObject* ReqFromBankToStockByStock(CKSOTPReqTransferField *pReqTransfer, int nRequestID){}

///证券资金转银行请求
static PyObject* ReqFromStockToBankByStock(CKSOTPReqTransferField *pReqTransfer, int nRequestID){}

///请求查询签约银行
static PyObject* ReqQryContractBank(CKSOTPQryContractBankField *pQryContractBank, int nRequestID){}

///查询银行余额请求
static PyObject* ReqQueryBankAccountMoneyByStock(CKSOTPReqQueryAccountField *pReqQueryAccount, int nRequestID){}

///请求查询转帐流水
static PyObject* ReqQryTransferSerial(CKSOTPQryTransferSerialField *pQryTransferSerial, int nRequestID){}

///请求查询结算信息确认
static PyObject* ReqQrySettlementInfoConfirm(CKSOTPQrySettlementInfoConfirmField *pQrySettlementInfoConfirm, int nRequestID){}

///投资者结算结果确认
static PyObject* ReqSettlementInfoConfirm(CKSOTPSettlementInfoConfirmField *pSettlementInfoConfirm, int nRequestID){}

///请求查询投资者结算结果
static PyObject* ReqQrySettlementInfo(CKSOTPQrySettlementInfoField *pQrySettlementInfo, int nRequestID){}

///查询客户交易级别
static PyObject* ReqQryInvestorTradeLevel(CKSOTPQryInvestorTradeLevelField *pQryInvestorTradeLevel, int nRequestID){}

///查询个股限购额度
static PyObject* ReqQryPurchaseLimitAmt(CKSOTPQryPurchaseLimitAmtField *pQryPurchaseLimitAmt, int nRequestID){}

///查询个股限仓额度
static PyObject* ReqQryPositionLimitVol(CKSOTPQryPositionLimitVolField *pQryPositionLimitVol, int nRequestID){}

///请求查询历史报单
static PyObject* ReqQryHistoryOrder(CKSOTPQryHistoryOrderField *pQryHistoryOrder, int nRequestID){}

///请求查询历史成交
static PyObject* ReqQryHistoryTrade(CKSOTPQryHistoryTradeField *pQryHistoryTrade, int nRequestID){}

///请求查询历史行权指派明细
static PyObject* ReqQryHistoryAssignment(CKSOTPQryHistoryAssignmentField *pQryHistoryAssignment, int nRequestID){}

///请求查询行权交割明细
static PyObject* ReqQryDelivDetail(CKSOTPQryDelivDetailField *pQryDelivDetail, int nRequestID){}

///自动行权执行操作
static PyObject* ReqAutoExecOrderAction(CKSOTPAutoExecOrderActionField *pAutoExecOrderAction, int nRequestID){}