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
#include <Shotgun/Type.h>
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
#include <Shotgun/Type.h>
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
#include <Shotgun/Type.h>
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
#include <Shotgun/Type.h>
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
#include <Shotgun/Type.h>
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
#include <Shotgun/Type.h>
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
#include <Shotgun/Type.h>
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
#include <Shotgun/Type.h>
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
#include <Shotgun/Type.h>
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
#include <Shotgun/Type.h>
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
#include <Shotgun/Type.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgEntityNotFoundError, detail);
        SIP_UNBLOCK_THREADS
%End
};

// *******************************************************************
// Shotgun::SgEntityDynamicCastError
// *******************************************************************
%Exception Shotgun::SgEntityDynamicCastError(SIP_Exception) /PyName=SgEntityDynamicCastError/
{
%TypeHeaderCode
#include <Shotgun/Type.h>
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
#include <Shotgun/Type.h>
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
#include <Shotgun/Type.h>
%End
%RaiseCode
        const char *detail = sipExceptionRef.what();

        SIP_BLOCK_THREADS
        PyErr_SetString(sipException_Shotgun_SgApiError, detail);
        SIP_UNBLOCK_THREADS
%End
};

