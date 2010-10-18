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

// ************************************************************************
//  std::string
//
//  Got this from the [PyQt] mailing list:
//  http://www.riverbankcomputing.com/pipermail/pyqt/2005-February/009662.html
// ************************************************************************

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
#include <time.h>
#include <datetime.h>
%End

%ConvertFromTypeCode
    // Convert a xmlrpc_c::value to a Python type

    // -------------------------------------------------------------------------
    // This line is IMPORTANT! - Otherwise, any PyDateTime calls will crash
    // -------------------------------------------------------------------------
    PyDateTime_IMPORT;

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
        //pObj = PyLong_FromLong(time_t(xmlrpc_c::value_datetime(*sipCpp)));

        time_t utcTime = time_t(xmlrpc_c::value_datetime(*sipCpp));
        struct tm localTime = *(localtime(&utcTime));

        pObj = PyDateTime_FromDateAndTime(localTime.tm_year + 1900,
                                          localTime.tm_mon + 1,
                                          localTime.tm_mday,
                                          localTime.tm_hour,
                                          localTime.tm_min,
                                          localTime.tm_sec,
                                          0);
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
    
    // -------------------------------------------------------------------------
    // This line is IMPORTANT! - Otherwise, any PyDateTime calls will crash
    // -------------------------------------------------------------------------
    PyDateTime_IMPORT;

    if (sipIsErr == NULL)
    {
        return (PyBool_Check(sipPy) || 
                PyInt_Check(sipPy) || 
                PyFloat_Check(sipPy) ||
                PyLong_Check(sipPy) ||
                PyString_Check(sipPy) ||
                PyDateTime_Check(sipPy) ||
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
    else if (PyDateTime_Check(sipPy))
    {
        time_t utcTime;
        struct tm localTime; 

        localTime.tm_year = PyDateTime_GET_YEAR(sipPy) - 1900;
        localTime.tm_mon = PyDateTime_GET_MONTH(sipPy) - 1;
        localTime.tm_mday = PyDateTime_GET_DAY(sipPy);
        localTime.tm_hour = PyDateTime_DATE_GET_HOUR(sipPy);
        localTime.tm_min = PyDateTime_DATE_GET_MINUTE(sipPy);
        localTime.tm_sec = PyDateTime_DATE_GET_SECOND(sipPy);

        utcTime = mktime(&localTime);

        *sipCppPtr = new xmlrpc_c::value(xmlrpc_c::value_datetime(time_t(utcTime)));
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
//  std::vector<std::string> - SG::Strings
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
//  std::vector< std::vector<std::string> >  
// ************************************************************************
%MappedType std::vector< std::vector<std::string> > // NOTE: need a whitespace between > >
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
//  std::vector<SG::Entity *> - SG::EntityPtrs
// ************************************************************************

%MappedType std::vector<SG::Entity *>
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
        SG::Entity *t = (*sipCpp)[i];
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_SG_Entity, sipTransferObj)) == NULL)
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
                       sipCanConvertToType(itm, sipType_SG_Entity, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<SG::Entity *> *stdVector = new std::vector<SG::Entity *>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        SG::Entity *t = reinterpret_cast<SG::Entity *>(
                                 sipConvertToType( itm,
                                                   sipType_SG_Entity,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_SG_Entity, state);

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
//  std::vector<SG::Project *> - SG::ProjectPtrs
// ************************************************************************

%MappedType std::vector<SG::Project *>
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
        SG::Project *t = (*sipCpp)[i];
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_SG_Project, sipTransferObj)) == NULL)
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
                       sipCanConvertToType(itm, sipType_SG_Project, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<SG::Project *> *stdVector = new std::vector<SG::Project *>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        SG::Project *t = reinterpret_cast<SG::Project *>(
                                 sipConvertToType( itm,
                                                   sipType_SG_Project,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_SG_Project, state);

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
//  std::vector<SG::Sequence *> - SG::SequencePtrs
// ************************************************************************

%MappedType std::vector<SG::Sequence *>
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
        SG::Sequence *t = (*sipCpp)[i];
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_SG_Sequence, sipTransferObj)) == NULL)
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
                       sipCanConvertToType(itm, sipType_SG_Sequence, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<SG::Sequence *> *stdVector = new std::vector<SG::Sequence *>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        SG::Sequence *t = reinterpret_cast<SG::Sequence *>(
                                 sipConvertToType( itm,
                                                   sipType_SG_Sequence,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_SG_Sequence, state);

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
//  std::vector<SG::Shot *> - SG::ShotPtrs
// ************************************************************************

%MappedType std::vector<SG::Shot *>
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
        SG::Shot *t = (*sipCpp)[i];
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_SG_Shot, sipTransferObj)) == NULL)
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
                       sipCanConvertToType(itm, sipType_SG_Shot, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<SG::Shot *> *stdVector = new std::vector<SG::Shot *>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        SG::Shot *t = reinterpret_cast<SG::Shot *>(
                                 sipConvertToType( itm,
                                                   sipType_SG_Shot,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_SG_Shot, state);

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
//  std::vector<SG::Version *> - SG::VersionPtrs
// ************************************************************************

%MappedType std::vector<SG::Version *>
{
%TypeHeaderCode
#include <vector>
#include <Shotgun/Version.h>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        SG::Version *t = (*sipCpp)[i];
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_SG_Version, sipTransferObj)) == NULL)
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
                       sipCanConvertToType(itm, sipType_SG_Version, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<SG::Version *> *stdVector = new std::vector<SG::Version *>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        SG::Version *t = reinterpret_cast<SG::Version *>(
                                 sipConvertToType( itm,
                                                   sipType_SG_Version,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_SG_Version, state);

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
//  std::vector<SG::HumanUser *> - SG::HumanUserPtrs
// ************************************************************************

%MappedType std::vector<SG::HumanUser *>
{
%TypeHeaderCode
#include <vector>
#include <Shotgun/HumanUser.h>
%End

%ConvertFromTypeCode
    PyObject *pList = NULL;

    if ((pList = PyList_New(sipCpp->size())) == NULL)
        return NULL;

    for (SIP_SSIZE_T i = 0; i < SIP_SSIZE_T(sipCpp->size()); ++i)
    {
        SG::HumanUser *t = (*sipCpp)[i];
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_SG_HumanUser, sipTransferObj)) == NULL)
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
                       sipCanConvertToType(itm, sipType_SG_HumanUser, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<SG::HumanUser *> *stdVector = new std::vector<SG::HumanUser *>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        SG::HumanUser *t = reinterpret_cast<SG::HumanUser *>(
                                 sipConvertToType( itm,
                                                   sipType_SG_HumanUser,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_SG_HumanUser, state);

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
//  std::vector<SG::Element *> - SG::ElementPtrs
// ************************************************************************

%MappedType std::vector<SG::Element *>
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
        SG::Element *t = (*sipCpp)[i];
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_SG_Element, sipTransferObj)) == NULL)
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
                       sipCanConvertToType(itm, sipType_SG_Element, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<SG::Element *> *stdVector = new std::vector<SG::Element *>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        SG::Element *t = reinterpret_cast<SG::Element *>(
                                 sipConvertToType( itm,
                                                   sipType_SG_Element,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_SG_Element, state);

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
//  std::vector<SG::Asset *> - SG::AssetPtrs
// ************************************************************************

%MappedType std::vector<SG::Asset *>
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
        SG::Asset *t = (*sipCpp)[i];
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_SG_Asset, sipTransferObj)) == NULL)
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
                       sipCanConvertToType(itm, sipType_SG_Asset, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<SG::Asset *> *stdVector = new std::vector<SG::Asset *>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        SG::Asset *t = reinterpret_cast<SG::Asset *>(
                                 sipConvertToType( itm,
                                                   sipType_SG_Asset,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_SG_Asset, state);

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
//  std::vector<SG::Delivery *> - SG::DeliveryPtrs
// ************************************************************************

%MappedType std::vector<SG::Delivery *>
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
        SG::Delivery *t = (*sipCpp)[i];
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_SG_Delivery, sipTransferObj)) == NULL)
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
                       sipCanConvertToType(itm, sipType_SG_Delivery, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<SG::Delivery *> *stdVector = new std::vector<SG::Delivery *>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        SG::Delivery *t = reinterpret_cast<SG::Delivery *>(
                                 sipConvertToType( itm,
                                                   sipType_SG_Delivery,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_SG_Delivery, state);

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
//  std::vector<SG::PublishEvent *> - SG::PublishEventPtrs
// ************************************************************************

%MappedType std::vector<SG::PublishEvent *>
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
        SG::PublishEvent *t = (*sipCpp)[i];
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_SG_PublishEvent, sipTransferObj)) == NULL)
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
                       sipCanConvertToType(itm, sipType_SG_PublishEvent, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<SG::PublishEvent *> *stdVector = new std::vector<SG::PublishEvent *>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        SG::PublishEvent *t = reinterpret_cast<SG::PublishEvent *>(
                                 sipConvertToType( itm,
                                                   sipType_SG_PublishEvent,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_SG_PublishEvent, state);

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
//  std::vector<SG::Review *> - SG::ReviewPtrs
// ************************************************************************

%MappedType std::vector<SG::Review *>
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
        SG::Review *t = (*sipCpp)[i];
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_SG_Review, sipTransferObj)) == NULL)
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
                       sipCanConvertToType(itm, sipType_SG_Review, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<SG::Review *> *stdVector = new std::vector<SG::Review *>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        SG::Review *t = reinterpret_cast<SG::Review *>(
                                 sipConvertToType( itm,
                                                   sipType_SG_Review,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_SG_Review, state);

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
//  std::vector<SG::ReviewItem *> - SG::ReviewItemPtrs
// ************************************************************************

%MappedType std::vector<SG::ReviewItem *>
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
        SG::ReviewItem *t = (*sipCpp)[i];
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_SG_ReviewItem, sipTransferObj)) == NULL)
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
                       sipCanConvertToType(itm, sipType_SG_ReviewItem, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<SG::ReviewItem *> *stdVector = new std::vector<SG::ReviewItem *>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        SG::ReviewItem *t = reinterpret_cast<SG::ReviewItem *>(
                                 sipConvertToType( itm,
                                                   sipType_SG_ReviewItem,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_SG_ReviewItem, state);

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
//  std::vector<SG::Task *> - SG::TaskPtrs
// ************************************************************************

%MappedType std::vector<SG::Task *>
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
        SG::Task *t = (*sipCpp)[i];
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_SG_Task, sipTransferObj)) == NULL)
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
                       sipCanConvertToType(itm, sipType_SG_Task, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<SG::Task *> *stdVector = new std::vector<SG::Task *>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        SG::Task *t = reinterpret_cast<SG::Task *>(
                                 sipConvertToType( itm,
                                                   sipType_SG_Task,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_SG_Task, state);

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
//  std::vector<SG::Group *> - SG::GroupPtrs
// ************************************************************************

%MappedType std::vector<SG::Group *>
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
        SG::Group *t = (*sipCpp)[i];
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_SG_Group, sipTransferObj)) == NULL)
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
                       sipCanConvertToType(itm, sipType_SG_Group, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<SG::Group *> *stdVector = new std::vector<SG::Group *>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        SG::Group *t = reinterpret_cast<SG::Group *>(
                                 sipConvertToType( itm,
                                                   sipType_SG_Group,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_SG_Group, state);

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
//  std::vector<SG::Note *> - SG::NotePtrs
// ************************************************************************

%MappedType std::vector<SG::Note *>
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
        SG::Note *t = (*sipCpp)[i];
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_SG_Note, sipTransferObj)) == NULL)
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
                       sipCanConvertToType(itm, sipType_SG_Note, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<SG::Note *> *stdVector = new std::vector<SG::Note *>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        SG::Note *t = reinterpret_cast<SG::Note *>(
                                 sipConvertToType( itm,
                                                   sipType_SG_Note,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_SG_Note, state);

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
//  std::vector<SG::Playlist *> - SG::PlaylistPtrs
// ************************************************************************

%MappedType std::vector<SG::Playlist *>
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
        SG::Playlist *t = (*sipCpp)[i];
        
        PyObject *pObj;

        if ((pObj = sipConvertFromNewType(t, sipType_SG_Playlist, sipTransferObj)) == NULL)
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
                       sipCanConvertToType(itm, sipType_SG_Playlist, SIP_NOT_NONE));

            Py_XDECREF(itm);

            if (!ok)
                return 0;
        }

        return 1;
    }

    std::vector<SG::Playlist *> *stdVector = new std::vector<SG::Playlist *>;
    len = PySequence_Size(sipPy);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
    {
        PyObject *itm = PySequence_ITEM(sipPy, i);
        int state;
        SG::Playlist *t = reinterpret_cast<SG::Playlist *>(
                                 sipConvertToType( itm,
                                                   sipType_SG_Playlist,
                                                   sipTransferObj,
                                                   SIP_NOT_NONE,
                                                   &state,
                                                   sipIsErr));

        Py_DECREF(itm);

        if (*sipIsErr)
        {
            sipReleaseType(t, sipType_SG_Playlist, state);

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
//
//    - EntityPtrs
//    - ProjectPtrs;
//    - SequencePtrs;
//    - ShotPtrs;
//    - VersionPtrs;
//    - HumanUserPtrs;
//    - ElementPtrs;
//    - AssetPtrs;
//    - DeliveryPtrs;
//    - PublishEventPtrs;
//    - ReviewPtrs;
//    - ReviewItemPtrs;
//    - TaskPtrs;
//    - GroupPtrs;
//    - NotePtrs;
//    - PlaylistPtrs;
//
// ************************************************************************

namespace SG {

typedef std::vector<std::string> Strings;

// --------------------------------------------------------------------
// In Python, the Entity object and its pointer are treated the same.
// --------------------------------------------------------------------
typedef std::vector<SG::Entity *> EntityPtrs;
typedef std::vector<SG::Project *> ProjectPtrs;
typedef std::vector<SG::Sequence *> SequencePtrs;
typedef std::vector<SG::Shot *> ShotPtrs;
typedef std::vector<SG::Version *> VersionPtrs;
typedef std::vector<SG::HumanUser *> HumanUserPtrs;
typedef std::vector<SG::Element *> ElementPtrs;
typedef std::vector<SG::Asset *> AssetPtrs;
typedef std::vector<SG::Delivery *> DeliveryPtrs;
typedef std::vector<SG::PublishEvent *> PublishEventPtrs;
typedef std::vector<SG::Review *> ReviewPtrs;
typedef std::vector<SG::ReviewItem *> ReviewItemPtrs;
typedef std::vector<SG::Task *> TaskPtrs;
typedef std::vector<SG::Group *> GroupPtrs;
typedef std::vector<SG::Note *> NotePtrs;
typedef std::vector<SG::Playlist *> PlaylistPtrs;

}; // End namespace SG


