//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$ 
//******************************************************************************

#include <iostream>

#include <assert.h>

#include <Shotgun/Method.h>
#include <Shotgun/Shotgun.h>

namespace Shotgun {

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
    xmlrpc_c::paramList params;
    params.add(toXmlrpcValue(m_methodName));

    // RPC
    xmlrpc_c::carriageParm_curl0 myCarriageParm(m_sg->serverURL());
    xmlrpc_c::rpcPtr myRpcP(sigMethodName, params);
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
    xmlrpc_c::paramList params;
    params.add(toXmlrpcValue(m_methodName));

    // RPC
    xmlrpc_c::carriageParm_curl0 myCarriageParm(m_sg->serverURL());
    xmlrpc_c::rpcPtr myRpcP(helpMethodName, params);
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
    
    xmlrpc_c::paramList params;
    xmlrpc_c::carriageParm_curl0 myCarriageParm(m_sg->serverURL());
    xmlrpc_c::rpcPtr myRpcP(m_methodName, params);
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
xmlrpc_c::value Method::call(const xmlrpc_c::paramList &params)
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
    
#if 0
    xmlrpc_c::carriageParm_curl0 myCarriageParm(m_sg->serverURL());
    xmlrpc_c::rpcOutcome outcome;

    m_sg->client()->call(&myCarriageParm, m_methodName, params, &outcome);
    output = xmlrpc_c::value(outcome.getResult());
#else
    xmlrpc_c::carriageParm_curl0 myCarriageParm(m_sg->serverURL());
    xmlrpc_c::rpcPtr myRpcP(m_methodName, params);
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

} // End namespace Shotgun
