#ifndef _py_tools_h_
#define _py_tools_h_

#include <Python.h>

char _get_map_char(PyObject *map, const char *key);

void _get_map_string(PyObject *map, const char *key, char *buf, int size);

double _get_map_double(PyObject *map, const char *key);

int _get_map_int(PyObject *map, const char *key);

#endif