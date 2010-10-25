
#
# Attempt to make some sense out of the namespaces sip generates
#
# Before: 
#   import _siteshotgun
#   sg = _siteshotgun.SG.Shotgun("...")
#
# After:
#   import siteshotgun
#   sg = siteshotgun.Shotgun("...")
#


import inspect
import _siteshotgun

for (_sgClassName, _sgClass) in inspect.getmembers(_siteshotgun, 
                                                   inspect.isclass):
    globals()[_sgClassName] = _sgClass

for (_sgClassName, _sgClass) in inspect.getmembers(_siteshotgun.SG, 
                                                   inspect.isclass):
    globals()[_sgClassName] = _sgClass

del _sgClassName
del _sgClass
del inspect
del _siteshotgun
