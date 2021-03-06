#include "KSOTPMdApi.h"
#include "md_wrapper.h"

#include <Python.h>

#include "..\py_tools.h"

static PyObject* create_MdApi(PyObject* self, PyObject *args)
{
	char * pszFlowPath = NULL;
	bool bIsUsingUdp = false;
	bool bIsMulticast = false;

	PyArg_ParseTuple(args, "sbb", &pszFlowPath, &bIsUsingUdp, &bIsMulticast);
	CKSOTPMdApi *p = CKSOTPMdApi::CreateOTPMdApi(pszFlowPath, bIsUsingUdp, bIsMulticast);
	return PyInt_FromLong((long)p);
}

static PyObject* Md_Init(PyObject * self, PyObject * args)
{
	CKSOTPMdApi * handle = (CKSOTPMdApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	handle->Init();
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject* Md_Release(PyObject * self, PyObject * args)
{
	CKSOTPMdApi * handle = (CKSOTPMdApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	handle->Release();
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject* Md_GetTradingDay(PyObject * self, PyObject * args)
{
	CKSOTPMdApi * handle = (CKSOTPMdApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	const char *buf = handle->GetTradingDay();
	if (buf != NULL)
	{
		PyObject * ret = Py_BuildValue("s", buf);
		return ret;
	}
	else
	{
		Py_INCREF(Py_None);
		return Py_None;
	}

}

static PyObject* Md_RegisterFront(PyObject * self, PyObject * args)
{
	CKSOTPMdApi * handle = (CKSOTPMdApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * py_pszFrontAddress = PyTuple_GET_ITEM(args, 1);
	char* pszFrontAddress = PyString_AsString(py_pszFrontAddress);
	handle->RegisterFront(pszFrontAddress);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject* Md_RegisterSpi(PyObject * self, PyObject * args){
	CKSOTPMdApi * handle = (CKSOTPMdApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * py_pSpi = PyTuple_GET_ITEM(args, 1);
	CKSOTPMdSpi* pSpi = new md_imp(py_pSpi);
	handle->RegisterSpi(pSpi);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject * Md_SubscribeMarketData(PyObject* self, PyObject * args)
{
	CKSOTPMdApi * handle = (CKSOTPMdApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * instruments = PyTuple_GET_ITEM(args, 1);

	int l = PySequence_Length(instruments);
	if (l > 0)
	{
		char ** pp = (char**)calloc(l, sizeof(char *));
		int i;
		for (i = 0; i < l; i++)
		{
			pp[i] = PyString_AsString(PySequence_GetItem(instruments, i));
		}
		PyObject * ret = Py_BuildValue("i", handle->SubscribeMarketData(pp, l));
		free(pp);
		return ret;
	}
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject * Md_UnSubscribeMarketData(PyObject* self, PyObject * args)
{
	CKSOTPMdApi * handle = (CKSOTPMdApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * instruments = PyTuple_GET_ITEM(args, 1);

	int l = PySequence_Length(instruments);
	if (l > 0)
	{
		char ** pp = (char**)calloc(l, sizeof(char *));
		int i;
		for (i = 0; i < l; i++)
		{
			pp[i] = PyString_AsString(PySequence_GetItem(instruments, i));
		}
		PyObject * ret = Py_BuildValue("i", handle->UnSubscribeMarketData(pp, l));
		free(pp);
		return ret;
	}
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject* Md_ReqUserLogin(PyObject * self, PyObject * args)
{
	CKSOTPMdApi * handle = (CKSOTPMdApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * map = PyTuple_GET_ITEM(args, 1);
	CKSOTPReqUserLoginField req;

	_get_map_string(map, "BrokerID", req.BrokerID, sizeof(req.BrokerID) - 1);
	_get_map_string(map, "UserID", req.UserID, sizeof(req.UserID) - 1);
	_get_map_string(map, "Password", req.Password, sizeof(req.Password) - 1);
	_get_map_string(map, "UserProductInfo", req.UserProductInfo, sizeof(req.UserProductInfo) - 1);
	_get_map_string(map, "MacAddress", req.MacAddress, sizeof(req.MacAddress) - 1);
	_get_map_string(map, "ClientIPAddress", req.ClientIPAddress, sizeof(req.ClientIPAddress) - 1);

	PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
	int nRequestID = PyInt_AsLong(py_nRequestID);
	PyObject * ret = Py_BuildValue("i", handle->ReqUserLogin(&req, nRequestID));
	return ret;
}

static PyObject* Md_ReqUserLogout(PyObject * self, PyObject * args)
{
	CKSOTPMdApi * handle = (CKSOTPMdApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * map = PyTuple_GET_ITEM(args, 1);
	CKSOTPUserLogoutField req;
	_get_map_string(map, "BrokerID", req.BrokerID, sizeof(req.BrokerID) - 1);
	_get_map_string(map, "UserID", req.UserID, sizeof(req.UserID) - 1);

	PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
	int nRequestID = PyInt_AsLong(py_nRequestID);
	PyObject * ret = Py_BuildValue("i", handle->ReqUserLogout(&req, nRequestID));
	return ret;
}

extern "C" __declspec(dllexport) void init_otp_md()
{
	static PyMethodDef mbMethods[] = {
		{ "create_MdApi", create_MdApi, METH_VARARGS },
		{ "ReqUserLogout", Md_ReqUserLogout, METH_VARARGS },
		{ "UnSubscribeMarketData", Md_UnSubscribeMarketData, METH_VARARGS },
		{ "RegisterFront", Md_RegisterFront, METH_VARARGS },
		{ "Init", Md_Init, METH_VARARGS },
		{ "ReqUserLogin", Md_ReqUserLogin, METH_VARARGS },
		{ "Release", Md_Release, METH_VARARGS },
		{ "GetTradingDay", Md_GetTradingDay, METH_VARARGS },
		{ "SubscribeMarketData", Md_SubscribeMarketData, METH_VARARGS },
		{ "RegisterSpi", Md_RegisterSpi, METH_VARARGS },
		{ NULL, NULL, NULL }
	};

	PyObject *m = Py_InitModule("_otp_md", mbMethods);

	PyEval_InitThreads();
}