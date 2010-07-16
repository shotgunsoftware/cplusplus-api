//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$ 
//******************************************************************************

#ifndef __METHOD_H__
#define __METHOD_H__

#include <cstdlib>
#include <string>

#include <xmlrpc-c/girerr.hpp>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client.hpp>
#include <xmlrpc-c/client_transport.hpp>

#include <Shotgun/Type.h>

namespace Shotgun {

class Shotgun;

// *****************************************************************************
class Method
{
    friend class Shotgun;

protected:
    Method(Shotgun *sg, const std::string &methodName);
    virtual ~Method();

public:
    const std::string &methodName() const { return m_methodName; }
    MethodSignatures &signature(); 
    std::string &help();
    xmlrpc_c::value call();
    xmlrpc_c::value call(const xmlrpc_c::paramList &params);

protected:
    Shotgun *m_sg;
    std::string m_methodName;

    MethodSignatures m_signatures;
    std::string m_help;
};

} // End namespace Shotgun

#endif    // End #ifdef __METHOD_H__
