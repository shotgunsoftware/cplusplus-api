#!/usr/bin/env python

import sys
from shotgun import *

def usage():
    print
    print "Usage: listProjects [options]"
    print "Options:"
    print "  -url      <string>   Shotgun serverl URL."
    print "  -authName <string>   Shotgun authentication \"script_name\"."
    print "  -authKey  <string>   Shotgun authentication \"script_key\"."
    print

try:

    #################################################################
    # Check on the essentials for connecting to Shotgun.
    #################################################################
    if len(sys.argv) > 1:
        shotgunURL = ""
        authName = ""
        authKey = ""

        for i in range(1, len(sys.argv)):
            if sys.argv[i] == "-url":
                shotgunURL = sys.argv[i+1]
            elif sys.argv[i] == "-authName":
                authName = sys.argv[i+1]
            elif sys.argv[i] == "-authKey":
                authKey = sys.argv[i+1]

        if not shotgunURL:
            print "No default Shotgun URL specified to configure.  Skipping test."
            sys.exit(0)

        if not authName:
            print "No default Shotgun authentication script_name specified to configure."
            print "It corresponds to \"Script Name\" on the [Admin] page > [Scripts] page.  Skipping test."
            sys.exit(0)

        if not authKey:
            print "No default Shotgun authentication script_key specified to configure."
            print "It corresponds to \"Application Key\" on the [Admin] page > [Scripts] page.  Skipping test."
            sys.exit(0)

        sg = Shotgun(shotgunURL, authName, authKey) 
    else:
        print
        print "ERROR: Missing arguments..."

        usage()
        sys.exit(0)

    #################################################################
    # Find all the Project entities
    #################################################################
    print "*" * 40, "findEntities", "*" * 40
    for project in sg.findEntities("Project"):
        print project
        print "-" * 40

    #################################################################
    # Create a new Project entity
    #################################################################
    print "*" * 40, "createEntity", "*" * 40
    project = sg.createEntity("Project",  Dict("name", "TEST PROJECT")
                                          .add("code", "tp"))
    print project

    #################################################################
    # Find one Project entity
    #################################################################
    print "*" * 40, "findEntity", "*" * 40
    project = sg.findEntity("Project", FilterBy("code", "is", "tp"))
    print project

    #################################################################
    # Update the Project entity fields
    #################################################################
    print "*" * 40, "setAttrValue - update entity", "*" * 40
    project.setAttrValue(Fields("name", "My Test Project")
                        .append("sg_default_start_frame", 101))
    print project
    
    #################################################################
    # Delete the Project entity
    #################################################################
    print "*" * 40, "deleteEntity", "*" * 40
    id = project.sgId()
    if sg.deleteEntity("Project", id):
        print "Project entity with id, %d, deleted!" % id
    else:
        print "Project entity with id, %d, not deleted! - it may be retired or non-existent" % id

except SgError, e:
    print "SgError:", e
except Exception, e:
    print "Error:", e

