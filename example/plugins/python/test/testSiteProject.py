#!/usr/bin/env python

import sys
from siteshotgun import *

try:
    if len(sys.argv) > 1:
        sg = SiteShotgunWrapper(sys.argv[1])
    else:
        sg = SiteShotgunWrapper()

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

