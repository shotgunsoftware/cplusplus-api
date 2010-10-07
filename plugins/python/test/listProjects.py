#!/usr/bin/env python

import sys
from shotgun import *

try:
    if len(sys.argv) > 1:
        sg = Shotgun(sys.argv[1])
    else:
        sg = Shotgun()

    print "*" * 80
    for project in sg.findEntities("Project"):
        print project
        print "-" * 40

except SgError, e:
    print "SgError:", e
except Exception, e:
    print "Error:", e

