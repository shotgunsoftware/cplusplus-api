#!/usr/bin/env python

import sys
sys.path.insert(0, "..")

from shotgun import *

try:
    if len(sys.argv) > 1:
        sg = Shotgun(sys.argv[1])
    else:
        sg = Shotgun()

    for project in sg.allProjects():
        print project

except Exception, e:
    print "Error:", e

