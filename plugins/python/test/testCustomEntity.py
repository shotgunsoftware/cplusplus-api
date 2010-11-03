#!/usr/bin/env python

import sys
from shotgun import *

try:
    if len(sys.argv) > 1:
        sg = Shotgun(sys.argv[1])
    else:
        sg = Shotgun()

    #################################################################
    # Find CustomEntity01 entities
    #################################################################
    print "*" * 40, "findEntities - CustomEntity01", "*" * 40
    for entity in sg.findEntities("CustomEntity01", FilterBy(), 5):
        #print entity
        #print "-" * 40
        print "%s : %s" % (entity.sgProjectCode(), entity.getAttrValue("code"))

    #################################################################
    # Find CustomEntity02 entities
    #################################################################
    print "*" * 40, "findEntities - CustomEntity02", "*" * 40
    for entity in sg.findEntities("CustomEntity02", FilterBy(), 5):
        #print entity
        #print "-" * 40
        print "%s : %s" % (entity.sgProjectCode(), entity.getAttrValue("code"))

except SgError, e:
    print "SgError:", e
except Exception, e:
    print "Error:", e

