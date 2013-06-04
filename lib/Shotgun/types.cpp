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

#include <time.h>

#include <Shotgun/types.h>
#include <Shotgun/List.h>
#include <Shotgun/Dict.h>
#include <Shotgun/FilterBy.h>
#include <Shotgun/SortBy.h>
#include <Shotgun/Fields.h>

//extern char *tzname[2];
//extern long timezone;
//extern int daylight;

namespace SG {

// *****************************************************************************
std::string jsonrpcValueTypeStr(const Json::ValueType jsonrpcType)
{
    switch (jsonrpcType)
    {
		case Json::intValue:
            return std::string("TYPE_INT");
		case Json::booleanValue:
            return std::string("TYPE_BOOLEAN");
		case Json::realValue:
            return std::string("TYPE_DOUBLE");
        //case Json::Value::TYPE_DATETIME:
        //    return std::string("TYPE_DATETIME");
		case Json::stringValue:
            return std::string("TYPE_STRING");
        //case Json::Value::TYPE_BYTESTRING:
        //    return std::string("TYPE_BYTESTRING");
		case Json::arrayValue:
            return std::string("TYPE_ARRAY");
		case Json::objectValue:
            return std::string("TYPE_OBJECT");
        //case Json::Value::TYPE_C_PTR:
        //    return std::string("TYPE_C_PTR");
		case Json::nullValue:
            return std::string("TYPE_NULL");
        //case Json::Value::TYPE_DEAD:
        default:
            return std::string("TYPE_DEAD");
    }
}

// *****************************************************************************
Json::Value toJsonrpcValue(const char *in)
{
    return Json::Value(in);
}

// *****************************************************************************
Json::Value toJsonrpcValue(const std::string &in)
{
    return Json::Value(in);
}

// *****************************************************************************
Json::Value toJsonrpcValue(const int &in)
{
	return Json::Value(in);
}

// *****************************************************************************
Json::Value toJsonrpcValue(const double &in)
{
    return Json::Value(in);
}

// *****************************************************************************
Json::Value toJsonrpcValue(const bool &in)
{
    return Json::Value(in);
}

// *****************************************************************************
//Json::Value toJsonrpcValue(const time_t &in)
//{
//    return Json::Value(in);
//}

// *****************************************************************************
//Json::Value toJsonrpcValue(const struct tm &in)
//{
//    // This converts the local time to UTC time
//    time_t time = mktime((struct tm *)&in);
//
//    return Json::Value(time);
//}

// *****************************************************************************
Json::Value toJsonrpcValue(const std::vector<Json::Value> &in)
{
	Json::Value val(Json::arrayValue);
	for(std::vector<Json::Value>::const_iterator itr = in.begin(); itr != in.end(); ++itr)
		val.append(*itr);
    return val;
}

// *****************************************************************************
Json::Value toJsonrpcValue(const std::map<std::string, Json::Value> &in)
{
	Json::Value val(Json::objectValue);
	for(std::map<std::string, Json::Value>::const_iterator itr = in.begin(); itr != in.end(); ++itr)
		val[(*itr).first] = (*itr).second;
    return val;
}

// *****************************************************************************
Json::Value toJsonrpcValue(const Strings &in)
{
    std::vector<Json::Value> strArray;
   
    for (size_t i = 0; i < in.size(); i++)
    {
        strArray.push_back(toJsonrpcValue(in[i]));
    }
	
    return toJsonrpcValue(strArray);
}

// *****************************************************************************
Json::Value toJsonrpcValue(const MethodSignatures &in)
{
    std::vector<Json::Value> strArray;
   
    for (size_t i = 0; i < in.size(); i++)
    {
        strArray.push_back(toJsonrpcValue(in[i]));
    }

    return toJsonrpcValue(strArray);
}

// *****************************************************************************
Json::Value toJsonrpcValue(const List &in)
{
	Json::Value out(Json::arrayValue);
	for(std::vector<Json::Value>::const_iterator itr = in.value().begin(); itr != in.value().end(); ++itr)
		out.append(*itr);
    return out;
}

// *****************************************************************************
Json::Value toJsonrpcValue(const Dict &in)
{
	Json::Value out(Json::objectValue);
	for(std::map<std::string, Json::Value>::const_iterator itr = in.value().begin(); itr != in.value().end(); ++itr)
		out[(*itr).first] = (*itr).second;
    return out;
}

// *****************************************************************************
Json::Value toJsonrpcValue(const FilterBy &in)
{
    return toJsonrpcValue(in.filters());
}

// *****************************************************************************
Json::Value toJsonrpcValue(const SortBy &in)
{
    return toJsonrpcValue(in.sorts());
}

// *****************************************************************************
Json::Value toJsonrpcValue(const Fields &in)
{
    return toJsonrpcValue(in.fields());
}

// *****************************************************************************
Json::Value toJsonrpcValue(const Json::Value &in)
{
    return in;
}

// *****************************************************************************
void fromJsonrpcValue(const Json::Value &value, char *out)
{
	if (value.isString())
    {
        out = _strdup(value.asCString());
    }
	else if (value.isNull())
    {
        throw SgJsonrpcValueIsNilError();
    }
    else
    {
        throw SgJsonrpcValueTypeError(value,
									 Json::stringValue,
                                     value.type());
    }
}

// *****************************************************************************
void fromJsonrpcValue(const Json::Value &value, std::string &out)
{
	if (value.isString())
    {
		out = value.asString();
    }
    else if (value.isNull())
    {
        throw SgJsonrpcValueIsNilError();
    }
    else
    {
        throw SgJsonrpcValueTypeError(value,
                                     Json::stringValue,
                                     value.type());
    }
}

// *****************************************************************************
void fromJsonrpcValue(const Json::Value &value, int &out)
{
	if (value.isInt())
    {
		out = value.asInt();
    }
    else if (value.isNull())
    {
        throw SgJsonrpcValueIsNilError();
    }
    else
    {
        throw SgJsonrpcValueTypeError(value,
									 Json::intValue,
                                     value.type());
    }
}

// *****************************************************************************
void fromJsonrpcValue(const Json::Value &value, double &out)
{
	if (value.isDouble())
    {
		out = value.asDouble();
    }
    else if (value.isNull())
    {
        throw SgJsonrpcValueIsNilError();
    }
    else
    {
        throw SgJsonrpcValueTypeError(value,
                                     Json::realValue,
                                     value.type());
    }
}

// *****************************************************************************
void fromJsonrpcValue(const Json::Value &value, bool &out)
{
	if (value.isBool())
    {
		out = value.asBool();
    }
    else if (value.isNull())
    {
        throw SgJsonrpcValueIsNilError();
    }
    else
    {
        throw SgJsonrpcValueTypeError(value,
                                     Json::booleanValue,
                                     value.type());
    }
}

// *****************************************************************************
//void fromJsonrpcValue(const Json::Value &value, time_t &out)
//{
//    if (value.type() == Json::Value::TYPE_DATETIME)
//    {
//        out = time_t(Json::Value_datetime(value));
//    }
//    else if (value.type() == Json::Value::TYPE_NIL)
//    {
//        throw SgJsonrpcValueIsNilError();
//    }
//    else
//    {
//        throw SgJsonrpcValueTypeError(value,
//                                     Json::Value::TYPE_DATETIME,
//                                     value.type());
//    }
//}

// *****************************************************************************
//void fromJsonrpcValue(const Json::Value &value, struct tm &out)
//{
//    if (value.type() == Json::Value::TYPE_DATETIME)
//    {
//        time_t t = time_t(Json::Value_datetime(value));
//
//        // This converts the UTC time to local time
//        out = *(localtime(&t));
//    }
//    else if (value.type() == Json::Value::TYPE_NIL)
//    {
//        throw SgJsonrpcValueIsNilError();
//    }
//    else
//    {
//        throw SgJsonrpcValueTypeError(value,
//                                     Json::Value::TYPE_DATETIME,
//                                     value.type());
//    }
//}

// *****************************************************************************
void fromJsonrpcValue(const Json::Value &value, std::vector<Json::Value> &out)
{
	if (value.isArray())
    {
		for( Json::ValueIterator itr = value.begin(); itr != value.end(); itr++ )
		{
			out.push_back(itr.key());
		}
    }
	else if (value.isNull())
    {
        throw SgJsonrpcValueIsNilError();
    }
    else
    {
        throw SgJsonrpcValueTypeError(value,
									 Json::arrayValue,
                                     value.type());
    }
}

// *****************************************************************************
void fromJsonrpcValue(const Json::Value &value, std::map<std::string, Json::Value> &out)
{
	if (value.isObject())
    {
        for (Json::ValueIterator itr = value.begin(); itr != value.end(); itr++ )
			out[itr.memberName()] = itr.key();
    }
	else if (value.isNull())
    {
        throw SgJsonrpcValueIsNilError();
    }
    else
    {
        throw SgJsonrpcValueTypeError(value,
									 Json::objectValue,
                                     value.type());
    }
}

// *****************************************************************************
void fromJsonrpcValue(const Json::Value &value, Strings &out)
{
	if (value.isArray())
    {   
        Strings strings;
		for (Json::ValueIterator itr = value.begin(); itr != value.end(); itr++)
        {
            if (itr.key().isString())
            {
				strings.push_back(itr.key().asString());
            }
            else
            {
				throw SgJsonrpcValueTypeError(itr.key(), Json::stringValue, itr.key().type());
            }
        }

        out = strings;
    }
    else if (value.isNull())
    {
        throw SgJsonrpcValueIsNilError();
    }
    else
    {
        throw SgJsonrpcValueTypeError(value, Json::arrayValue, value.type());
    }
}

// *****************************************************************************
void fromJsonrpcValue(const Json::Value &value, List &out)
{
	if (value.isArray())
    {
        out = List(value);
    }
    else if (value.isNull())
    {
        throw SgJsonrpcValueIsNilError();
    }
    else
    {
        throw SgJsonrpcValueTypeError(value,
                                     Json::arrayValue,
                                     value.type());
    }
}

// *****************************************************************************
void fromJsonrpcValue(const Json::Value &value, Dict &out)
{
	if (value.isObject())
    {
        out = Dict(value);
    }
	else if (value.isNull())
    {
        throw SgJsonrpcValueIsNilError();
    }
    else
    {
        throw SgJsonrpcValueTypeError(value,
									 Json::objectValue,
                                     value.type());
    }
}

// *****************************************************************************
void fromJsonrpcValue(const Json::Value &value, FilterBy &out)
{
	if (value.isObject())
    {
        out = FilterBy(Dict(value));
    }
	else if (value.isNull())
    {
        throw SgJsonrpcValueIsNilError();
    }
    else
    {
        throw SgJsonrpcValueTypeError(value,
									 Json::objectValue,
                                     value.type());
    }
}

// *****************************************************************************
void fromJsonrpcValue(const Json::Value &value, SortBy &out)
{
	if (value.isArray())
    {
        out = SortBy(List(value));
    }
    else if (value.isNull())
    {
        throw SgJsonrpcValueIsNilError();
    }
    else
    {
        throw SgJsonrpcValueTypeError(value,
                                     Json::arrayValue,
                                     value.type());
    }
}

// *****************************************************************************
void fromJsonrpcValue(const Json::Value &value, Fields &out)
{
	if (value.isArray())
    {
        out = Fields(value);
    }
    else if (value.isNull())
    {
        throw SgJsonrpcValueIsNilError();
    }
    else
    {
        throw SgJsonrpcValueTypeError(value,
                                     Json::arrayValue,
                                     value.type());
    }
}

// *****************************************************************************
void fromJsonrpcValue(const Json::Value &value, Json::Value &out)
{
    out = value;
}

// *****************************************************************************
std::string currDateStr()
{
    // Get the current time
    time_t rawTime;
    time(&rawTime);

    // Convert to a time string
    struct tm *timeInfo = localtime(&rawTime);
    char timeStr[10];
    strftime(timeStr, 20, "%Y-%m-%d", timeInfo);

    return std::string(timeStr);
}

} // End namespace SG

// *****************************************************************************
// *****************************************************************************
std::string toStdString(const int val)
{
    char str[1024];
    sprintf_s(str, "%d", val);
    return std::string(str);
}

std::string toStdString(const bool val)
{
    char str[1024];
    sprintf_s(str, "%d", val);
    return std::string(str);
}

std::string toStdString(const double val)
{
    char str[1024];
    sprintf_s(str, "%f", val);
    return std::string(str);
}

std::string toStdString(const time_t val)
{
    char str[1024];
    sprintf_s(str, "%u", val);
    return std::string(str);
}

//std::string toStdString(const struct tm &val)
//{
//    return std::string(asctime_s(&val));
//}

std::string toStdString(const Json::Value &value)
{
	return value.toStyledString();
}

std::string toStdString(const std::map<std::string, Json::Value> &map)
{
	Json::Value val;
	for(std::map<std::string, Json::Value>::const_iterator itr = map.begin(); itr != map.end(); ++itr)
		val[(*itr).first] = (*itr).second;
	
	return toStdString(val);
}

// *****************************************************************************
std::string toStdString(const std::vector<Json::Value> &arr)
{
	Json::Value val(Json::arrayValue);
	for(std::vector<Json::Value>::const_iterator itr = arr.begin(); itr != arr.end(); ++itr)
		val.append(*itr);
    
	return toStdString(val);
}

// *****************************************************************************
std::string toStdString(const SG::Strings &strs)
{
    std::string output = "[";

    if (strs.size() > 0)
    {
        for (size_t i = 0; i < strs.size()-1; i++)
        {
            output += "\"" + strs[i] + "\", ";
        }

        output += "\"" + strs[strs.size()-1] + "\"";
    }

    output += "]";

    return output;
}

// *****************************************************************************
std::string toStdString(const SG::MethodSignatures &sigs)
{
    std::string output = "[";

    if (sigs.size() > 0)
    {
        for (size_t i = 0; i < sigs.size()-1; i++)
        {
            output += toStdString(sigs[i]) + ", ";
        }

        output += toStdString(sigs[sigs.size()-1]);
    }

    output += "]";

    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Json::Value &value)
{
    output << toStdString(value);
    return output;
}

// *****************************************************************************
//std::ostream &operator<<(std::ostream& output, const struct tm &time)
//{
//    output << toStdString(time);
//    return output;
//}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const std::map<std::string, Json::Value> &map)
{
    output << toStdString(map);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const std::vector<Json::Value> &arr)
{
    output << toStdString(arr);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const SG::Strings &strs)
{
    output << toStdString(strs);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const SG::MethodSignatures &sigs)
{
    output << toStdString(sigs);
    return output;
}


