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

#include <Shotgun/Shotgun.h>
#include <Shotgun/Type.h>
#include <Shotgun/FilterBy.h>
#include <Shotgun/SortBy.h>

int main( int argc, char **argv )
{
    std::string shotgunURL(SG_DEFAULT_URL);
    if( argc == 2 )
    {
        shotgunURL = argv[1];
    }
    if(shotgunURL == "")
    {
        std::cerr << "No default Shotgun URL specified to configure.  Skipping test."
                  << std::endl;
        exit(0);
    }
    try
    {
        Shotgun::Shotgun sg(shotgunURL);

        std::cout << std::endl << "allProjects: ***********************************************" << std::endl;
        Shotgun::ProjectPtrs projects = sg.allProjects();
        for( size_t p = 0; p < projects.size(); ++p )
        {
            std::cout << *(projects[p]) << std::endl;
            std::cout << "-------------------" << std::endl;
            delete projects[p];
        }

        std::cout << std::endl << "allProjects: order by code (ascending): ***********************************************" << std::endl;
        Shotgun::ProjectPtrs projectsOrderByCode = sg.findEntities<Shotgun::Project>(Shotgun::FilterBy(),  // filters
                                                                                     0,                    // limit
                                                                                     Shotgun::SgArray(),   // extraReturnFields
                                                                                     false,                // retiredOnly
                                                                                     Shotgun::SortBy("code", "asc"));  // order
        for( size_t p = 0; p < projectsOrderByCode.size(); ++p )
        {
            std::cout << projectsOrderByCode[p]->sgCode() << std::endl;
            delete projectsOrderByCode[p];
        }

        std::cout << std::endl << "allProjects: order by name (descending): ***********************************************" << std::endl;
        Shotgun::ProjectPtrs projectsOrderByName = sg.findEntities<Shotgun::Project>(Shotgun::FilterBy(),  // filters
                                                                                     0,                    // limit
                                                                                     Shotgun::SgArray(),   // extraReturnFields
                                                                                     false,                // retiredOnly
                                                                                     Shotgun::SortBy("name", "desc"));  // order
        for( size_t p = 0; p < projectsOrderByName.size(); ++p )
        {
            std::cout << projectsOrderByName[p]->sgName() << std::endl;
            delete projectsOrderByName[p];
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
