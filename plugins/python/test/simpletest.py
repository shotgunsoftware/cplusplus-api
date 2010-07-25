#!/usr/bin/env python

import sys
sys.path.insert(0, "..")

from shotgun import *

try:
    if len(sys.argv) > 1:
        sg = Shotgun(sys.argv[1])
    else:
        sg = Shotgun()

    myMethod = sg.method("system.listMethods")
    
    print "Signature:", myMethod.signature()
    print "Help:", myMethod.help()
    print "Results:"
    for result in myMethod.call():
        print "  ", result

except Exception, e:
    print "Error:", e
