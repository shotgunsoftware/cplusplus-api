//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/Sequence.h>
#include <Shotgun/Show.h>
#include <Shotgun/utils.h>

namespace Shotgun {

// *****************************************************************************
Sequence::Sequence(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "Sequence";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
Sequence::Sequence()
    : Entity(NULL)
{
    m_type = "Sequence";
    m_attrs = NULL; 
}

// *****************************************************************************
Sequence::Sequence(const Sequence &ref)
    : Entity(ref.m_sg)
{
    m_type = "Sequence";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
Sequence::~Sequence()
{
    // Nothing
}

// *****************************************************************************
Sequence Sequence::create(Shotgun *sg, 
                          const std::string &showCode,
                          const std::string &sequenceName)
{
    // By convention, the sequence name is in uppercase
    std::string sequenceNameUpper = toupper(sequenceName);

    // Check if the sequence already exists
    try
    {
        Sequence seq = sg->findSequenceByName(showCode, sequenceNameUpper);

        std::string err = "Sequence \"" + sequenceNameUpper + "\" already exists for show \"" + showCode + "\"";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        Show show = sg->findShowByCode(showCode);

        SgMap attrsMap;
        attrsMap["project"] = toXmlrpcValue(show.asLink());
        attrsMap["code"] = toXmlrpcValue(sequenceNameUpper);

        // Call the base class function to create an entity
        return Sequence(sg, createEntity(sg, "Sequence", attrsMap));
    }
}

// *****************************************************************************
Sequences Sequence::find(Shotgun *sg, SgMap &findMap)
{
    // Find the entities that match the findMap and create a Sequence for each of them
    Sequences sequences;

    SgArray result = Entity::findEntities(sg, findMap);
    if (result.size() > 0)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            sequences.push_back(Sequence(sg, result[i]));
        }
    }

    return sequences;
}

} // End namespace Shotgun
