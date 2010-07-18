/*
-----------------------------------------------------------------------------
Copyright (c) 2010 Tippett Studio
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
-----------------------------------------------------------------------------
*/
// Got this from the [PyQt] mailing list:
// http://www.riverbankcomputing.com/pipermail/pyqt/2005-February/009662.html

%MappedType std::string
{
%TypeHeaderCode
#include <string>
%End

%ConvertFromTypeCode
    // convert an std::string to a Python string
    // I removed the part that converts to a Python unicode string.
    PyObject* newstring;
    newstring = PyString_FromString(sipCpp->c_str());
    return newstring;
%End

%ConvertToTypeCode
    // Allow a Python string (or a unicode string) whenever a string is
    // expected.
    // If argument is a Unicode string, just decode it to UTF-8
    // If argument is a Python string, assume it's UTF-8
    if (sipIsErr == NULL)
    {
        return (PyString_Check(sipPy) || PyUnicode_Check(sipPy));
    }
    if (sipPy == Py_None)
    {
        *sipCppPtr = new std::string;
        return 1;
    }
    if (PyUnicode_Check(sipPy))
    {
        PyObject* s = PyUnicode_AsEncodedString(sipPy, "UTF-8", "");
        *sipCppPtr = new std::string(PyString_AS_STRING(s));
        Py_DECREF(s);
        return 1;
    }
    if (PyString_Check(sipPy))
    {
        *sipCppPtr = new std::string(PyString_AS_STRING(sipPy));
        return 1;
    }
    return 0;
%End
};

// ************************************************************************
//  time_t
// ************************************************************************

%MappedType time_t
{
%TypeHeaderCode
#include <time.h>
%End

%ConvertFromTypeCode
    PyObject* pTime;
    pTime = PyLong_FromLong(*sipCpp);  
    return pTime;
%End

%ConvertToTypeCode
    if (sipIsErr == NULL)
    {
        // Both Int & Long are eligible for being converted to time_t
        return (PyInt_Check(sipPy) || PyLong_Check(sipPy));
    }

    if (sipPy == Py_None)
    {
        *sipCppPtr = new long();
        return 1;
    }

    if (PyInt_Check(sipPy) || PyLong_Check(sipPy))
    {
        // Why on earth does this PyLong_AsLong(..) have different cases for its name?
        // All other objects have naming convention such as:
        //     - PyInt_AS_LONG
        //     - PyString_AS_STRING

        *sipCppPtr = new long(PyLong_AsLong(sipPy)); 
        return 1;
    }
    return 0;
%End
};

// ************************************************************************
//  size_t
// ************************************************************************

%MappedType size_t
{
%TypeHeaderCode
#include <glob.h>
%End

%ConvertFromTypeCode
    PyObject* pSize;
    pSize = PyLong_FromSize_t(*sipCpp);  
    return pSize;
%End

%ConvertToTypeCode
    if (sipIsErr == NULL)
    {
        return (PyInt_Check(sipPy));
    }

    if (sipPy == Py_None)
    {
        *sipCppPtr = new size_t();
        return 1;
    }

    if (PyInt_Check(sipPy))
    {
        *sipCppPtr = new size_t(PyInt_AS_LONG(sipPy)); 
        return 1;
    }
    return 0;
%End
};

// ************************************************************************
//  xmlrpc_c::value 
// ************************************************************************

%MappedType xmlrpc_c::value
{
%TypeHeaderCode
#include <xmlrpc-c/base.hpp>
%End

%ConvertFromTypeCode
    // Convert a xmlrpc_c::value to a Python type

    PyObject* pObj = NULL;

    if (sipCpp->type() == xmlrpc_c::value::TYPE_BOOLEAN)
    {
        pObj = PyBool_FromLong(bool(xmlrpc_c::value_boolean(*sipCpp)));
    }
    else if (sipCpp->type() == xmlrpc_c::value::TYPE_INT)
    {
        pObj = PyInt_FromLong(int(xmlrpc_c::value_int(*sipCpp)));
    }
    else if (sipCpp->type() == xmlrpc_c::value::TYPE_DOUBLE)
    {
        pObj = PyFloat_FromDouble(double(xmlrpc_c::value_double(*sipCpp)));
    }
    else if (sipCpp->type() == xmlrpc_c::value::TYPE_DATETIME)
    {
        pObj = PyLong_FromLong(time_t(xmlrpc_c::value_datetime(*sipCpp)));
    }
    else if (sipCpp->type() == xmlrpc_c::value::TYPE_STRING)
    {
        pObj = PyString_FromString((std::string(xmlrpc_c::value_string(*sipCpp))).c_str());
    }
    else if (sipCpp->type() == xmlrpc_c::value::TYPE_NIL)
    {
        pObj = Py_None;
    }
    else if (sipCpp->type() == xmlrpc_c::value::TYPE_ARRAY)
    {
        std::vector<xmlrpc_c::value> *array = NULL;

        try
        {
            array = new std::vector<xmlrpc_c::value>(xmlrpc_c::value_array(*sipCpp).vectorValueValue());
            pObj = sipConvertFromNewType(array, 
                                         sipType_std_vector_27000100xmlrpc_c_value, 
                                         sipTransferObj);
        }
        catch (...)
        {
            sipRaiseUnknownException();
            pObj = NULL;
        }

        delete array;
    }
    else if (sipCpp->type() == xmlrpc_c::value::TYPE_STRUCT)
    {
        std::map<std::string, xmlrpc_c::value> *map = NULL;

        try
        {
            map = new std::map<std::string, xmlrpc_c::value>(
                      std::map<std::string, xmlrpc_c::value>(xmlrpc_c::value_struct(*sipCpp)));
            pObj = sipConvertFromNewType(map, 
                                         sipType_std_map_27000100std_string_27000100xmlrpc_c_value, 
                                         sipTransferObj);
        }
        catch (...)
        {
            sipRaiseUnknownException();
            pObj = NULL;
        }

        delete map;
    }

    return pObj;
%End

%ConvertToTypeCode
    // Convert a Python type to a xmlrpc_c::value type

    if (sipIsErr == NULL)
    {
        return (PyBool_Check(sipPy) || 
                PyInt_Check(sipPy) || 
                PyFloat_Check(sipPy) ||
                PyLong_Check(sipPy) ||
                PyString_Check(sipPy) ||
                sipCanConvertToType(sipPy, sipType_std_vector_27000100xmlrpc_c_value, SIP_NOT_NONE) ||
                sipCanConvertToType(sipPy, sipType_std_map_27000100std_string_27000100xmlrpc_c_value, SIP_NOT_NONE) ||
                (sipPy == Py_None));
    }

    if (sipPy == Py_None)
    {
        *sipCppPtr = new xmlrpc_c::value(xmlrpc_c::value_nil());
        return 1;
    }

    // Put PyBool_Check in front of the PyInt_Check since bool type pass both checks
    if (PyBool_Check(sipPy))
    {
        *sipCppPtr = new xmlrpc_c::value(xmlrpc_c::value_boolean(bool(PyInt_AS_LONG(sipPy))));
        return 1;
    }
    else if (PyInt_Check(sipPy))
    {
        *sipCppPtr = new xmlrpc_c::value(xmlrpc_c::value_int(int(PyInt_AS_LONG(sipPy))));
        return 1;
    }
    else if (PyFloat_Check(sipPy))
    {
        *sipCppPtr = new xmlrpc_c::value(xmlrpc_c::value_double(double(PyFloat_AS_DOUBLE(sipPy))));
        return 1;
    }
    else if (PyLong_Check(sipPy))
    {
        // NOTE: this PyLong_AsLong(..) is named differently than the other similar functions
        *sipCppPtr = new xmlrpc_c::value(xmlrpc_c::value_datetime(time_t(PyLong_AsLong(sipPy))));
        return 1;
    }
    else if (PyString_Check(sipPy))
    {
        *sipCppPtr = new xmlrpc_c::value(xmlrpc_c::value_string(std::string(PyString_AS_STRING(sipPy))));
        return 1;
    }
    else if (sipCanConvertToType(sipPy, sipType_std_vector_27000100xmlrpc_c_value, SIP_NOT_NONE))
    {
        int state;
        std::vector<xmlrpc_c::value> *array = reinterpret_cast<std::vector<xmlrpc_c::value> *>(
                                                  sipConvertToType( sipPy,
                                                                    sipType_std_vector_27000100xmlrpc_c_value,
                                                                    sipTransferObj,
                                                                    SIP_NOT_NONE,
                                                                    &state,
                                                                    sipIsErr));
        if (*sipIsErr)
        {
            sipReleaseType(array, sipType_std_vector_27000100xmlrpc_c_value, state);
            return 0;
        }

        *sipCppPtr = new xmlrpc_c::value(xmlrpc_c::value_array(*array));
        return sipGetState(sipTransferObj);
    }
    else if (sipCanConvertToType(sipPy, sipType_std_map_27000100std_string_27000100xmlrpc_c_value, SIP_NOT_NONE))
    {
        int state;
        std::map<std::string, xmlrpc_c::value> *map = 
                                              reinterpret_cast<std::map<std::string, xmlrpc_c::value> *>(
                                                  sipConvertToType( sipPy,
                                                                    sipType_std_map_27000100std_string_27000100xmlrpc_c_value,
                                                                    sipTransferObj,
                                                                    SIP_NOT_NONE,
                                                                    &state,
                                                                    sipIsErr));
        if (*sipIsErr)
        {
            sipReleaseType(map, sipType_std_map_27000100std_string_27000100xmlrpc_c_value, state);
            return 0;
        }

        *sipCppPtr = new xmlrpc_c::value(xmlrpc_c::value_struct(*map));
        return sipGetState(sipTransferObj);

    }

    return 0;
%End
};

// ************************************************************************
//  std::vector<xmlrpc_c::value> 
// ************************************************************************

// Refer to /tip/rnd/3rdparty/managed/python/modules/pyqt/PyQt-x11-gpl-4.5.1/sip/QtCore/qlist.sip

%MappedType std::vector<xmlrpc_c::value>
{
%TypeHeaderCode
#include <vector>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    // Create the Python list of the correct length.
    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    // Go through each element in the C++ instance and convert it to the
    // corresponding Python object.
    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        xmlrpc_c::value *t = new xmlrpc_c::value((*sipCpp)[i]);
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_xmlrpc_c_value, sipTransferObj)) == NULL)
        {
            // There was an error so garbage collect the Python list.
            Py_DECREF(pList);
            delete t;

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    // Return the Python list.
    return pList;
%End

%ConvertToTypeCode
    SIP_SSIZE_T len;

    // See if we are just being asked to check the type of the Python object.
    if (sipIsErr == NULL)
    {
        // Check it is a list.
        if (!PySequence_Check(sipPy) || (len = PySequence_Size(sipPy)) < 0)
            return 0;

        // Now check each element of the list is of the type we expect.
        // The template is for a pointer type so we don't disallow None.
        for (SIP_SSIZE_T i = 0; i < len; ++i)
        {
            PyObject *itm = PySequence_ITEM(sipPy, i);
            bool ok = (itm &&
                       sipCanConvertToType(itm, sipType_xmlrpc_c_value, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    // Create the instance on the heap.
    std::vector<xmlrpc_c::value> *stdVector = new std::vector<xmlrpc_c::value>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        // Use the SIP API to convert the Python object to the
        // corresponding C++ instance.  Note that we apply any ownership
        // transfer to the list itself, not the individual elements.

        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        xmlrpc_c::value *t = reinterpret_cast<xmlrpc_c::value *>(
                                 sipConvertToType( itm,
                                                   sipType_xmlrpc_c_value,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_xmlrpc_c_value, state);

            // Tidy up.
            delete stdVector;

            // There is nothing on the heap.
            return 0;
        }

        // Add the pointer to the C++ instance.
        stdVector->push_back(*t);
    }

    // Return the instance on the heap.
    *sipCppPtr = stdVector;

    // Apply the normal transfer.
    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  std::vector<std::string> 
// ************************************************************************

%MappedType std::vector<std::string>
{
%TypeHeaderCode
#include <vector>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    // Create the Python list of the correct length.
    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    // Go through each element in the C++ instance and convert it to the
    // corresponding Python object.
    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        PyObject *pObj;

        if ((pObj = PyString_FromString((*sipCpp)[i].c_str())) == NULL)
        {
            Py_DECREF(pList);

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    // Return the Python list.
    return pList;
%End

%ConvertToTypeCode
    if (sipIsErr == NULL)
    {
        return (PySequence_Check(sipPy) && PySequence_Size(sipPy) >= 0);
    }

    std::vector<std::string> *stdVector = new std::vector<std::string>;
    SIP_SSIZE_T len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);

        if (!itm)
        {
            delete stdVector;
            *sipIsErr = 1;

            return 0;
        }

        stdVector->push_back(PyString_AS_STRING(itm));

        Py_DECREF(itm);
    }

    // Return the instance on the heap.
    *sipCppPtr = stdVector;

    // Apply the normal transfer.
    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  std::vector<std::vector<std::string>>  - std::vector<Strings>
// ************************************************************************
%MappedType std::vector< std::vector<std::string> > // NOTE: need a whitespace between > > in sip's syntax
{
%TypeHeaderCode
#include <vector>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        std::vector<std::string> *t = new std::vector<std::string>((*sipCpp)[i]);
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_std_vector_27000100std_string, sipTransferObj)) == NULL)
        {
            // There was an error so garbage collect the Python list.
            Py_DECREF(pList);
            delete t;

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    // Return the Python list.
    return pList;
%End

%ConvertToTypeCode
    SIP_SSIZE_T len;

    if (sipIsErr == NULL)
    {
        if (!PySequence_Check(sipPy) || (len = PySequence_Size(sipPy)) < 0)
            return 0;

        for (SIP_SSIZE_T i = 0; i < len; ++i)
        {
            PyObject *itm = PySequence_ITEM(sipPy, i);
            bool ok = (itm &&
                       sipCanConvertToType(itm, sipType_std_vector_27000100std_string, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    // NOTE: need a whitespace between > > in sip's syntax
    std::vector< std::vector<std::string> > *stdVector = new std::vector< std::vector<std::string> >;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        std::vector<std::string> *t = reinterpret_cast<std::vector<std::string> *>(
                                          sipConvertToType( itm,
                                                            sipType_std_vector_27000100std_string,
                                                            sipTransferObj,
                                                            SIP_NOT_NONE,
                                                            &state,
                                                            sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_std_vector_27000100std_string, state);

            delete stdVector;

            return 0;
        }

        stdVector->push_back(*t);
    }

    *sipCppPtr = stdVector;

    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  std::vector<Shotgun::Entity *> - Shotgun::EntityPtrs
// ************************************************************************

%MappedType std::vector<Shotgun::Entity *>
{
%TypeHeaderCode
#include <vector>
#include <Shotgun/Entity.h>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        Shotgun::Entity *t = (*sipCpp)[i];
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_Shotgun_Entity, sipTransferObj)) == NULL)
        {
            Py_DECREF(pList);
            delete t;

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    return pList;
%End

%ConvertToTypeCode
    SIP_SSIZE_T len;

    if (sipIsErr == NULL)
    {
        if (!PySequence_Check(sipPy) || (len = PySequence_Size(sipPy)) < 0)
            return 0;

        for (SIP_SSIZE_T i = 0; i < len; ++i)
        {
            PyObject *itm = PySequence_ITEM(sipPy, i);
            bool ok = (itm &&
                       sipCanConvertToType(itm, sipType_Shotgun_Entity, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<Shotgun::Entity *> *stdVector = new std::vector<Shotgun::Entity *>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        Shotgun::Entity *t = reinterpret_cast<Shotgun::Entity *>(
                                 sipConvertToType( itm,
                                                   sipType_Shotgun_Entity,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_Shotgun_Entity, state);

            delete stdVector;

            return 0;
        }

        stdVector->push_back(t);
    }

    *sipCppPtr = stdVector;

    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  std::vector<Shotgun::Project> 
// ************************************************************************

%MappedType std::vector<Shotgun::Project>
{
%TypeHeaderCode
#include <vector>
#include <Shotgun/Project.h>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        Shotgun::Project *t = new Shotgun::Project((*sipCpp)[i]);
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_Shotgun_Project, sipTransferObj)) == NULL)
        {
            Py_DECREF(pList);
            delete t;

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    return pList;
%End

%ConvertToTypeCode
    SIP_SSIZE_T len;

    if (sipIsErr == NULL)
    {
        if (!PySequence_Check(sipPy) || (len = PySequence_Size(sipPy)) < 0)
            return 0;

        for (SIP_SSIZE_T i = 0; i < len; ++i)
        {
            PyObject *itm = PySequence_ITEM(sipPy, i);
            bool ok = (itm &&
                       sipCanConvertToType(itm, sipType_Shotgun_Project, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<Shotgun::Project> *stdVector = new std::vector<Shotgun::Project>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        Shotgun::Project *t = reinterpret_cast<Shotgun::Project *>(
                                 sipConvertToType( itm,
                                                   sipType_Shotgun_Project,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_Shotgun_Project, state);

            delete stdVector;

            return 0;
        }

        stdVector->push_back(*t);
    }

    *sipCppPtr = stdVector;

    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  std::vector<Shotgun::Sequence> 
// ************************************************************************

%MappedType std::vector<Shotgun::Sequence>
{
%TypeHeaderCode
#include <vector>
#include <Shotgun/Sequence.h>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        Shotgun::Sequence *t = new Shotgun::Sequence((*sipCpp)[i]);
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_Shotgun_Sequence, sipTransferObj)) == NULL)
        {
            Py_DECREF(pList);
            delete t;

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    return pList;
%End

%ConvertToTypeCode
    SIP_SSIZE_T len;

    if (sipIsErr == NULL)
    {
        if (!PySequence_Check(sipPy) || (len = PySequence_Size(sipPy)) < 0)
            return 0;

        for (SIP_SSIZE_T i = 0; i < len; ++i)
        {
            PyObject *itm = PySequence_ITEM(sipPy, i);
            bool ok = (itm &&
                       sipCanConvertToType(itm, sipType_Shotgun_Sequence, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<Shotgun::Sequence> *stdVector = new std::vector<Shotgun::Sequence>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        Shotgun::Sequence *t = reinterpret_cast<Shotgun::Sequence *>(
                                 sipConvertToType( itm,
                                                   sipType_Shotgun_Sequence,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_Shotgun_Sequence, state);

            delete stdVector;

            return 0;
        }

        stdVector->push_back(*t);
    }

    *sipCppPtr = stdVector;

    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  std::vector<Shotgun::Shot> 
// ************************************************************************

%MappedType std::vector<Shotgun::Shot>
{
%TypeHeaderCode
#include <vector>
#include <Shotgun/Shot.h>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        Shotgun::Shot *t = new Shotgun::Shot((*sipCpp)[i]);
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_Shotgun_Shot, sipTransferObj)) == NULL)
        {
            Py_DECREF(pList);
            delete t;

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    return pList;
%End

%ConvertToTypeCode
    SIP_SSIZE_T len;

    if (sipIsErr == NULL)
    {
        if (!PySequence_Check(sipPy) || (len = PySequence_Size(sipPy)) < 0)
            return 0;

        for (SIP_SSIZE_T i = 0; i < len; ++i)
        {
            PyObject *itm = PySequence_ITEM(sipPy, i);
            bool ok = (itm &&
                       sipCanConvertToType(itm, sipType_Shotgun_Shot, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<Shotgun::Shot> *stdVector = new std::vector<Shotgun::Shot>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        Shotgun::Shot *t = reinterpret_cast<Shotgun::Shot *>(
                                 sipConvertToType( itm,
                                                   sipType_Shotgun_Shot,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_Shotgun_Shot, state);

            delete stdVector;

            return 0;
        }

        stdVector->push_back(*t);
    }

    *sipCppPtr = stdVector;

    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  std::vector<Shotgun::Daily> 
// ************************************************************************

%MappedType std::vector<Shotgun::Daily>
{
%TypeHeaderCode
#include <vector>
#include <Shotgun/Daily.h>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        Shotgun::Daily *t = new Shotgun::Daily((*sipCpp)[i]);
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_Shotgun_Daily, sipTransferObj)) == NULL)
        {
            Py_DECREF(pList);
            delete t;

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    return pList;
%End

%ConvertToTypeCode
    SIP_SSIZE_T len;

    if (sipIsErr == NULL)
    {
        if (!PySequence_Check(sipPy) || (len = PySequence_Size(sipPy)) < 0)
            return 0;

        for (SIP_SSIZE_T i = 0; i < len; ++i)
        {
            PyObject *itm = PySequence_ITEM(sipPy, i);
            bool ok = (itm &&
                       sipCanConvertToType(itm, sipType_Shotgun_Daily, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<Shotgun::Daily> *stdVector = new std::vector<Shotgun::Daily>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        Shotgun::Daily *t = reinterpret_cast<Shotgun::Daily *>(
                                 sipConvertToType( itm,
                                                   sipType_Shotgun_Daily,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_Shotgun_Daily, state);

            delete stdVector;

            return 0;
        }

        stdVector->push_back(*t);
    }

    *sipCppPtr = stdVector;

    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  std::vector<Shotgun::User> 
// ************************************************************************

%MappedType std::vector<Shotgun::User>
{
%TypeHeaderCode
#include <vector>
#include <Shotgun/User.h>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        Shotgun::User *t = new Shotgun::User((*sipCpp)[i]);
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_Shotgun_User, sipTransferObj)) == NULL)
        {
            Py_DECREF(pList);
            delete t;

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    return pList;
%End

%ConvertToTypeCode
    SIP_SSIZE_T len;

    if (sipIsErr == NULL)
    {
        if (!PySequence_Check(sipPy) || (len = PySequence_Size(sipPy)) < 0)
            return 0;

        for (SIP_SSIZE_T i = 0; i < len; ++i)
        {
            PyObject *itm = PySequence_ITEM(sipPy, i);
            bool ok = (itm &&
                       sipCanConvertToType(itm, sipType_Shotgun_User, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<Shotgun::User> *stdVector = new std::vector<Shotgun::User>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        Shotgun::User *t = reinterpret_cast<Shotgun::User *>(
                                 sipConvertToType( itm,
                                                   sipType_Shotgun_User,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_Shotgun_User, state);

            delete stdVector;

            return 0;
        }

        stdVector->push_back(*t);
    }

    *sipCppPtr = stdVector;

    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  std::vector<Shotgun::Element> 
// ************************************************************************

%MappedType std::vector<Shotgun::Element>
{
%TypeHeaderCode
#include <vector>
#include <Shotgun/Element.h>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        Shotgun::Element *t = new Shotgun::Element((*sipCpp)[i]);
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_Shotgun_Element, sipTransferObj)) == NULL)
        {
            Py_DECREF(pList);
            delete t;

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    return pList;
%End

%ConvertToTypeCode
    SIP_SSIZE_T len;

    if (sipIsErr == NULL)
    {
        if (!PySequence_Check(sipPy) || (len = PySequence_Size(sipPy)) < 0)
            return 0;

        for (SIP_SSIZE_T i = 0; i < len; ++i)
        {
            PyObject *itm = PySequence_ITEM(sipPy, i);
            bool ok = (itm &&
                       sipCanConvertToType(itm, sipType_Shotgun_Element, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<Shotgun::Element> *stdVector = new std::vector<Shotgun::Element>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        Shotgun::Element *t = reinterpret_cast<Shotgun::Element *>(
                                 sipConvertToType( itm,
                                                   sipType_Shotgun_Element,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_Shotgun_Element, state);

            delete stdVector;

            return 0;
        }

        stdVector->push_back(*t);
    }

    *sipCppPtr = stdVector;

    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  std::vector<Shotgun::Asset> 
// ************************************************************************

%MappedType std::vector<Shotgun::Asset>
{
%TypeHeaderCode
#include <vector>
#include <Shotgun/Asset.h>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        Shotgun::Asset *t = new Shotgun::Asset((*sipCpp)[i]);
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_Shotgun_Asset, sipTransferObj)) == NULL)
        {
            Py_DECREF(pList);
            delete t;

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    return pList;
%End

%ConvertToTypeCode
    SIP_SSIZE_T len;

    if (sipIsErr == NULL)
    {
        if (!PySequence_Check(sipPy) || (len = PySequence_Size(sipPy)) < 0)
            return 0;

        for (SIP_SSIZE_T i = 0; i < len; ++i)
        {
            PyObject *itm = PySequence_ITEM(sipPy, i);
            bool ok = (itm &&
                       sipCanConvertToType(itm, sipType_Shotgun_Asset, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<Shotgun::Asset> *stdVector = new std::vector<Shotgun::Asset>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        Shotgun::Asset *t = reinterpret_cast<Shotgun::Asset *>(
                                 sipConvertToType( itm,
                                                   sipType_Shotgun_Asset,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_Shotgun_Asset, state);

            delete stdVector;

            return 0;
        }

        stdVector->push_back(*t);
    }

    *sipCppPtr = stdVector;

    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  std::vector<Shotgun::Delivery> 
// ************************************************************************

%MappedType std::vector<Shotgun::Delivery>
{
%TypeHeaderCode
#include <vector>
#include <Shotgun/Delivery.h>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        Shotgun::Delivery *t = new Shotgun::Delivery((*sipCpp)[i]);
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_Shotgun_Delivery, sipTransferObj)) == NULL)
        {
            Py_DECREF(pList);
            delete t;

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    return pList;
%End

%ConvertToTypeCode
    SIP_SSIZE_T len;

    if (sipIsErr == NULL)
    {
        if (!PySequence_Check(sipPy) || (len = PySequence_Size(sipPy)) < 0)
            return 0;

        for (SIP_SSIZE_T i = 0; i < len; ++i)
        {
            PyObject *itm = PySequence_ITEM(sipPy, i);
            bool ok = (itm &&
                       sipCanConvertToType(itm, sipType_Shotgun_Delivery, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<Shotgun::Delivery> *stdVector = new std::vector<Shotgun::Delivery>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        Shotgun::Delivery *t = reinterpret_cast<Shotgun::Delivery *>(
                                 sipConvertToType( itm,
                                                   sipType_Shotgun_Delivery,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_Shotgun_Delivery, state);

            delete stdVector;

            return 0;
        }

        stdVector->push_back(*t);
    }

    *sipCppPtr = stdVector;

    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  std::vector<Shotgun::DeliveryItem> 
// ************************************************************************

%MappedType std::vector<Shotgun::DeliveryItem>
{
%TypeHeaderCode
#include <vector>
#include <Shotgun/DeliveryItem.h>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        Shotgun::DeliveryItem *t = new Shotgun::DeliveryItem((*sipCpp)[i]);
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_Shotgun_DeliveryItem, sipTransferObj)) == NULL)
        {
            Py_DECREF(pList);
            delete t;

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    return pList;
%End

%ConvertToTypeCode
    SIP_SSIZE_T len;

    if (sipIsErr == NULL)
    {
        if (!PySequence_Check(sipPy) || (len = PySequence_Size(sipPy)) < 0)
            return 0;

        for (SIP_SSIZE_T i = 0; i < len; ++i)
        {
            PyObject *itm = PySequence_ITEM(sipPy, i);
            bool ok = (itm &&
                       sipCanConvertToType(itm, sipType_Shotgun_DeliveryItem, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<Shotgun::DeliveryItem> *stdVector = new std::vector<Shotgun::DeliveryItem>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        Shotgun::DeliveryItem *t = reinterpret_cast<Shotgun::DeliveryItem *>(
                                 sipConvertToType( itm,
                                                   sipType_Shotgun_DeliveryItem,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_Shotgun_DeliveryItem, state);

            delete stdVector;

            return 0;
        }

        stdVector->push_back(*t);
    }

    *sipCppPtr = stdVector;

    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  std::vector<Shotgun::PublishEvent> 
// ************************************************************************

%MappedType std::vector<Shotgun::PublishEvent>
{
%TypeHeaderCode
#include <vector>
#include <Shotgun/PublishEvent.h>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        Shotgun::PublishEvent *t = new Shotgun::PublishEvent((*sipCpp)[i]);
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_Shotgun_PublishEvent, sipTransferObj)) == NULL)
        {
            Py_DECREF(pList);
            delete t;

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    return pList;
%End

%ConvertToTypeCode
    SIP_SSIZE_T len;

    if (sipIsErr == NULL)
    {
        if (!PySequence_Check(sipPy) || (len = PySequence_Size(sipPy)) < 0)
            return 0;

        for (SIP_SSIZE_T i = 0; i < len; ++i)
        {
            PyObject *itm = PySequence_ITEM(sipPy, i);
            bool ok = (itm &&
                       sipCanConvertToType(itm, sipType_Shotgun_PublishEvent, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<Shotgun::PublishEvent> *stdVector = new std::vector<Shotgun::PublishEvent>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        Shotgun::PublishEvent *t = reinterpret_cast<Shotgun::PublishEvent *>(
                                 sipConvertToType( itm,
                                                   sipType_Shotgun_PublishEvent,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_Shotgun_PublishEvent, state);

            delete stdVector;

            return 0;
        }

        stdVector->push_back(*t);
    }

    *sipCppPtr = stdVector;

    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  std::vector<Shotgun::Review> 
// ************************************************************************

%MappedType std::vector<Shotgun::Review>
{
%TypeHeaderCode
#include <vector>
#include <Shotgun/Review.h>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        Shotgun::Review *t = new Shotgun::Review((*sipCpp)[i]);
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_Shotgun_Review, sipTransferObj)) == NULL)
        {
            Py_DECREF(pList);
            delete t;

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    return pList;
%End

%ConvertToTypeCode
    SIP_SSIZE_T len;

    if (sipIsErr == NULL)
    {
        if (!PySequence_Check(sipPy) || (len = PySequence_Size(sipPy)) < 0)
            return 0;

        for (SIP_SSIZE_T i = 0; i < len; ++i)
        {
            PyObject *itm = PySequence_ITEM(sipPy, i);
            bool ok = (itm &&
                       sipCanConvertToType(itm, sipType_Shotgun_Review, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<Shotgun::Review> *stdVector = new std::vector<Shotgun::Review>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        Shotgun::Review *t = reinterpret_cast<Shotgun::Review *>(
                                 sipConvertToType( itm,
                                                   sipType_Shotgun_Review,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_Shotgun_Review, state);

            delete stdVector;

            return 0;
        }

        stdVector->push_back(*t);
    }

    *sipCppPtr = stdVector;

    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  std::vector<Shotgun::ReviewItem> 
// ************************************************************************

%MappedType std::vector<Shotgun::ReviewItem>
{
%TypeHeaderCode
#include <vector>
#include <Shotgun/ReviewItem.h>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        Shotgun::ReviewItem *t = new Shotgun::ReviewItem((*sipCpp)[i]);
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_Shotgun_ReviewItem, sipTransferObj)) == NULL)
        {
            Py_DECREF(pList);
            delete t;

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    return pList;
%End

%ConvertToTypeCode
    SIP_SSIZE_T len;

    if (sipIsErr == NULL)
    {
        if (!PySequence_Check(sipPy) || (len = PySequence_Size(sipPy)) < 0)
            return 0;

        for (SIP_SSIZE_T i = 0; i < len; ++i)
        {
            PyObject *itm = PySequence_ITEM(sipPy, i);
            bool ok = (itm &&
                       sipCanConvertToType(itm, sipType_Shotgun_ReviewItem, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<Shotgun::ReviewItem> *stdVector = new std::vector<Shotgun::ReviewItem>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        Shotgun::ReviewItem *t = reinterpret_cast<Shotgun::ReviewItem *>(
                                 sipConvertToType( itm,
                                                   sipType_Shotgun_ReviewItem,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_Shotgun_ReviewItem, state);

            delete stdVector;

            return 0;
        }

        stdVector->push_back(*t);
    }

    *sipCppPtr = stdVector;

    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  std::vector<Shotgun::Task> 
// ************************************************************************

%MappedType std::vector<Shotgun::Task>
{
%TypeHeaderCode
#include <vector>
#include <Shotgun/Task.h>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        Shotgun::Task *t = new Shotgun::Task((*sipCpp)[i]);
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_Shotgun_Task, sipTransferObj)) == NULL)
        {
            Py_DECREF(pList);
            delete t;

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    return pList;
%End

%ConvertToTypeCode
    SIP_SSIZE_T len;

    if (sipIsErr == NULL)
    {
        if (!PySequence_Check(sipPy) || (len = PySequence_Size(sipPy)) < 0)
            return 0;

        for (SIP_SSIZE_T i = 0; i < len; ++i)
        {
            PyObject *itm = PySequence_ITEM(sipPy, i);
            bool ok = (itm &&
                       sipCanConvertToType(itm, sipType_Shotgun_Task, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<Shotgun::Task> *stdVector = new std::vector<Shotgun::Task>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        Shotgun::Task *t = reinterpret_cast<Shotgun::Task *>(
                                 sipConvertToType( itm,
                                                   sipType_Shotgun_Task,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_Shotgun_Task, state);

            delete stdVector;

            return 0;
        }

        stdVector->push_back(*t);
    }

    *sipCppPtr = stdVector;

    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  std::vector<Shotgun::Group> 
// ************************************************************************

%MappedType std::vector<Shotgun::Group>
{
%TypeHeaderCode
#include <vector>
#include <Shotgun/Group.h>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        Shotgun::Group *t = new Shotgun::Group((*sipCpp)[i]);
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_Shotgun_Group, sipTransferObj)) == NULL)
        {
            Py_DECREF(pList);
            delete t;

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    return pList;
%End

%ConvertToTypeCode
    SIP_SSIZE_T len;

    if (sipIsErr == NULL)
    {
        if (!PySequence_Check(sipPy) || (len = PySequence_Size(sipPy)) < 0)
            return 0;

        for (SIP_SSIZE_T i = 0; i < len; ++i)
        {
            PyObject *itm = PySequence_ITEM(sipPy, i);
            bool ok = (itm &&
                       sipCanConvertToType(itm, sipType_Shotgun_Group, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<Shotgun::Group> *stdVector = new std::vector<Shotgun::Group>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        Shotgun::Group *t = reinterpret_cast<Shotgun::Group *>(
                                 sipConvertToType( itm,
                                                   sipType_Shotgun_Group,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_Shotgun_Group, state);

            delete stdVector;

            return 0;
        }

        stdVector->push_back(*t);
    }

    *sipCppPtr = stdVector;

    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  std::vector<Shotgun::Note> 
// ************************************************************************

%MappedType std::vector<Shotgun::Note>
{
%TypeHeaderCode
#include <vector>
#include <Shotgun/Note.h>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        Shotgun::Note *t = new Shotgun::Note((*sipCpp)[i]);
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_Shotgun_Note, sipTransferObj)) == NULL)
        {
            Py_DECREF(pList);
            delete t;

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    return pList;
%End

%ConvertToTypeCode
    SIP_SSIZE_T len;

    if (sipIsErr == NULL)
    {
        if (!PySequence_Check(sipPy) || (len = PySequence_Size(sipPy)) < 0)
            return 0;

        for (SIP_SSIZE_T i = 0; i < len; ++i)
        {
            PyObject *itm = PySequence_ITEM(sipPy, i);
            bool ok = (itm &&
                       sipCanConvertToType(itm, sipType_Shotgun_Note, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<Shotgun::Note> *stdVector = new std::vector<Shotgun::Note>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        Shotgun::Note *t = reinterpret_cast<Shotgun::Note *>(
                                 sipConvertToType( itm,
                                                   sipType_Shotgun_Note,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_Shotgun_Note, state);

            delete stdVector;

            return 0;
        }

        stdVector->push_back(*t);
    }

    *sipCppPtr = stdVector;

    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  std::vector<Shotgun::Reference> 
// ************************************************************************

%MappedType std::vector<Shotgun::Reference>
{
%TypeHeaderCode
#include <vector>
#include <Shotgun/Reference.h>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        Shotgun::Reference *t = new Shotgun::Reference((*sipCpp)[i]);
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_Shotgun_Reference, sipTransferObj)) == NULL)
        {
            Py_DECREF(pList);
            delete t;

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    return pList;
%End

%ConvertToTypeCode
    SIP_SSIZE_T len;

    if (sipIsErr == NULL)
    {
        if (!PySequence_Check(sipPy) || (len = PySequence_Size(sipPy)) < 0)
            return 0;

        for (SIP_SSIZE_T i = 0; i < len; ++i)
        {
            PyObject *itm = PySequence_ITEM(sipPy, i);
            bool ok = (itm &&
                       sipCanConvertToType(itm, sipType_Shotgun_Reference, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<Shotgun::Reference> *stdVector = new std::vector<Shotgun::Reference>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        Shotgun::Reference *t = reinterpret_cast<Shotgun::Reference *>(
                                 sipConvertToType( itm,
                                                   sipType_Shotgun_Reference,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_Shotgun_Reference, state);

            delete stdVector;

            return 0;
        }

        stdVector->push_back(*t);
    }

    *sipCppPtr = stdVector;

    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  std::vector<Shotgun::Playlist> 
// ************************************************************************

%MappedType std::vector<Shotgun::Playlist>
{
%TypeHeaderCode
#include <vector>
#include <Shotgun/Playlist.h>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        Shotgun::Playlist *t = new Shotgun::Playlist((*sipCpp)[i]);
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_Shotgun_Playlist, sipTransferObj)) == NULL)
        {
            Py_DECREF(pList);
            delete t;

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    return pList;
%End

%ConvertToTypeCode
    SIP_SSIZE_T len;

    if (sipIsErr == NULL)
    {
        if (!PySequence_Check(sipPy) || (len = PySequence_Size(sipPy)) < 0)
            return 0;

        for (SIP_SSIZE_T i = 0; i < len; ++i)
        {
            PyObject *itm = PySequence_ITEM(sipPy, i);
            bool ok = (itm &&
                       sipCanConvertToType(itm, sipType_Shotgun_Playlist, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<Shotgun::Playlist> *stdVector = new std::vector<Shotgun::Playlist>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        Shotgun::Playlist *t = reinterpret_cast<Shotgun::Playlist *>(
                                 sipConvertToType( itm,
                                                   sipType_Shotgun_Playlist,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_Shotgun_Playlist, state);

            delete stdVector;

            return 0;
        }

        stdVector->push_back(*t);
    }

    *sipCppPtr = stdVector;

    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  xmlrpc_c::paramList
// ************************************************************************

%MappedType xmlrpc_c::paramList
{
%TypeHeaderCode
#include <xmlrpc-c/base.hpp>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        xmlrpc_c::value *t = new xmlrpc_c::value((*sipCpp)[i]);
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_xmlrpc_c_value, sipTransferObj)) == NULL)
        {
            Py_DECREF(pList);
            delete t;

            return NULL;
        }

        PyList_SET_ITEM(pList, i, pObj);
    }

    return pList;
%End

%ConvertToTypeCode
    SIP_SSIZE_T len;

    if (sipIsErr == NULL)
    {
        if (!PySequence_Check(sipPy) || (len = PySequence_Size(sipPy)) < 0)
            return 0;

        for (SIP_SSIZE_T i = 0; i < len; ++i)
        {
            PyObject *itm = PySequence_ITEM(sipPy, i);
            bool ok = (itm &&
                       sipCanConvertToType(itm, sipType_xmlrpc_c_value, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    xmlrpc_c::paramList *paramL = new xmlrpc_c::paramList;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        xmlrpc_c::value *t = reinterpret_cast<xmlrpc_c::value *>(
                                 sipConvertToType( itm,
                                                   sipType_xmlrpc_c_value,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_xmlrpc_c_value, state);

            delete paramL;

            return 0;
        }

        paramL->add(*t);
    }

    *sipCppPtr = paramL;

    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  std::map<std::string, xmlrpc_c::value> 
// ************************************************************************

// Refer to /tip/rnd/3rdparty/managed/python/modules/pyqt/PyQt-x11-gpl-4.5.1/sip/QtCore/qmap.sip

%MappedType std::map<std::string, xmlrpc_c::value>
{
%TypeHeaderCode
#include <map>
%End

%ConvertFromTypeCode
    // Create the dictionary.
    PyObject *d = PyDict_New();

    if (!d)
        return NULL;

    // Set the dictionary elements.
    std::map<std::string, xmlrpc_c::value>::const_iterator i = sipCpp->begin();

    while (i != sipCpp->end())
    {
        std::string *t1 = new std::string((*i).first);
        xmlrpc_c::value *t2 = new xmlrpc_c::value((*i).second);

        PyObject *t1obj = sipConvertFromNewType(t1, sipType_std_string, sipTransferObj);
        PyObject *t2obj = sipConvertFromNewType(t2, sipType_xmlrpc_c_value, sipTransferObj);

        if (t1obj == NULL || t2obj == NULL || PyDict_SetItem(d, t1obj, t2obj) < 0)
        {
            Py_DECREF(d);

            if (t1obj)
            {
                Py_DECREF(t1obj);
            }
            else
            {
                delete t1;
            }

            if (t2obj)
            {
                Py_DECREF(t2obj);
            }
            else
            {
                delete t2;
            }

            return NULL;
        }

        Py_DECREF(t1obj);
        Py_DECREF(t2obj);

        ++i;
    }

    return d;
%End

%ConvertToTypeCode
    PyObject *t1obj, *t2obj;
    SIP_SSIZE_T i = 0;

    // Check the type if that is all that is required.
    if (sipIsErr == NULL)
    {
        if (!PyDict_Check(sipPy))
            return 0;

        while (PyDict_Next(sipPy, &i, &t1obj, &t2obj))
        {
            if (!sipCanConvertToType(t1obj, sipType_std_string, SIP_NOT_NONE))
                return 0;

            if (!sipCanConvertToType(t2obj, sipType_xmlrpc_c_value, SIP_NOT_NONE))
                return 0;
        }

        return 1;
    }

    std::map<std::string, xmlrpc_c::value> *stdMap = new std::map<std::string, xmlrpc_c::value>;

    while (PyDict_Next(sipPy, &i, &t1obj, &t2obj))
    {
        int state1, state2;

        std::string *t1 = reinterpret_cast<std::string *>(
                             sipConvertToType(t1obj, 
                                              sipType_std_string, 
                                              sipTransferObj, 
                                              SIP_NOT_NONE, 
                                              &state1, 
                                              sipIsErr));

        xmlrpc_c::value *t2 = reinterpret_cast<xmlrpc_c::value *>(
                                  sipConvertToType(t2obj, 
                                                   sipType_xmlrpc_c_value, 
                                                   sipTransferObj, 
                                                   SIP_NOT_NONE, 
                                                   &state2, 
                                                   sipIsErr));

        if (*sipIsErr)
        {
            sipReleaseType(t1, sipType_std_string, state1);
            sipReleaseType(t2, sipType_xmlrpc_c_value, state2);

            delete stdMap;
            return 0;
        }

        (*stdMap)[*t1] = *t2;

        sipReleaseType(t1, sipType_std_string, state1);
        sipReleaseType(t2, sipType_xmlrpc_c_value, state2);
    }

    *sipCppPtr = stdMap;

    return sipGetState(sipTransferObj);
%End
};

// ************************************************************************
//  typedefs:
//
//    - Strings
//    - MethodSignature
//    - MethodSignatures
//    - SgArray
//    - SgMap
//
//    - EntityPtrs
//    - Projects
//    - Sequences
//    - Shots
//    - Dailies
//    - Users
//    - Elements
//    - Assets
//    - Deliveries
//    - DeliveryItems
//    - PublishEvents
//    - Reviews
//    - ReviewItems
//    - Tasks
//    - Groups
//    - Notes
//    - References
//    - Playlists
//
// ************************************************************************

namespace Shotgun {

typedef std::vector<std::string> Strings;
typedef std::vector<std::string> MethodSignature;
typedef std::vector< std::vector<std::string> > MethodSignatures;
typedef std::vector<xmlrpc_c::value> SgArray;
typedef std::map<std::string, xmlrpc_c::value> SgMap;
typedef std::vector<Shotgun::Entity *> EntityPtrs;
typedef std::vector<Shotgun::Project> Projects;
typedef std::vector<Shotgun::Sequence> Sequences;
typedef std::vector<Shotgun::Shot> Shots;
typedef std::vector<Shotgun::Daily> Dailies;
typedef std::vector<Shotgun::User> Users;
typedef std::vector<Shotgun::Element> Elements;
typedef std::vector<Shotgun::Asset> Assets;
typedef std::vector<Shotgun::Delivery> Deliveries;
typedef std::vector<Shotgun::DeliveryItem> DeliveryItems;
typedef std::vector<Shotgun::PublishEvent> PublishEvents;
typedef std::vector<Shotgun::Review> Reviews;
typedef std::vector<Shotgun::ReviewItem> ReviewItems;
typedef std::vector<Shotgun::Task> Tasks;
typedef std::vector<Shotgun::Group> Groups;
typedef std::vector<Shotgun::Note> Notes;
typedef std::vector<Shotgun::Reference> References;
typedef std::vector<Shotgun::Playlist> Playlists;

};


