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

#ifndef __SG_TYPES_H__
#define __SG_TYPES_H__

#include <iostream>
#include <map>

#include <json/json.h>

#include <Shotgun/config.h>


namespace SG {

class List;
class Dict;
class FilterBy;
class SortBy;
class Fields;

// *****************************************************************************
typedef std::vector<std::string> Strings;
typedef Strings MethodSignature;
typedef std::vector<MethodSignature> MethodSignatures;

// *****************************************************************************
/// Returns the string representation of "Json::Value::type_t" type.
std::string jsonrpcValueTypeStr(const Json::ValueType jsonrpcType);

// *****************************************************************************
// Converts a particular data type to Json::Value type.
Json::Value toJsonrpcValue(const char *in);
Json::Value toJsonrpcValue(const std::string &in);
Json::Value toJsonrpcValue(const int &in);
Json::Value toJsonrpcValue(const double &in);
Json::Value toJsonrpcValue(const bool &in);
//Json::Value toJsonrpcValue(const time_t &in);
//Json::Value toJsonrpcValue(const struct tm &in);
Json::Value toJsonrpcValue(const std::vector<Json::Value> &in);
Json::Value toJsonrpcValue(const std::map<std::string, Json::Value> &in);
Json::Value toJsonrpcValue(const Strings &in);
Json::Value toJsonrpcValue(const MethodSignatures &in);
Json::Value toJsonrpcValue(const List &in);
Json::Value toJsonrpcValue(const Dict &in);
Json::Value toJsonrpcValue(const FilterBy &in);
Json::Value toJsonrpcValue(const SortBy &in);
Json::Value toJsonrpcValue(const Fields &in);
Json::Value toJsonrpcValue(const Json::Value &in);

// *****************************************************************************
// Converts a Json::Value type to a specified data type.
// The template approach won't work since Json::Value has to be casted to a
// specific derived Json::Value type first, which the compiler doesn't like.
void fromJsonrpcValue(const Json::Value &value, char *out);
void fromJsonrpcValue(const Json::Value &value, std::string &out);
void fromJsonrpcValue(const Json::Value &value, int &out);
void fromJsonrpcValue(const Json::Value &value, double &out);
void fromJsonrpcValue(const Json::Value &value, bool &out);
//void fromJsonrpcValue(const Json::Value &value, time_t &out);
//void fromJsonrpcValue(const Json::Value &value, struct tm &out);
void fromJsonrpcValue(const Json::Value &value, std::vector<Json::Value> &out);
void fromJsonrpcValue(const Json::Value &value, std::map<std::string, Json::Value> &out);
void fromJsonrpcValue(const Json::Value &value, Strings &out); 
void fromJsonrpcValue(const Json::Value &value, List &out);
void fromJsonrpcValue(const Json::Value &value, Dict &out);
void fromJsonrpcValue(const Json::Value &value, FilterBy &out);
void fromJsonrpcValue(const Json::Value &value, SortBy &out);
void fromJsonrpcValue(const Json::Value &value, Fields &out);
void fromJsonrpcValue(const Json::Value &value, Json::Value &out);

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
//std::string toStdString(const time_t val);
//std::string toStdString(const struct tm &val);
std::string toStdString(const Json::Value &value);
std::string toStdString(const std::vector<Json::Value> &a);
std::string toStdString(const std::map<std::string, Json::Value> &map);
std::string toStdString(const SG::Strings &strs);
std::string toStdString(const SG::MethodSignatures &sigs);

std::ostream &operator<<(std::ostream& output, const Json::Value &value);
std::ostream &operator<<(std::ostream& output, const struct tm &time);
std::ostream &operator<<(std::ostream& output, const std::map<std::string, Json::Value> &map);
std::ostream &operator<<(std::ostream& output, const std::vector<Json::Value> &array);
std::ostream &operator<<(std::ostream& output, const SG::Strings &strs);
std::ostream &operator<<(std::ostream& output, const SG::MethodSignatures &sigs);

#endif    // End #ifdef __SG_TYPES_H__
