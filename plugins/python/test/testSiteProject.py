#!/usr/bin/env python

import sys
from shotgun import *

def usage():
    print
    print "Usage: testSiteProject [options]"
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

        sg = SiteShotgun(shotgunURL, authName, authKey)
    else:
        print
        print "ERROR: Missing arguments..."

        usage()
        sys.exit(0)

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

