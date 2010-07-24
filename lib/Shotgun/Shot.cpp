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

// #include <TipUtil/ShotName.h>

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/Shot.h>
#include <Shotgun/Sequence.h>
#include <Shotgun/Project.h>

namespace Shotgun {

// *****************************************************************************
Shot::Shot(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg), TaskMixin(), NoteMixin()
{
    m_type = "Shot";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
Shot::Shot()
    : Entity(NULL)
{
    m_type = "Shot";
    m_attrs = NULL;
}

// *****************************************************************************
Shot::Shot(const Shot &ref)
    : Entity(ref.m_sg)
{
    m_type = "Shot";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
Shot::~Shot()
{
    // Nothing
}

// *****************************************************************************
Shot Shot::create(Shotgun *sg, 
                  const std::string &shotName,
                  const std::string &shotType)
{
    // Check if the shot already exists
    try
    {
        Shot shot = sg->findShotByName(shotName);

        std::string err = "Shot \"" + shotName + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
#warning Implement in non-Tippett way
//         TipUtil::ShotName sn = TipUtil::ShotName(shotName);
//         Show show = sg->findShowByCode(sn.show());
//         Sequence seq;
//         try
//         {
//             seq = Sequence(sg, sg->findSequenceByName(sn.show(), sn.sequence()).attrs());
//         }
//         catch (SgEntityNotFoundError)
//         {
//             seq = sg->createSequence(sn.show(), sn.sequence());
//         }
//         // Other attributes will be filled by the python code
//         SgMap attrsMap;
//         attrsMap["project"] = toXmlrpcValue(show.asLink());
//         attrsMap["code"] = toXmlrpcValue(shotName);
//         attrsMap["sg_type"] = toXmlrpcValue(shotType);
//         attrsMap["sg_sequence"] = toXmlrpcValue(seq.asLink());
//         
//         // Call the base class function to create an entity
//         return Shot(sg, createEntity(sg, "Shot", attrsMap));
    }
}

// *****************************************************************************
Shots Shot::find(Shotgun *sg, SgMap &findMap)
{
    // Find the entities that match the findMap and create a Shot for each of them
    Shots shots;

    SgArray result = Entity::findEntities(sg, findMap);
    if (result.size() > 0)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            shots.push_back(Shot(sg, result[i]));
        }
    }

    return shots;
}

// *****************************************************************************
void Shot::sgSequence(const SgMap &val)
{
    try
    {
        Entity::validateLink(val);
    }
    catch (SgAttrLinkError &error)
    {
        throw SgAttrSetValueError("sg_sequence", error.what());
    }

    setAttrValue("sg_sequence", toXmlrpcValue(val));
}

// *****************************************************************************
const std::string Shot::getTippettWorkingLength() const
{
    std::string result;
    bool makeWorkingLength = false;

    try
    {
        result = getAttrValueAsString("sg_tippett_working_length");
        if (result == "") makeWorkingLength = true;
    }
    catch (SgAttrError &err)
    {
        makeWorkingLength = true;
    }

    if (makeWorkingLength)
    {
        char workingLen[1024];
        sprintf(workingLen, "%d-%d", sgHeadIn(), sgHeadOut());

        result = std::string(workingLen);
    }

    return result;
}

// *****************************************************************************
const Elements Shot::sgElements() const
{
    Elements elements;

    SgArray entities = getAttrValueAsMultiEntityAttrMap("elements");
    for (size_t i = 0; i < entities.size(); i++)
    {
        elements.push_back(Element(m_sg, entities[i]));
    }

    return elements;
}

// *****************************************************************************
void Shot::sgElements(const Elements &val)
{
    SgArray elementLinkArray;

    for (size_t i = 0; i < val.size(); i++)
    {
        elementLinkArray.push_back(toXmlrpcValue(val[i].asLink()));
    }

    setAttrValue("elements", toXmlrpcValue(elementLinkArray));
}

// *****************************************************************************
void Shot::sgElements(const SgArray &val)
{
    for (size_t i = 0; i < val.size(); i++)
    {
        try
        {
            Entity::validateLink(val[i]);
        }
        catch (SgAttrLinkError &error)
        {
            throw SgAttrSetValueError("elements", error.what());
        }
    }

    setAttrValue("elements", toXmlrpcValue(val));
}

} // End namespace Shotgun
