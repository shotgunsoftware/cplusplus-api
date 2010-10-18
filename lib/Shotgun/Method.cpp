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

#include <iostream>

#include <assert.h>

#include <Shotgun/Method.h>
#include <Shotgun/Shotgun.h>

namespace SG {

// *****************************************************************************
Method::Method(Shotgun *sg, const std::string &methodName)
    : m_sg(sg), m_methodName(methodName)
{
    // Nothing
}

// *****************************************************************************
Method::~Method()
{
    // Nothing
}

// *****************************************************************************
MethodSignatures &Method::signature()
{
    std::string sigMethodName = std::string("system.methodSignature");

    // Prepare the parameters
    xmlrpc_c::paramList paramList;
    paramList.add(toXmlrpcValue(m_methodName));

    // RPC
    xmlrpc_c::carriageParm_curl0 myCarriageParm(m_sg->serverURL());
    xmlrpc_c::rpcPtr myRpcP(sigMethodName, paramList);
    myRpcP->call(&(*m_sg->client()), &myCarriageParm);    
    assert(myRpcP->isFinished());

    m_signatures.clear();

    if (myRpcP->isSuccessful())
    {
        xmlrpc_c::value_array const sigs = xmlrpc_c::value_array(myRpcP->getResult());

        for (size_t i = 0; i < sigs.size(); i++)
        {
            xmlrpc_c::value_array sig = xmlrpc_c::value_array(sigs.vectorValueValue()[i]);
            MethodSignature mySig;
            for (size_t j = 0; j < sig.size(); j++)
            {
                std::string arg = xmlrpc_c::value_string(sig.vectorValueValue()[j]);
                mySig.push_back(arg);
            }
     
            m_signatures.push_back(mySig);
        }
    }
    else
    {
        xmlrpc_c::fault const fault = myRpcP->getFault();
        throw SgEntityXmlrpcError(fault.getDescription());
    }

    return m_signatures;
}

// *****************************************************************************
std::string &Method::help()
{
    std::string helpMethodName = std::string("system.methodHelp");

    // Prepare the parameters
    xmlrpc_c::paramList paramList;
    paramList.add(toXmlrpcValue(m_methodName));

    // RPC
    xmlrpc_c::carriageParm_curl0 myCarriageParm(m_sg->serverURL());
    xmlrpc_c::rpcPtr myRpcP(helpMethodName, paramList);
    myRpcP->call(&(*m_sg->client()), &myCarriageParm);
    assert(myRpcP->isFinished());

    if (myRpcP->isSuccessful())
    {
        m_help = std::string(xmlrpc_c::value_string(myRpcP->getResult()));
    }
    else
    {
        xmlrpc_c::fault const fault = myRpcP->getFault();
        throw SgEntityXmlrpcError(fault.getDescription());
    }

    return m_help;
}


// *****************************************************************************
xmlrpc_c::value Method::call()
{
    xmlrpc_c::value output;
    
    xmlrpc_c::paramList paramList;
    xmlrpc_c::carriageParm_curl0 myCarriageParm(m_sg->serverURL());
    xmlrpc_c::rpcPtr myRpcP(m_methodName, paramList);
    myRpcP->call(&(*m_sg->client()), &myCarriageParm);
    assert(myRpcP->isFinished());

    if (myRpcP->isSuccessful())
    {
        output = xmlrpc_c::value(myRpcP->getResult());
    }
    else
    {
        xmlrpc_c::fault const fault = myRpcP->getFault();
        throw SgEntityXmlrpcError(fault.getDescription());
    }

    return output;
}

// *****************************************************************************
xmlrpc_c::value Method::call(const Dict &params)
{
    // Here are two ways of doing the RPC call. They return the
    // same result. The "m_sg->client()->call" seems very intuitive, but
    // the doc says that an ordinary client program does not use 
    // this method because it performs RPC via the methods of an
    // xmlrpc_c::rpc object.
    //
    // I think the advantages of using a xmlrpc_c::rpc object are 
    // the execution status of the RPC. Has it been started yet? 
    // Has it finished? Has an error prevented the RPC from executing? 

    xmlrpc_c::value output;
    
    xmlrpc_c::paramList paramList;

    // Add the authentication info and the arguments to the parameter list
    paramList.add(toXmlrpcValue(m_sg->authMap()));
    paramList.add(toXmlrpcValue(params));

#if 0
    xmlrpc_c::carriageParm_curl0 myCarriageParm(m_sg->serverURL());
    xmlrpc_c::rpcOutcome outcome;

    m_sg->client()->call(&myCarriageParm, m_methodName, paramList, &outcome);
    output = xmlrpc_c::value(outcome.getResult());
#else
    xmlrpc_c::carriageParm_curl0 myCarriageParm(m_sg->serverURL());
    xmlrpc_c::rpcPtr myRpcP(m_methodName, paramList);
    myRpcP->call(&(*m_sg->client()), &myCarriageParm);
    assert(myRpcP->isFinished());

    if (myRpcP->isSuccessful())
    {
        output = xmlrpc_c::value(myRpcP->getResult());
    }
    else
    {
        xmlrpc_c::fault const fault = myRpcP->getFault();
        throw SgEntityXmlrpcError(fault.getDescription());
    }
#endif

    return output;
}

} // End namespace SG
