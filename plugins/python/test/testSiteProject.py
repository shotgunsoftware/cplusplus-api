#!/usr/bin/env python

import sys
from shotgun import *

try:
    if len(sys.argv) > 1:
        sg = SiteShotgun(sys.argv[1])
    else:
        sg = SiteShotgun()

    #################################################################
    # Find all the SiteProject entities
    #################################################################
    print "*" * 40, "findEntities", "*" * 40
    for project in sg.findEntities("SiteProject"):
        print project
        # These are SiteProject-specific convenience functions.
        print project.sgName()
        print project.sgCode()
        print "-" * 40

except SgError, e:
    print "SgError:", e
except Exception, e:
    print "Error:", e

