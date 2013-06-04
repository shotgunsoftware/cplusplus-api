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

#ifndef __SG_METHOD_H__
#define __SG_METHOD_H__

#include <cstdlib>
#include <string>

//#include <curlpp/curlpp.hpp>
//#include <curlpp/Easy.hpp>
//#include <curlpp/Options.hpp>
#include <json/json.h>
#include <curl/curl.h>
#include <Shotgun/config.h>
#include <Shotgun/exceptions.h>

namespace SG {

class Shotgun;

// *****************************************************************************
/*! 
 \class Method
 A Method class is a container for a Shotgun API function through which programs
 access Shotgun via XML-RPC (http://xmlrpc-c.sourceforge.net/). All Method objects
 have to be initiated by a Shotgun object. Valid Shotgun API functions are:

    - system.listMethods
    - system.methodSignature
    - system.methodHelp
    - create
    - read
    - update
    - delete
    - schema_entity_create
    - schema_entity_read
    - schema_entity_update
    - schema_entity_delete
    - schema_field_create
    - schema_field_read
    - schema_field_update
    - schema_field_delete
    - schema_read

 \htmlonly
 All Shotgun API functions and arguments are case-sensitive. <br>

 All Shotgun API functions have the signature: <br>
 <pre>
    struct function_name(struct <b>auth_args</b>, struct <b>args</b>)
 </pre>
 where: <br>
     <br>
     <b>auth_args</b> is a struct containing information to authenticate the 
     script with Shotgun.  Format:

     <pre>
     auth_args = { <br> 
         'script_name': string, # Corresponds to "Script Name" on the [Admin] > [Scripts] page. <br>
         'script_key': string   # Corresponds to ""Application Key" <br>
     }
     </pre>

     <b>args</b> is a struct of the function's arguments. <br>

     <br>
     All functions return a struct as the result.  General format:
     <pre>
     { <br>
         'results' = { <br>
             ... <br>
         } <br>
     }
     </pre>
 \endhtmlonly

 In this Shotgun library, only the CRUD functions (create, read, update, delete) are used.
*/
class SG_API Method
{
    friend class Shotgun;

protected:
    /// A constructor.
    ///
    /// \param sg - instantiated Shotgun object pointer
    /// \param methodName - name of a Shotgun API function. 
    Method(Shotgun *sg, const std::string &methodName);

    /// A destructor that does nothing.
    virtual ~Method();

	// Creates the default curl request
	/*std::auto_ptr<curlpp::Easy> createRequest();*/

public:
    /// Returns the name of the Shotgun API function.
    const std::string &methodName() const { return m_methodName; }

    /// Returns the usage of the Shotgun API function.
    /// It throws a SgEntityJsonrpcError exception if the XML-RPC call fails.
    std::string serverCapabilities();

    /// Calls the Shotgun API function without any argument.
    /// It throws a SgEntityJsonrpcError exception if the XML-RPC call fails.
    /// \return a struct as the result.
	Json::Value call();

    /// Calls the Shotgun API function with a struct of arguments.
    /// It throws a SgEntityJsonrpcError exception if the XML-RPC call fails.
    /// \return a struct as the result.
	Json::Value call(const Dict &params);

protected:
    Shotgun *m_sg; ///< The instantiated Shotgun object pointer.
    std::string m_methodName; ///< The name of the Shotgun API function.

    MethodSignatures m_signatures; ///< The signature of the Shotgun API function.
    std::string m_help; ///< The usage string of the Shotgun API function.
};

} // End namespace SG

#endif    // End #ifdef __SG_METHOD_H__
