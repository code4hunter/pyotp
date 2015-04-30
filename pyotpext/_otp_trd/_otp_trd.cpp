#include "KSOTPTraderApi.h"
#include "trd_wrapper.h"

#include <Python.h>

#include "..\py_tools.h"

using namespace KingstarAPI;

///����TraderApi
///@return ��������UserApi
///@param pszFlowPath ����������Ϣ�ļ���Ŀ¼��Ĭ��Ϊ��ǰĿ¼
static PyObject* CreateTrdApi(PyObject* self, PyObject *args)
{
	char * pszFlowPath=NULL;
	PyArg_ParseTuple(args, "s", &pszFlowPath);
	CKSOTPTraderApi *p = CKSOTPTraderApi::CreateOTPTraderApi(pszFlowPath);
	return PyInt_FromLong((long)(void*)p);
}

///ɾ���ӿڶ�����
///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
static PyObject* Release(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *) PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	handle->Release();
	Py_INCREF(Py_None);
	return Py_None;
}

///��ʼ��
///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
static PyObject* Init(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *) PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	handle->Init();
	Py_INCREF(Py_None);
	return Py_None;
}

///��ȡ��ǰ������
///@return ��ȡ���Ľ�����
///@remark ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ�����
static PyObject* GetTradingDay(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *) PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * ret = Py_BuildValue("s", handle->GetTradingDay());
	return ret;
}

///ע��ǰ�û������ַ
///@param pszFrontAddress��ǰ�û������ַ.
///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:17001��. 
///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ.��17001������������˿ں�.
static PyObject* RegisterFront(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *) PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * py_pszFrontAddress = PyTuple_GET_ITEM(args, 1);
	char* pszFrontAddress = PyString_AsString(py_pszFrontAddress);
	handle->RegisterFront(pszFrontAddress);
	Py_INCREF(Py_None);
	return Py_None;
}

///ע��ص��ӿ�
///@param pSpi �����Իص��ӿ����ʵ��
static PyObject* RegisterSpi(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *) PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * py_pSpi = PyTuple_GET_ITEM(args, 1);
	CKSOTPTraderSpi *imp = new trd_imp(py_pSpi); 
	handle->RegisterSpi(imp);
	Py_INCREF(Py_None);
	return Py_None;
}

///����˽����.
///@param nResumeType ˽�����ش���ʽ  
///        THOST_TERT_RESTART:�ӱ������տ�ʼ�ش�
///        THOST_TERT_RESUME:���ϴ��յ�������
///        THOST_TERT_QUICK:ֻ���͵�¼��˽����������
///@remark �÷���Ҫ��Init����ǰ����.���������򲻻��յ�˽����������.
static PyObject* SubscribePrivateTopic(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	KSOTP_TE_RESUME_TYPE nResumeType = (KSOTP_TE_RESUME_TYPE)PyInt_AsLong(PyTuple_GET_ITEM(args, 1));
	handle->SubscribePrivateTopic(nResumeType);
	Py_INCREF(Py_None);
	return Py_None;
}

///���Ĺ�����.
///@param nResumeType �������ش���ʽ  
///        THOST_TERT_RESTART:�ӱ������տ�ʼ�ش�
///        THOST_TERT_RESUME:���ϴ��յ�������
///        THOST_TERT_QUICK:ֻ���͵�¼�󹫹���������
///@remark �÷���Ҫ��Init����ǰ����.���������򲻻��յ�������������.
static PyObject* SubscribePublicTopic(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	KSOTP_TE_RESUME_TYPE nResumeType = (KSOTP_TE_RESUME_TYPE)PyInt_AsLong(PyTuple_GET_ITEM(args, 1));
	handle->SubscribePublicTopic(nResumeType);
	Py_INCREF(Py_None);
	return Py_None;
}

///�û���¼����
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

///�ǳ�����
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

///����¼������
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
	req.Direction = _get_map_char(map, "Direction");

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

///������������
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

///�����ѯ����
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

///�����ѯ�ɽ�
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

///�����ѯͶ���ֲ߳�
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

///�����ѯ�ʽ��˻�
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

///�����ѯͶ����
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

///�����ѯ��Լ
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

///�����ѯͶ���ֲ߳���ϸ
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

///��ѯ������Ȩ������������
static PyObject* ReqQryOTPInsCommRate(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * map = PyTuple_GET_ITEM(args, 1);
	CKSOTPQryOTPInsCommRateField req;

	_get_map_string(map, "BrokerID", req.BrokerID, sizeof(req.BrokerID));
	_get_map_string(map, "InvestorID", req.InvestorID, sizeof(req.InvestorID));
	_get_map_string(map, "InstrumentID", req.InstrumentID, sizeof(req.InstrumentID));
	_get_map_string(map, "ExchangeID", req.ExchangeID, sizeof(req.ExchangeID));

	PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
	int nRequestID = PyInt_AsLong(py_nRequestID);

	PyObject * ret = Py_BuildValue("i", handle->ReqQryOTPInsCommRate(&req, nRequestID));
	return ret;
}

///��ѯ������Ȩ��֤��������
static PyObject* ReqQryOTPInsMarginRate(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * map = PyTuple_GET_ITEM(args, 1);
	CKSOTPQryInstrumentMarginRateField req;

	_get_map_string(map, "BrokerID", req.BrokerID, sizeof(req.BrokerID));
	_get_map_string(map, "InvestorID", req.InvestorID, sizeof(req.InvestorID));
	_get_map_string(map, "InstrumentID", req.InstrumentID, sizeof(req.InstrumentID));
	_get_map_string(map, "ExchangeID", req.ExchangeID, sizeof(req.ExchangeID));
	req.HedgeFlag = _get_map_char(map, "HedgeFlag");

	PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
	int nRequestID = PyInt_AsLong(py_nRequestID);

	PyObject * ret = Py_BuildValue("i", handle->ReqQryInstrumentMarginRate(&req, nRequestID));
	return ret;
}

///Ͷ���߽�����ȷ��
static PyObject* ReqSettlementInfoConfirm(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * map = PyTuple_GET_ITEM(args, 1);
	CKSOTPSettlementInfoConfirmField req;

	_get_map_string(map, "BrokerID", req.BrokerID, sizeof(req.BrokerID));
	_get_map_string(map, "InvestorID", req.InvestorID, sizeof(req.InvestorID));
	_get_map_string(map, "ConfirmDate", req.ConfirmDate, sizeof(req.ConfirmDate));
	_get_map_string(map, "ConfirmTime", req.ConfirmTime, sizeof(req.ConfirmTime));
	PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
	int nRequestID = PyInt_AsLong(py_nRequestID);

	PyObject * ret = Py_BuildValue("i", handle->ReqSettlementInfoConfirm(&req, nRequestID));
	return ret;
}

///�����ѯͶ���߽�����
static PyObject* ReqQrySettlementInfo(PyObject* self, PyObject *args)
{
	CKSOTPTraderApi * handle = (CKSOTPTraderApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * map = PyTuple_GET_ITEM(args, 1);
	CKSOTPQrySettlementInfoField req;

	_get_map_string(map, "BrokerID", req.BrokerID, sizeof(req.BrokerID));
	_get_map_string(map, "InvestorID", req.InvestorID, sizeof(req.InvestorID));
	_get_map_string(map, "TradingDay", req.TradingDay, sizeof(req.TradingDay));

	PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
	int nRequestID = PyInt_AsLong(py_nRequestID);

	PyObject * ret = Py_BuildValue("i", handle->ReqQrySettlementInfo(&req, nRequestID));
	return ret;
}

///��ѯ�ͻ����׼���
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
		{ "ReqSettlementInfoConfirm", ReqSettlementInfoConfirm, METH_VARARGS },
		{ "ReqQrySettlementInfo", ReqQrySettlementInfo, METH_VARARGS },
		{ NULL, NULL, NULL }
	};

	PyObject *m = Py_InitModule("_otp_trd", mbMethods);

	PyEval_InitThreads();
}