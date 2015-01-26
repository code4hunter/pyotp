#ifndef _trd_wrapper_h_
#define _trd_wrapper_h_

#include <Python.h>
#include <string>
#include "KSOTPTraderApi.h"

using namespace KingstarAPI;

class trd_imp public: CKSOTPTraderSpi
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
	
};

#endif