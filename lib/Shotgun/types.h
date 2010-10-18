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

#ifndef __TYPE_H__
#define __TYPE_H__

#include <iostream>
#include <map>

#include <xmlrpc-c/base.hpp>

namespace SG {

class List;
class Dict;
class FilterBy;
class SortBy;
class Fields;

// *****************************************************************************
typedef std::vector<std::string> Strings;
typedef Strings MethodSignature;
typedef std::vector<Strings> MethodSignatures;
typedef std::map<std::string, xmlrpc_c::value> SgMap;
typedef std::vector<xmlrpc_c::value> SgArray;

// *****************************************************************************
/// Returns the string representation of "xmlrpc_c::value::type_t" type.
/// To download source for libxmlrpc, see http://xmlrpc-c.sourceforge.net/.
std::string xmlrpcValueTypeStr(const xmlrpc_c::value::type_t xmlrpcType);

// *****************************************************************************
// Converts a particular data type to xmlrpc_c::value type.
xmlrpc_c::value toXmlrpcValue(const char *in);
xmlrpc_c::value toXmlrpcValue(const std::string &in);
xmlrpc_c::value toXmlrpcValue(const int &in);
xmlrpc_c::value toXmlrpcValue(const double &in);
xmlrpc_c::value toXmlrpcValue(const bool &in);
xmlrpc_c::value toXmlrpcValue(const time_t &in);
xmlrpc_c::value toXmlrpcValue(const struct tm &in);
xmlrpc_c::value toXmlrpcValue(const SgArray &in);
xmlrpc_c::value toXmlrpcValue(const SgMap &in);
xmlrpc_c::value toXmlrpcValue(const Strings &in);
xmlrpc_c::value toXmlrpcValue(const MethodSignatures &in);
xmlrpc_c::value toXmlrpcValue(const List &in);
xmlrpc_c::value toXmlrpcValue(const Dict &in);
xmlrpc_c::value toXmlrpcValue(const FilterBy &in);
xmlrpc_c::value toXmlrpcValue(const SortBy &in);
xmlrpc_c::value toXmlrpcValue(const Fields &in);
xmlrpc_c::value toXmlrpcValue(const xmlrpc_c::value &in);

// *****************************************************************************
// Converts a xmlrpc_c::value type to a specified data type.
// The template approach won't work since xmlrpc_c::value has to be casted to a
// specific derived xmlrpc_c::value type first, which the compiler doesn't like.
void fromXmlrpcValue(const xmlrpc_c::value &value, char *out);
void fromXmlrpcValue(const xmlrpc_c::value &value, std::string &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, int &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, double &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, bool &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, time_t &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, struct tm &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, SgArray &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, SgMap &out);
// MethodSignatures is the same as Strings
void fromXmlrpcValue(const xmlrpc_c::value &value, Strings &out); 
void fromXmlrpcValue(const xmlrpc_c::value &value, List &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, Dict &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, FilterBy &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, SortBy &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, Fields &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, xmlrpc_c::value &out);

// *****************************************************************************
/// Utility function - returns a string representation of the current date.
/// It is in the format of "YYYY-MM-DD".
std::string currDateStr();

} // End namespace SG

// *****************************************************************************
// *****************************************************************************
// Returns a string representation of a given data type.
std::string toStdString(const int val);
std::string toStdString(const bool val);
std::string toStdString(const double val);
std::string toStdString(const time_t val);
std::string toStdString(const struct tm &val);
std::string toStdString(const xmlrpc_c::value &value);
std::string toStdString(const SG::SgArray &array);
std::string toStdString(const SG::SgMap &map);
std::string toStdString(const SG::Strings &strs);
std::string toStdString(const SG::MethodSignatures &sigs);

std::ostream &operator<<(std::ostream& output, const xmlrpc_c::value &value);
std::ostream &operator<<(std::ostream& output, const struct tm &time);
std::ostream &operator<<(std::ostream& output, const SG::SgMap &map);
std::ostream &operator<<(std::ostream& output, const SG::SgArray &array);
std::ostream &operator<<(std::ostream& output, const SG::Strings &strs);
std::ostream &operator<<(std::ostream& output, const SG::MethodSignatures &sigs);

#endif    // End #ifdef __TYPE_H__
