#include "py_tools.h"

char _get_map_char(PyObject *map, const char *key)
{
	PyObject * v = PyDict_GetItemString(map, key);
	if (v == NULL) return '\0';
	char *s = PyString_AsString(v);
	if (PyErr_Occurred() != NULL)
	{
		PyErr_Print();
		return '\0';
	}
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
	if (PyErr_Occurred() != NULL)
	{
		PyErr_Print();
		return;
	}
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
		PyErr_Print();
		ret = 0;
	}
	return ret;
}

int _get_map_int(PyObject *map, const char *key)
{
	PyObject * v = PyDict_GetItemString(map, key);
	if (v == NULL) return 0;
	int ret = PyInt_AsLong(v);
	if (PyErr_Occurred() != NULL)
	{
		PyErr_Print();
		ret = 0;
	}
	return ret;
}