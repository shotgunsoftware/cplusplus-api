
#
# Attempt to make some sense out of the namespaces sip generates
#
# Before: 
#   import _shotgun
#   sg = _shotgun.SG.Shotgun("...")
#
# After:
#   import shotgun
#   sg = shotgun.Shotgun("...")
#


import inspect
import _shotgun

for (_sgClassName, _sgClass) in inspect.getmembers(_shotgun, 
                                                   inspect.isclass):
    globals()[_sgClassName] = _sgClass

for (_sgClassName, _sgClass) in inspect.getmembers(_shotgun.SG, 
                                                   inspect.isclass):
    globals()[_sgClassName] = _sgClass

del _sgClassName
del _sgClass
del inspect
del _shotgun
