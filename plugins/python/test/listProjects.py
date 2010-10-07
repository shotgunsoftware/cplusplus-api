#!/usr/bin/env python

import sys
from shotgun import *

try:
    if len(sys.argv) > 1:
        sg = Shotgun(sys.argv[1])
    else:
        sg = Shotgun()

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
                           .add("sg_default_start_frame", 101))
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

    #################################################################
    # Find the Project entity which has just been deleted
    #################################################################
    print "*" * 40, "findEntity", "*" * 40
    project = sg.findEntity("Project", FilterBy("code", "is", "tp"))
    print project

except SgError, e:
    print "SgError:", e
except Exception, e:
    print "Error:", e

