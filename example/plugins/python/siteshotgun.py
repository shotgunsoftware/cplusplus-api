
###############################################################################
# Attempt to make some sense out of the namespaces sip generates
#
# Before: 
#   import _shotgun
#   import _siteshotgun
#   try:
#       sg = _siteshotgun.SiteSG.Shotgun("...")
#   except _shotgun.SG.SgError, e:
#       print "SgError:", e
#
# After:
#   import siteshotgun
#   try:
#       sg = siteshotgun.Shotgun("...")
#   except siteshotgun.SgError, e:
#        print "SgError:", e
#
#
# (1) In the case of "_siteshotgun" and "_shotgun" using the same namespace,
#     SIP implements a C++ namespace as a single Python class - in this case 
#     "_shotgun.SG".
#
#     It does not implement it as a separate class in each module. In other 
#     words, in this case, it does not implement it as "_shotgun.SG" AND 
#     "_siteshotgun.SG".
#
#     When the "_siteshotgun" module is imported the contents of the SG 
#     namespace that it implements are added to the SG class in the "_shotgun" 
#     module.
#
#     Therefore, we need to import "_shotgun" module as well. But only "Part1"
#     is needed.
# 
# (2) In our current case, "_siteshotgun" and "_shotgun" use different namespaces,
#     "SG" and "SiteSG", respectively. So we'll need to handle both "_shotgun.SG"
#     and "_siteshotgun.SiteSG", which means both "Part1" and "Part2" are needed.
###############################################################################

import _shotgun
import _siteshotgun
import inspect

######################
# Part1: _shotgun.SG #
######################
for (_sgClassName, _sgClass) in inspect.getmembers(_shotgun, 
                                                   inspect.isclass):
    globals()[_sgClassName] = _sgClass

for (_sgClassName, _sgClass) in inspect.getmembers(_shotgun.SG, 
                                                   inspect.isclass):
    globals()[_sgClassName] = _sgClass

##########################
# Part2: _siteshotgun.SG #
##########################
for (_sgClassName, _sgClass) in inspect.getmembers(_siteshotgun, 
                                                   inspect.isclass):
    globals()[_sgClassName] = _sgClass

for (_sgClassName, _sgClass) in inspect.getmembers(_siteshotgun.SiteSG, 
                                                   inspect.isclass):
    globals()[_sgClassName] = _sgClass


del _sgClassName
del _sgClass
del inspect
del _shotgun
del _siteshotgun
