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

//std::auto_ptr<curlpp::Easy> Method::createRequest()
//{
//	std::auto_ptr<curlpp::Easy> request(new curlpp::Easy);
//	
//	std::list<std::string> header;
//	header.push_back("content-type: application/json; charset=utf-8");
//	header.push_back("connection : keep-alive");
//	header.push_back("user-agent : shotgun-json");
//	header.push_back("Authorization : Basic ");
//	
//	request->setOpt<curlpp::options::Url>(m_sg->serverURL());
//	request->setOpt(new curlpp::options::SslVerifyPeer(FALSE));
//	request->setOpt(new curlpp::options::HttpHeader(header));
//	request->setOpt(new curlpp::options::FollowLocation(TRUE));
//
//	return request;
//}

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    std::string buf = std::string(static_cast<char *>(ptr), size * nmemb);
    std::stringstream *response = static_cast<std::stringstream *>(stream);
    response->write(buf.c_str(), (std::streamsize)buf.size());
    return size * nmemb;
}

// *****************************************************************************
std::string Method::serverCapabilities()
{
    // Prepare the parameters
	Json::Value root;
	Json::Value params(Json::arrayValue);

    root["method_name"] = "info";
	root.append(params);
	
	Json::StyledWriter writer;
	std::string data = writer.write(root);

 //   std::auto_ptr<curlpp::Easy> request = createRequest();
	//request->setOpt(new curlpp::options::PostFields(data));
	//std::stringstream response;
	//request->setOpt(new curlpp::options::WriteStream(&response));
	//
	//try{
	//	request->perform();
	//	return response.str();
 //   } catch (curlpp::UnknowException & e) {
 //       std::cout << "Unknown Exception: " << e.what() << std::endl;
 //   } catch (curlpp::RuntimeError & e) {
 //       std::cout << "Runtime Exception: " << e.what() << std::endl;
 //   } catch (curlpp::LogicError & e) {
 //       std::cout << "Logic Exception: " << e.what() << std::endl;
 //   }
	
	return std::string("failed");
}


// *****************************************************************************
Json::Value Method::call()
{
	// Prepare the parameters
	Json::Value root;
	Json::Value params(Json::arrayValue);

    root["method_name"] = m_methodName;
	root.append(params);

	
	
	Json::StyledWriter writer;
	std::string data = writer.write(root);

 //   std::auto_ptr<curlpp::Easy> request = createRequest();
	//request->setOpt(new curlpp::options::PostFields(data));
	//
	//std::stringstream response;
	//request->setOpt(new curlpp::options::WriteStream(&response));
	//std::cout << response << std::endl;
	//try{
	//	request->perform();
	//	Json::Reader reader;
	//	Json::Value output;
	//	reader.parse(response, output);
	//	return output;
 //   } catch (curlpp::UnknowException & e) {
 //       std::cout << "Unknown Exception: " << e.what() << std::endl;
 //   } catch (curlpp::RuntimeError & e) {
 //       std::cout << "Runtime Exception: " << e.what() << std::endl;
	//	throw SgJsonrpcValueError(e.what());
 //   } catch (curlpp::LogicError & e) {
 //       std::cout << "Logic Exception: " << e.what() << std::endl;
 //   }
	
	return Json::Value();
}

// *****************************************************************************
Json::Value Method::call(const Dict &params)
{
    // Here are two ways of doing the RPC call. They return the
    // same result. The "client.call" seems very intuitive, but
    // the doc says that an ordinary client program does not use 
    // this method because it performs RPC via the methods of an
    // xmlrpc_c::rpc object.
    //
    // I think the advantages of using a xmlrpc_c::rpc object are 
    // the execution status of the RPC. Has it been started yet? 
    // Has it finished? Has an error prevented the RPC from executing? 

	// Prepare the parameters
	Json::Value c_params(Json::arrayValue);
	c_params.append(toJsonrpcValue(m_sg->authMap()));
	c_params.append(toJsonrpcValue(params));
    
	Json::Value root;
    root["method_name"] = m_methodName;
    root["params"] = c_params;
	
	std::cout << root << std::endl;

    CURL *curl;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, m_sg->serverURL().c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);

    struct curl_slist *slist=NULL;
    slist = curl_slist_append(slist, "content-type: application/json; charset=utf-8");
    slist = curl_slist_append(slist, "connection : keep-alive");
    slist = curl_slist_append(slist, "user-agent : shotgun-json");
    slist = curl_slist_append(slist, "Authorization : Basic ");
    
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, TRUE);
    
	Json::StyledWriter writer;
	std::string data = writer.write(root);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
	
    std::stringstream response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    Json::Reader reader;
	Json::Value output;
	bool success = reader.parse(response.str(), output);
    curl_easy_cleanup(curl);
	curl_slist_free_all(slist);
	
    return output;
}

} // End namespace SG
