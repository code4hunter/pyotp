#include "KSOTPMdApi.h"
#include "md_wrapper.h"

#include <Python.h>

static PyObject* create_MdApi(PyObject* self, PyObject *args)
{
	char * pszFlowPath=NULL;
	bool bIsUsingUdp=false;
	bool bIsMulticast=false;

	PyArg_ParseTuple(args, "sbb", &pszFlowPath, &bIsUsingUdp, &bIsMulticast);
	CKSOTPMdApi *p = CKSOTPMdApi::CreateOTPMdApi(pszFlowPath, bIsUsingUdp, bIsMulticast);
	return PyInt_FromLong((long)p);
}

static PyObject* Md_Init(PyObject * self, PyObject * args)
{
	CKSOTPMdApi * handle = (CKSOTPMdApi *) PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	handle->Init();
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject* Md_Release(PyObject * self, PyObject * args)
{
	CKSOTPMdApi * handle = (CKSOTPMdApi *) PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	handle->Release();
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject* Md_GetTradingDay(PyObject * self, PyObject * args)
{
	CKSOTPMdApi * handle = (CKSOTPMdApi *) PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * ret = Py_BuildValue("s", user->GetTradingDay());
	return ret;
}

static PyObject* Md_RegisterFront(PyObject * self, PyObject * args)
{
	CKSOTPMdApi * handle = (CKSOTPMdApi *) PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * py_pszFrontAddress = PyTuple_GET_ITEM(args, 1);
	char* pszFrontAddress = PyString_AsString(py_pszFrontAddress);
	handle->RegisterFront(pszFrontAddress);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject* Md_RegisterSpi(PyObject * self, PyObject * args){
	CKSOTPMdApi * handle = (CKSOTPMdApi *) PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * py_pSpi = PyTuple_GET_ITEM(args, 1);
	CKSOTPMdApi* pSpi = new md_wrapper(py_pSpi);
	handle->RegisterSpi(pSpi);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject * Md_SubscribeMarketData(PyObject* self, PyObject * args)
{
	CKSOTPMdApi * user = (CKSOTPMdApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
	PyObject * instruments = PyTuple_GET_ITEM(args, 1);

	int l = PySequence_Length(instruments);
	char ** pp =(char**)calloc(l, sizeof(char *));
	int i;
	for (i=0; i<l; i++){
	pp[i] = PyString_AsString(PySequence_GetItem(instruments, i));
	}
	user->SubscribeMarketData(pp, l);

	free(pp);

	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject * Md_UnSubscribeMarketData(PyObject* self, PyObject * args)
{
  CKSOTPMdApi * user = (CKSOTPMdApi *)PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
  PyObject * instruments = PyTuple_GET_ITEM(args, 1);

  int l = PySequence_Length(instruments);
  char ** pp =(char**)calloc(l, sizeof(char *));
  int i;
  for (i=0; i<l; i++){
    pp[i] = PyString_AsString(PySequence_GetItem(instruments, i));
  }
  user->UnSubscribeMarketData(pp, l);
  
  free(pp);

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* Md_ReqUserLogin(PyObject * self, PyObject * args){
  CKSOTPMdApi * user = (CKSOTPMdApi *) PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
  PyObject * py_pReqUserLoginField = PyTuple_GET_ITEM(args, 1);
  CThostFtdcReqUserLoginField* pReqUserLoginField = from_CThostFtdcReqUserLoginField(py_pReqUserLoginField);
  PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
  int nRequestID = PyInt_AsLong(py_nRequestID);
  PyObject * ret = Py_BuildValue("i", user->ReqUserLogin(pReqUserLoginField, nRequestID));
  free(pReqUserLoginField);
  return ret;
}

static PyObject* Md_ReqUserLogout(PyObject * self, PyObject * args){
  CKSOTPMdApi * user = (CKSOTPMdApi *) PyInt_AsLong(PyTuple_GET_ITEM(args, 0));
  PyObject * py_pUserLogout = PyTuple_GET_ITEM(args, 1);
  CThostFtdcUserLogoutField* pUserLogout = from_CThostFtdcUserLogoutField(py_pUserLogout);
  PyObject * py_nRequestID = PyTuple_GET_ITEM(args, 2);
  int nRequestID = PyInt_AsLong(py_nRequestID);
  PyObject * ret = Py_BuildValue("i", user->ReqUserLogout(pUserLogout, nRequestID));
  free(pUserLogout);
  return ret;
}

extern "C" __declspec(dllexport) void init_otp_md()
{
	static PyMethodDef mbMethods[] = {
		{"create_MdApi", create_MdApi, METH_VARARGS},
		{"register_struct", register_struct, METH_VARARGS},
		{"ReqUserLogout", Md_ReqUserLogout, METH_VARARGS} ,
		{"UnSubscribeMarketData", Md_UnSubscribeMarketData, METH_VARARGS} ,
		{"RegisterFront", Md_RegisterFront, METH_VARARGS} ,
		{"Init", Md_Init, METH_VARARGS} ,
		{"ReqUserLogin", Md_ReqUserLogin, METH_VARARGS} ,
		{"Release", Md_Release, METH_VARARGS} ,
		{"GetTradingDay", Md_GetTradingDay, METH_VARARGS} ,
		{"SubscribeMarketData", Md_SubscribeMarketData, METH_VARARGS} ,
		{"RegisterSpi", Md_RegisterSpi, METH_VARARGS} ,
		{NULL, NULL, NULL}
   };

   PyObject *m = Py_InitModule("_otp_md", mbMethods);

   PyEval_InitThreads();
}