/*
	Copyright 2009-2012, Sumeet Chhetri

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
/*
 * RestController.cpp
 *
 *  Created on: Apr 7, 2011
 *      Author: sumeet
 */

#include "RestController.h"

Logger RestController::logger;

RestController::RestController() {
	logger = Logger::getLogger("RestController");
}

RestController::~RestController() {
	// TODO Auto-generated destructor stub
}

void RestController::buildResponse(HTTPResponseStatus status, string className, void* entity)
{
	string content;
	if(response->getContent_type()==ContentTypes::CONTENT_TYPE_APPLICATION_JSON)
	{
		content = JSONSerialize::serializeUnknown(entity, className);
		response->setContent_type(ContentTypes::CONTENT_TYPE_APPLICATION_JSON);
	}
	else
	{
		content = XMLSerialize::serializeUnknown(entity, className);
		response->setContent_type(ContentTypes::CONTENT_TYPE_APPLICATION_XML);
	}
	if(content!="")
	{
		response->setHTTPResponseStatus(status);
		response->setContent_str(content);
	}
	else
	{
		response->setHTTPResponseStatus(HTTPResponseStatus::BadRequest);
		response->setContent_str(content);
	}
}

void RestController::buildResponseVector(HTTPResponseStatus status, string className, void* entity)
{
	string content;
	if(response->getContent_type()==ContentTypes::CONTENT_TYPE_APPLICATION_JSON)
	{
		content = JSONSerialize::serializeUnknown(entity, "std::vector<"+className+",");
		response->setContent_type(ContentTypes::CONTENT_TYPE_APPLICATION_JSON);
	}
	else
	{
		content = XMLSerialize::serializeUnknown(entity, "std::vector<"+className+",");
		response->setContent_type(ContentTypes::CONTENT_TYPE_APPLICATION_XML);
	}
	if(content!="")
	{
		response->setHTTPResponseStatus(status);
		response->setContent_str(content);
	}
	else
	{
		response->setHTTPResponseStatus(HTTPResponseStatus::BadRequest);
		response->setContent_str(content);
	}
}
