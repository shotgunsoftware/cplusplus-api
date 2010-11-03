#!/usr/bin/env python

import sys
from siteshotgun import *

try:
    if len(sys.argv) > 1:
        sg = SiteShotgun(sys.argv[1])
    else:
        sg = SiteShotgun()

    #################################################################
    # Find all the SiteReference entities
    #################################################################
    print "*" * 40, "findEntities", "*" * 40
    for reference in sg.findEntities("SiteReference", FilterBy(), 5):
        print reference
        # These are SiteReference-specific convenience functions.
        print reference.sgCode()
        print "-" * 40

except SgError, e:
    print "SgError:", e
except Exception, e:
    print "Error:", e

