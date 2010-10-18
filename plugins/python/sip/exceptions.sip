// *******************************************************************
// std::exception
// *******************************************************************
%Exception std::exception(SIP_Exception) /PyName=StdException/
{
%TypeHeaderCode
#include <exception>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_std_exception, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// std::runtime_error
// *******************************************************************
%Exception std::runtime_error(SIP_Exception) /PyName=StdRuntimeError/
{
%TypeHeaderCode
#include <stdexcept>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_std_runtime_error, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgError
// *******************************************************************
%Exception SG::SgError(SIP_Exception) /PyName=SgError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgAttrError
// *******************************************************************
%Exception SG::SgAttrError(SIP_Exception) /PyName=SgAttrError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgAttrError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgAttrNotFoundError
// *******************************************************************
%Exception SG::SgAttrNotFoundError(SIP_Exception) /PyName=SgAttrNotFoundError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgAttrNotFoundError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgAttrTypeError
// *******************************************************************
%Exception SG::SgAttrTypeError(SIP_Exception) /PyName=SgAttrTypeError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgAttrTypeError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgAttrValueError
// *******************************************************************
%Exception SG::SgAttrValueError(SIP_Exception) /PyName=SgAttrValueError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgAttrValueError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgAttrLinkError
// *******************************************************************
%Exception SG::SgAttrLinkError(SIP_Exception) /PyName=SgAttrLinkError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgAttrLinkError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgAttrSetValueError
// *******************************************************************
%Exception SG::SgAttrSetValueError(SIP_Exception) /PyName=SgAttrSetValueError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgAttrSetValueError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgEmptyAttrMapError
// *******************************************************************
%Exception SG::SgEmptyAttrMapError(SIP_Exception) /PyName=SgEmptyAttrMapError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgEmptyAttrMapError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgEntityError
// *******************************************************************
%Exception SG::SgEntityError(SIP_Exception) /PyName=SgEntityError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgEntityError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgEntityXmlrpcError
// *******************************************************************
%Exception SG::SgEntityXmlrpcError(SIP_Exception) /PyName=SgEntityXmlrpcError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgEntityXmlrpcError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgEntityNotFoundError
// *******************************************************************
%Exception SG::SgEntityNotFoundError(SIP_Exception) /PyName=SgEntityNotFoundError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgEntityNotFoundError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgEntityClassNotRegisteredError
// *******************************************************************
%Exception SG::SgEntityClassNotRegisteredError(SIP_Exception) /PyName=SgEntityClassNotRegisteredError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgEntityClassNotRegisteredError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgEntityDynamicCastError
// *******************************************************************
%Exception SG::SgEntityDynamicCastError(SIP_Exception) /PyName=SgEntityDynamicCastError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgEntityDynamicCastError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgEntityCreateError
// *******************************************************************
%Exception SG::SgEntityCreateError(SIP_Exception) /PyName=SgEntityCreateError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgEntityCreateError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgXmlrpcValueError
// *******************************************************************
%Exception SG::SgXmlrpcValueError(SIP_Exception) /PyName=SgXmlrpcValueError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgXmlrpcValueError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgXmlrpcValueTypeError
// *******************************************************************
%Exception SG::SgXmlrpcValueTypeError(SIP_Exception) /PyName=SgXmlrpcValueTypeError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgXmlrpcValueTypeError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgXmlrpcValueIsNilError
// *******************************************************************
%Exception SG::SgXmlrpcValueIsNilError(SIP_Exception) /PyName=SgXmlrpcValueIsNilError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgXmlrpcValueIsNilError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgListError
// *******************************************************************
%Exception SG::SgListError(SIP_Exception) /PyName=SgListError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgListError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgListIndexOutOfRangeError
// *******************************************************************
%Exception SG::SgListIndexOutOfRangeError(SIP_Exception) /PyName=SgListIndexOutOfRangeError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgListIndexOutOfRangeError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgListConversionError
// *******************************************************************
%Exception SG::SgListConversionError(SIP_Exception) /PyName=SgListConversionError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgListConversionError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgDictError
// *******************************************************************
%Exception SG::SgDictError(SIP_Exception) /PyName=SgDictError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgDictError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgDictKeyNotFoundError
// *******************************************************************
%Exception SG::SgDictKeyNotFoundError(SIP_Exception) /PyName=SgDictKeyNotFoundError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgDictKeyNotFoundError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// SG::SgDictConversionError
// *******************************************************************
%Exception SG::SgDictConversionError(SIP_Exception) /PyName=SgDictConversionError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_SG_SgDictConversionError, detail);
        SIP_UNBLOCK_THREADS
%End
};


