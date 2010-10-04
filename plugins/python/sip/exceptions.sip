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
// Shotgun::SgError
// *******************************************************************
%Exception Shotgun::SgError(SIP_Exception) /PyName=SgError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// Shotgun::SgAttrError
// *******************************************************************
%Exception Shotgun::SgAttrError(SIP_Exception) /PyName=SgAttrError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgAttrError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// Shotgun::SgAttrNotFoundError
// *******************************************************************
%Exception Shotgun::SgAttrNotFoundError(SIP_Exception) /PyName=SgAttrNotFoundError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgAttrNotFoundError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// Shotgun::SgAttrTypeError
// *******************************************************************
%Exception Shotgun::SgAttrTypeError(SIP_Exception) /PyName=SgAttrTypeError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgAttrTypeError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// Shotgun::SgAttrValueError
// *******************************************************************
%Exception Shotgun::SgAttrValueError(SIP_Exception) /PyName=SgAttrValueError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgAttrValueError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// Shotgun::SgAttrLinkError
// *******************************************************************
%Exception Shotgun::SgAttrLinkError(SIP_Exception) /PyName=SgAttrLinkError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgAttrLinkError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// Shotgun::SgAttrSetValueError
// *******************************************************************
%Exception Shotgun::SgAttrSetValueError(SIP_Exception) /PyName=SgAttrSetValueError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgAttrSetValueError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// Shotgun::SgEmptyAttrMapError
// *******************************************************************
%Exception Shotgun::SgEmptyAttrMapError(SIP_Exception) /PyName=SgEmptyAttrMapError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgEmptyAttrMapError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// Shotgun::SgEntityError
// *******************************************************************
%Exception Shotgun::SgEntityError(SIP_Exception) /PyName=SgEntityError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgEntityError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// Shotgun::SgEntityXmlrpcError
// *******************************************************************
%Exception Shotgun::SgEntityXmlrpcError(SIP_Exception) /PyName=SgEntityXmlrpcError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgEntityXmlrpcError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// Shotgun::SgEntityNotFoundError
// *******************************************************************
%Exception Shotgun::SgEntityNotFoundError(SIP_Exception) /PyName=SgEntityNotFoundError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgEntityNotFoundError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// Shotgun::SgEntityFunctionNotFoundError
// *******************************************************************
%Exception Shotgun::SgEntityFunctionNotFoundError(SIP_Exception) /PyName=SgEntityFunctionNotFoundError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgEntityFunctionNotFoundError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// Shotgun::SgEntityDynamicCastError
// *******************************************************************
%Exception Shotgun::SgEntityDynamicCastError(SIP_Exception) /PyName=SgEntityDynamicCastError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgEntityDynamicCastError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// Shotgun::SgEntityCreateError
// *******************************************************************
%Exception Shotgun::SgEntityCreateError(SIP_Exception) /PyName=SgEntityCreateError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgEntityCreateError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// Shotgun::SgApiError
// *******************************************************************
%Exception Shotgun::SgApiError(SIP_Exception) /PyName=SgApiError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgApiError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// Shotgun::SgXmlrpcValueError
// *******************************************************************
%Exception Shotgun::SgXmlrpcValueError(SIP_Exception) /PyName=SgXmlrpcValueError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgXmlrpcValueError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// Shotgun::SgXmlrpcValueTypeError
// *******************************************************************
%Exception Shotgun::SgXmlrpcValueTypeError(SIP_Exception) /PyName=SgXmlrpcValueTypeError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgXmlrpcValueTypeError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// Shotgun::SgXmlrpcValueIsNilError
// *******************************************************************
%Exception Shotgun::SgXmlrpcValueIsNilError(SIP_Exception) /PyName=SgXmlrpcValueIsNilError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgXmlrpcValueIsNilError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// Shotgun::SgListError
// *******************************************************************
%Exception Shotgun::SgListError(SIP_Exception) /PyName=SgListError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgListError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// Shotgun::SgDictError
// *******************************************************************
%Exception Shotgun::SgDictError(SIP_Exception) /PyName=SgDictError/
{
%TypeHeaderCode
#include <Shotgun/exceptions.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgDictError, detail);
        SIP_UNBLOCK_THREADS
%End
};


