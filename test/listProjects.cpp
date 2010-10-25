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
#include <Shotgun/Shotgun.h>
#include <Shotgun/FilterBy.h>
#include <Shotgun/Dict.h>
#include <Shotgun/Fields.h>

using namespace SG;

int main( int argc, char **argv )
{
    // ************************************************************************
    // Check on the essentials for connecting to Shotgun.
    // ************************************************************************

    std::string shotgunURL(SG_DEFAULT_URL);
    std::string authName(SG_AUTHENTICATION_NAME);
    std::string authKey(SG_AUTHENTICATION_KEY);

    for (size_t i = 1; i < argc; i++)
    {
        if (!strcasecmp(argv[i], "-url"))
        {
            shotgunURL = argv[++i];
        }
        else if (!strcasecmp(argv[i], "-authName"))
        {
            authName = argv[++i];
        }
        else if (!strcasecmp(argv[i], "-authKey"))
        {
            authKey = argv[++i];
        }
    }

    if(shotgunURL == "")
    {
        std::cerr << "No default Shotgun URL specified to configure.  Skipping test." << std::endl;
        exit(0);
    }

    if(authName == "")
    {
        std::cerr << std::endl
                  << "No default Shotgun authentication script_name specified to configure." << std::endl
                  << "It corresponds to \"Script Name\" on the [Admin] > [Scripts] page.  Skipping test." << std::endl;
        exit(0);
    }

    if(authKey == "")
    {
        std::cerr << std::endl
                  << "No default Shotgun authentication script_key specified to configure." << std::endl
                  << "It corresponds to \"Application Key\" on the [Admin] > [Scripts] page.  Skipping test." << std::endl;
        exit(0);
    }

    // ************************************************************************
    // Start to test
    // ************************************************************************

    try
    {
        Shotgun sg(shotgunURL, authName, authKey);

        std::cout << std::endl << "**************************** findEntities ****************************" << std::endl;
        ProjectPtrs projects = sg.findEntities<Project>();
        for( size_t p = 0; p < projects.size(); ++p )
        {
            std::cout << *(projects[p]) << std::endl;

            std::cout << projects[p]->getAttrValueAsString("code") << std::endl;
            std::cout << projects[p]->getAttrValueAsInt("id") << std::endl;
            std::cout << "-------------------" << std::endl;
            delete projects[p];
        }


        std::cout << std::endl << "**************************** createEntity ****************************" << std::endl;
        Project *newProject = sg.createEntity<Project>(Dict("name", "TEST PROJECT")
                                                       .add("code", "tp"));
        std::cout << *newProject << std::endl;
        delete newProject;


        std::cout << std::endl << "**************************** findEntiy ****************************" << std::endl;
        Project *project = sg.findEntity<Project>(FilterBy("code", "is", "tp"));
        std::cout << *project << std::endl;
        //delete project; // delete later


        std::cout << std::endl << "**************************** setAttrValue - update entity ****************************" << std::endl;
        project->setAttrValue(Fields("name", "My Test Project")
                             .append("sg_default_start_frame", 101));
        std::cout << *project << std::endl;


        std::cout << std::endl << "**************************** deleteEntity ****************************" << std::endl;
        int id = project->sgId();
        if (sg.deleteEntity<Project>(id)) // Delete the Shotgun entity by its id
        {
            std::cout << "Project entity with id, " << id << ", deleted" << std::endl;
        }
        else
        {
            std::cout << "Project entity with id, " << id << ", not deleted - it may be retired or non-existent" << std::endl;
        }
        delete project; // Delete the Project class instance.
    }
    catch (const SgError & e)
    {
        std::cerr << "SgError: " << e.what() << std::endl;
        return -1;
    }
    catch (const std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
