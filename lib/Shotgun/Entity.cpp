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
#include <stdexcept>

#include <Shotgun/types.h>
#include <Shotgun/exceptions.h>
#include <Shotgun/FilterBy.h>
#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>

namespace Shotgun {

// *****************************************************************************
Entity::Entity(Shotgun *sg)
    : m_sg(sg)
{
    m_attrs = NULL;

}

// *****************************************************************************
Entity::~Entity()
{
    delete m_attrs;
}

// *****************************************************************************
xmlrpc_c::value Entity::createSGEntity(Shotgun *sg, const Dict &createMap)
{
    Method *md = sg->method("create");

    xmlrpc_c::paramList params;
    params.add(toXmlrpcValue(sg->authMap()));
    params.add(toXmlrpcValue(createMap));

    xmlrpc_c::value rawResult = md->call(params); 
    xmlrpc_c::value results;

    if (rawResult.type() != xmlrpc_c::value::TYPE_NIL)
    {
        results = getAttrValue("results", Dict(rawResult));
    }

    return results;
}

// *****************************************************************************
List Entity::findSGEntities(Shotgun *sg, 
                            Dict &findMap,
                            const int limit)
{
    Method *md = sg->method("read");

    List entityList;

    bool done = false;
    while (!done)
    {
        xmlrpc_c::paramList params;
        params.add(toXmlrpcValue(sg->authMap()));
        params.add(toXmlrpcValue(findMap));

        // Returns a struct - so convert it to an array of entities
        xmlrpc_c::value rawResult = md->call(params);

        List entities = Entity::getFindResultEntityList(rawResult);

        if (entities.size() == 0)
        {
            done = true;
        }
        else
        {
            entityList.extend(entities);

            Dict resultPaging = Entity::getResultPagingInfo(rawResult);
            int entityCount = getAttrValueAsInt("entity_count", resultPaging);

            if (limit > 0 && entityList.size() >= limit)
            {
                entityList.erase(limit, entityList.size());
                done = true;
            }
            else if (entityList.size() == entityCount)
            {
                done = true;
            }
            else
            {
                // Erase the current "paging" field in the findMap
                Dict findMapPaging;
                try
                {
                    findMapPaging = findMap.value<Dict>("paging");
                    findMap.erase("paging");
                }
                catch (SgDictKeyNotFoundError)
                {
                    // Do nothing
                }

                // Increase the "current_page" for the findMap "paging".
                findMap.add("paging", Dict("current_page", getAttrValueAsInt("current_page", findMapPaging)+1)
                                      .add("entities_per_page", getAttrValueAsInt("entities_per_page", findMapPaging)));
            }
        }
    }

    return entityList;
}

// *****************************************************************************
xmlrpc_c::value Entity::updateSGEntity(Shotgun *sg, 
                                       const std::string &entityType, 
                                       const int entityId,
                                       const Fields &fieldsToUpdate)
{
    Method *md = sg->method("update");

    Dict updateMap = Dict("type", entityType)
                     .add("id", entityId)
                     .add("fields", fieldsToUpdate);

    xmlrpc_c::paramList params;
    params.add(toXmlrpcValue(sg->authMap()));
    params.add(toXmlrpcValue(updateMap));

    xmlrpc_c::value rawResult = md->call(params); 
    xmlrpc_c::value results;

    if (rawResult.type() != xmlrpc_c::value::TYPE_NIL)
    {
        results = getAttrValue("results",
                               Dict(rawResult));
    }

    return results;
}

// *****************************************************************************
bool Entity::deleteSGEntity(Shotgun *sg,
                            const std::string &entityType,
                            const int entityId)
{
    Method *md = sg->method("delete");

    Dict deleteMap = Dict("type", entityType)
                     .add("id", entityId);

    xmlrpc_c::paramList params;
    params.add(toXmlrpcValue(sg->authMap()));
    params.add(toXmlrpcValue(deleteMap));

    xmlrpc_c::value rawResult = md->call(params); 

    return getAttrValueAsBool("results", Dict(rawResult));
}

// *****************************************************************************
List Entity::getFindResultEntityList(xmlrpc_c::value &rawResult)
{
    List entityList;

    if (rawResult.type() != xmlrpc_c::value::TYPE_NIL)
    {
        Dict results = getAttrValueAsDict("results", Dict(rawResult));
        entityList = getAttrValueAsList("entities", results);
    }

    return entityList;
}

// *****************************************************************************
Dict Entity::getResultPagingInfo(xmlrpc_c::value &rawResult)
{
    Dict pagingInfoMap;

    if (rawResult.type() != xmlrpc_c::value::TYPE_NIL)
    {
        Dict results = getAttrValueAsDict("results", Dict(rawResult));
        pagingInfoMap = getAttrValueAsDict("paging_info", results);
    }

    return pagingInfoMap;
}

// *****************************************************************************
void Entity::validateLink(const Dict &link)
{
    try
    {
        int id = getAttrValueAsInt("id", link);
        std::string type = getAttrValueAsString("type", link);

        // I think "name" is optional
        //std::string name = getAttrValueAsString("name", link);
    }
    catch (SgAttrError)
    {
        throw SgAttrLinkError(link);
    }
}

// *****************************************************************************
void Entity::validateLink(const xmlrpc_c::value &link)
{
    if (link.type() == xmlrpc_c::value::TYPE_STRUCT)
    {
        Dict linkAsDict;
        fromXmlrpcValue(link, linkAsDict);

        validateLink(linkAsDict);
    }
    else
    {
        throw SgAttrLinkError(link, link.type());
    }
}

// *****************************************************************************
const std::string Entity::getProjectName() const
{
    Dict projectMap = getAttrValueAsDict("project");
    std::string projectName = getAttrValueAsString("name", projectMap);

    return projectName;
}

// *****************************************************************************
const std::string Entity::getProjectCode() const
{
    Dict projectMap = getAttrValueAsDict("project");
    std::string projectName = getAttrValueAsString("name", projectMap);

    Project *project = m_sg->findEntity<Project>(FilterBy("name", "is", projectName));
    return project->sgCode();
}

// *****************************************************************************
const Dict Entity::asLink() const
{
    return Dict("type", entityType())
           .add("id", sgId());
}

// *****************************************************************************
const std::string Entity::linkEntityType(const std::string &linkName) const
{
    Dict entity = getAttrValueAsDict(linkName);

    if (!entity.empty())
    {
        std::string type = getAttrValueAsString("type", entity);
        return type;
    }
    else
    {
        throw SgEntityNotFoundError("\"" + linkName + "\"");
    }
}

// *****************************************************************************
Dict Entity::buildCreateMap(const std::string &entityType,
                            const Dict &data,
                            const List &extraReturnFields)
{
    Dict createMap;

    // -------------------------------------------------------------------
    // "type"
    createMap.add("type", entityType);

    // -------------------------------------------------------------------
    // "fields"
    List fields;
    for(SgMap::const_iterator dataIter = data.value().begin(); dataIter != data.value().end(); ++dataIter)
    {
        fields.append(Dict("field_name", (*dataIter).first)
                      .add("value", (*dataIter).second));
    }
    
    createMap.add("fields", fields);

    // ---------------------------------------------------------------------
    // "return_fields" - the default return fields will be populated in 
    // Shotgun class' entityFactoryCreate(..)
    if (!extraReturnFields.empty())
    {
        createMap.add("return_fields", extraReturnFields);
    } 

    return createMap;
}

// *****************************************************************************
Dict Entity::buildFindMap(const std::string &entityType,
                          const FilterBy &filterList,
                          const List &extraReturnFields,
                          const bool retiredOnly,
                          const int limit,
                          const SortBy &order)
{
    Dict findMap;

    // -------------------------------------------------------------------
    // "type"
    findMap.add("type", entityType);

    // -------------------------------------------------------------------
    // "filters"
    if (!filterList.empty())
    {
        findMap.add("filters", filterList);
    }
    else
    {
        // The "logic_operator" is required, so give some default value       
        findMap.add("filters", Dict("logical_operator", "and")
                               .add("conditions", List()));
    }

    // -------------------------------------------------------------------
    // "return_only"
    findMap.add("return_only", retiredOnly ? "retired" : "active");

    // -------------------------------------------------------------------
    // "paging"
    //
    // "entities_per_page" is used to split up requests into batches 
    // when doing requests. This helps speed tremendously when getting 
    // lots of results back.  It doesn't affect the interface of the api 
    // at all (you always get the full set of results back as one array) 
    // but just how the client class communicates with the server.
    //
    // NOTE: It looks like there is a limit on how much data can be 
    // sent, i.e. 524288 characters. Otherwise you'll get "girerr::error"
    // such as:
    //
    //     Response XML from server is not valid XML-RPC response.  Unable 
    //     to find XML-RPC response in what server sent back.  XML-RPC response 
    //     too large.  Our limit is 524288 characters.  We got 758343 characters
    //
    // Therefore, we need to be careful about what number to put in
    // for "entities_per_page". Here I say 200 for Version entities,
    // but to be safe use 100 for potential large entity data set.
    int maxEntitiesPerPage = 100;

    Dict paging = Dict("current_page", 1);
    if (limit && limit > 0 && limit < maxEntitiesPerPage) 
    {
        paging.add("entities_per_page", limit);
    }
    else
    {
        paging.add("entities_per_page", maxEntitiesPerPage);
    }
    findMap.add("paging", paging);

    // -------------------------------------------------------------------
    // "return_fields" - the default return fields will be populated in 
    // Shotgun class' entityFactoryFind(..)
    if (!extraReturnFields.empty())
    {
        findMap.add("return_fields", extraReturnFields);
    } 

    // -------------------------------------------------------------------
    // "sorts" 
    if (!order.empty())
    {
        findMap.add("sorts", order);
    }

    return findMap;
}

// *****************************************************************************
const xmlrpc_c::value Entity::getAttrValue(const std::string &attrName) const
{
    Dict attrMap;

    // First check to see if the attrName exists in m_attrs, which contains a
    // list of default return fields for this entity type. 
    if (m_attrs->type() != xmlrpc_c::value::TYPE_NIL)
    {
        attrMap = Dict(*m_attrs);

        try
        {
            return attrMap[attrName];
        }
        catch (SgDictKeyNotFoundError)
        {
            // Do nothing
        }
    }
    
    // If attrName is not in m_attrs, do a fresh search in Shotgun using the
    // entity's id because id is a default return field of all entity types
    // and it has already been retrieved at this point.
    // ------------------------------------------------------------------
    // Add attrName to the list of return fields
    Entity *entity = m_sg->findEntity(m_type,
                                      FilterBy("id", "is", sgId()),
                                      List(attrName));

    attrMap = Dict(entity->attrs());
    delete entity;

    try
    {
        return attrMap[attrName];
    }
    catch (SgDictKeyNotFoundError)
    {
        throw SgAttrNotFoundError(attrName);
    }
}

// *****************************************************************************
// static
const xmlrpc_c::value Entity::getAttrValue(const std::string &attrName, 
                                           const Dict &attrsMap)
{
    if (!attrsMap.empty())
    {
        try
        {
            return attrsMap[attrName];
        }
        catch (SgDictKeyNotFoundError)
        {
            throw SgAttrNotFoundError(attrName);
        }
    }
    else
    {
        throw SgEmptyAttrMapError();
    }

}

// *****************************************************************************
void Entity::setAttrValue(const Fields &fields)
{
    // This involves two steps:
    // (1) Update the Shotgun records
    // (2) Update the attribute that is already in m_attrs

    try
    {
        // -------------------------------------------------------------------------
        // Update the Shotgun records - update all the fields in one call
        xmlrpc_c::value result = updateSGEntity(m_sg,
                                                m_type,
                                                sgId(),
                                                fields);

        // -------------------------------------------------------------------------
        // Update the attrbutes if they are already in m_attrs. If not there, don't 
        // add them to m_attrs.
        if (m_attrs->type() != xmlrpc_c::value::TYPE_NIL)
        {
            Dict attrMap = Dict(*m_attrs);
            bool updated = false;
        
            for (size_t i = 0; i < fields.data().size(); i++)
            {
                Dict field = Dict(fields.data()[i]);

                try
                {
                    // ------------------------------------------------------------
                    // Note that the syntax to get the "field_name" and "value" from
                    // the Dict type field is different. They all work, but the value()
                    // func and the operator[] for getting "field_name" uses template,
                    // but the operator[] for getting "value" is the regular func.
                    // 
                    //     std::string fieldName = field.operator[]<std::string>("field_name");
                    //     std::string fieldName = field.value<std::string>("field_name");
                    //
                    //     xmlrpc_c::value fieldValue = field["value"];
                    // ------------------------------------------------------------
                    std::string fieldName = field.value<std::string>("field_name");
                    if (attrMap.find(fieldName))
                    {
                        attrMap.erase(fieldName);
                        attrMap.add(fieldName, field["value"]);

                        updated = true;
                    }
                }
                catch (SgDictKeyNotFoundError)
                {
                    // Do nothing
                }
            }
            // Update the m_attrs as a whole
            if (updated)
            {
                delete m_attrs;
                m_attrs = new xmlrpc_c::value(xmlrpc_c::value_struct(attrMap.value()));
            }
        }
    }
    catch (SgEntityXmlrpcError &error)
    {
        throw SgAttrSetValueError(fields, error.what());
    }
}

// *****************************************************************************
const int Entity::getAttrValueAsInt(const std::string &attrName) const
{
    return getAttrValue<int>(attrName);
}

// *****************************************************************************
const int Entity::getAttrValueAsInt(const std::string &attrName, 
                                    const int defaultVal) const
{
    return getAttrValue<int>(attrName, defaultVal);
}

// *****************************************************************************
// static
const int Entity::getAttrValueAsInt(const std::string &attrName, 
                                    const Dict &attrsMap)
{
    return getAttrValue<int>(attrName, attrsMap);
}

// *****************************************************************************
// static
const int Entity::getAttrValueAsInt(const std::string &attrName, 
                                    const Dict &attrsMap,
                                    const int defaultVal)
{
    return getAttrValue<int>(attrName, attrsMap, defaultVal);
}

// *****************************************************************************
const bool Entity::getAttrValueAsBool(const std::string &attrName) const
{
    return getAttrValue<bool>(attrName);
}

// *****************************************************************************
const bool Entity::getAttrValueAsBool(const std::string &attrName, 
                                      const bool defaultVal) const
{
    return getAttrValue<bool>(attrName, defaultVal);
}

// *****************************************************************************
// static
const bool Entity::getAttrValueAsBool(const std::string &attrName, 
                                      const Dict &attrsMap)
{
    return getAttrValue<bool>(attrName, attrsMap);
}

// *****************************************************************************
// static
const bool Entity::getAttrValueAsBool(const std::string &attrName, 
                                      const Dict &attrsMap,
                                      const bool defaultVal) 
{
    return getAttrValue<bool>(attrName, attrsMap, defaultVal);
}

// *****************************************************************************
const double Entity::getAttrValueAsDouble(const std::string &attrName) const
{
    return getAttrValue<double>(attrName);
}

// *****************************************************************************
const double Entity::getAttrValueAsDouble(const std::string &attrName, 
                                          const double defaultVal) const
{
    return getAttrValue<double>(attrName, defaultVal);
}

// *****************************************************************************
// static
const double Entity::getAttrValueAsDouble(const std::string &attrName, 
                                          const Dict &attrsMap)
{
    return getAttrValue<double>(attrName, attrsMap);
}

// *****************************************************************************
// static
const double Entity::getAttrValueAsDouble(const std::string &attrName, 
                                          const Dict &attrsMap,
                                          const double defaultVal)
{
    return getAttrValue<double>(attrName, attrsMap, defaultVal);
}

// *****************************************************************************
const time_t Entity::getAttrValueAsDatetime(const std::string &attrName) const
{
    return getAttrValue<time_t>(attrName);
}

// *****************************************************************************
const time_t Entity::getAttrValueAsDatetime(const std::string &attrName, 
                                           const time_t defaultVal) const
{
    return getAttrValue<time_t>(attrName, defaultVal);
}

// *****************************************************************************
// static
const time_t Entity::getAttrValueAsDatetime(const std::string &attrName, 
                                            const Dict &attrsMap)
{
    return getAttrValue<time_t>(attrName, attrsMap);
}

// *****************************************************************************
// static
const time_t Entity::getAttrValueAsDatetime(const std::string &attrName, 
                                            const Dict &attrsMap,
                                            const time_t defaultVal)
{
    return getAttrValue<time_t>(attrName, attrsMap, defaultVal);
}

// *****************************************************************************
const std::string Entity::getAttrValueAsString(const std::string &attrName) const 
{
    return getAttrValue<std::string>(attrName);
}

// *****************************************************************************
const std::string Entity::getAttrValueAsString(const std::string &attrName, 
                                               const std::string &defaultVal) const
{
    return getAttrValue<std::string>(attrName, defaultVal);
}

// *****************************************************************************
// static
const std::string Entity::getAttrValueAsString(const std::string &attrName, 
                                               const Dict &attrsMap)
{
    return getAttrValue<std::string>(attrName, attrsMap);
}

// *****************************************************************************
// static
const std::string Entity::getAttrValueAsString(const std::string &attrName, 
                                               const Dict &attrsMap,
                                               const std::string &defaultVal)
{
    return getAttrValue<std::string>(attrName, attrsMap, defaultVal);
}

// *****************************************************************************
const List Entity::getAttrValueAsList(const std::string &attrName) const
{
    return getAttrValue<List>(attrName);
}

// *****************************************************************************
const List Entity::getAttrValueAsList(const std::string &attrName, 
                                      const List &defaultVal) const
{
    return getAttrValue<List>(attrName, defaultVal);
}

// *****************************************************************************
// static
const List Entity::getAttrValueAsList(const std::string &attrName, 
                                      const Dict &attrsMap)
{
    return getAttrValue<List>(attrName, attrsMap);
}

// *****************************************************************************
// static
const List Entity::getAttrValueAsList(const std::string &attrName, 
                                      const Dict &attrsMap,
                                      const List &defaultVal)
{
    return getAttrValue<List>(attrName, attrsMap, defaultVal);
}

// *****************************************************************************
const Dict Entity::getAttrValueAsDict(const std::string &attrName) const
{
    return getAttrValue<Dict>(attrName);
}

// *****************************************************************************
// static
const Dict Entity::getAttrValueAsDict(const std::string &attrName, 
                                      const Dict &attrsMap)
{
    return getAttrValue<Dict>(attrName, attrsMap);
}

// *****************************************************************************
// static
const Dict Entity::getAttrValueAsDict(const std::string &attrName, 
                                      const Dict &attrsMap,
                                      const Dict &defaultVal)
{
    return getAttrValue<Dict>(attrName, attrsMap, defaultVal);
}

// *****************************************************************************
const Strings Entity::getAttrValueAsTags(const std::string &attrName) const 
{
    Strings tags;

    xmlrpc_c::value genericResult = getAttrValue(attrName);

    if (genericResult.type() == xmlrpc_c::value::TYPE_ARRAY)
    {
        List list;
        fromXmlrpcValue(genericResult, list);
    
        for (size_t i = 0; i < list.size(); i++)
        {
            if (list[i].type() == xmlrpc_c::value::TYPE_STRUCT)
            {
                Dict dict;
                fromXmlrpcValue(list[i], dict);

                try
                {
                    tags.push_back(dict.value<std::string>("name"));
                }
                catch (SgDictKeyNotFoundError)
                {
                    // Do nothing
                }
            }
            else if (list[i].type() == xmlrpc_c::value::TYPE_STRING)
            {
                tags.push_back(std::string(xmlrpc_c::value_string(list[i])));
            }
        }
    }

    return tags;
}

// *****************************************************************************
// static
const Strings Entity::getAttrValueAsTags(const std::string &attrName,
                                         const Dict &attrsMap)
{
    Strings tags;

    xmlrpc_c::value genericResult = getAttrValue(attrName, attrsMap);

    if (genericResult.type() == xmlrpc_c::value::TYPE_ARRAY)
    {
        List list;
        fromXmlrpcValue(genericResult, list);

        for (size_t i = 0; i < list.size(); i++)
        {
            if (list[i].type() == xmlrpc_c::value::TYPE_STRUCT)
            {
                Dict dict;
                fromXmlrpcValue(list[i], dict);

                try
                {
                    tags.push_back(dict.value<std::string>("name"));
                }
                catch (SgDictKeyNotFoundError)
                {
                    // Do nothing
                }
            }
            else if (list[i].type() == xmlrpc_c::value::TYPE_STRING)
            {
                tags.push_back(std::string(xmlrpc_c::value_string(list[i])));
            }
        }
    }

    return tags;
}

// *****************************************************************************
const Entity *Entity::getAttrValueAsEntityPtr(const std::string &attrName) const
{
    Dict entity = getAttrValueAsDict(attrName);

    if (!entity.empty())
    {
        int id = getAttrValueAsInt("id", entity);
        std::string type = getAttrValueAsString("type", entity);

        return m_sg->findEntity(type,
                                FilterBy("id", "is", id));
    }
    else
    {
        throw SgEntityNotFoundError("\"" + attrName + "\"");
    }
}

// *****************************************************************************
// static
const Entity *Entity::getAttrValueAsEntityPtr(Shotgun *sg, 
                                              const std::string &attrName,
                                              const Dict &attrsMap)
{
    Dict entity = getAttrValueAsDict(attrName, attrsMap);

    if (!entity.empty())
    {
        int id = getAttrValueAsInt("id", entity);
        std::string type = getAttrValueAsString("type", entity);

        return sg->findEntity(type,
                              FilterBy("id", "is", id));
    }
    else
    {
        throw SgEntityNotFoundError("\"" + attrName + "\"");
    }
}

// *****************************************************************************
const EntityPtrs Entity::getAttrValueAsMultiEntityPtr(const std::string &attrName) const
{
    EntityPtrs entities;

    List entityList = getAttrValueAsList(attrName);
    for (size_t i = 0; i < entityList.size(); i++)
    {
        Dict entity = Dict(entityList[i]);

        if (!entity.empty())
        {
            int id = getAttrValueAsInt("id", entity);
            std::string type = getAttrValueAsString("type", entity);

            entities.push_back(m_sg->findEntity(type,
                                                FilterBy("id", "is", id)));
        }
    }

    return entities;
}

// *****************************************************************************
// static
const EntityPtrs Entity::getAttrValueAsMultiEntityPtr(Shotgun *sg, 
                                                      const std::string &attrName,
                                                      const Dict &attrsMap)
{
    EntityPtrs entities;

    List entityList = getAttrValueAsList(attrName, attrsMap);
    for (size_t i = 0; i < entityList.size(); i++)
    {
        Dict entity = Dict(entityList[i]);

        if (!entity.empty())
        {
            int id = getAttrValueAsInt("id", entity);
            std::string type = getAttrValueAsString("type", entity);

            entities.push_back(sg->findEntity(type,
                                              FilterBy("id", "is", id)));
        }
    }

    return entities;
}

// *****************************************************************************
const std::string Entity::getAttrValueAsUserLogin(const std::string &attrName) const 
{
    const Entity *entity = getAttrValueAsEntityPtr(attrName);
    if (const HumanUser *user = dynamic_cast<const HumanUser *>(entity))
    {
        std::string sgLogin = user->sgLogin();
        delete entity;

        return sgLogin;
    }
    else
    {
        delete entity;
        throw SgEntityDynamicCastError("HumanUser");
    }
}

// *****************************************************************************
// static
const std::string Entity::getAttrValueAsUserLogin(Shotgun *sg,
                                                  const std::string &attrName,
                                                  const Dict &attrsMap) 
{
    const Entity *entity = getAttrValueAsEntityPtr(sg, attrName, attrsMap);
    if (const HumanUser *user = dynamic_cast<const HumanUser *>(entity))
    {
        std::string sgLogin = user->sgLogin();
        delete entity;

        return sgLogin;
    }
    else
    {
        delete entity;
        throw SgEntityDynamicCastError("HumanUser");
    }
}

} // End namespace Shotgun
