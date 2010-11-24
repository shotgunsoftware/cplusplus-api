###############################################################################
# Attempt to make some sense out of the namespaces sip generates
#
# -----------------------------------------------------------------------------
# Before:
#   import _siteshotgun
#   try:
#       sg = _siteshotgun.SiteSG.Shotgun("...")
#   except _siteshotgun.SgError, e:
#       print "SgError:", e
#
# -----------------------------------------------------------------------------
# After:
#   import siteshotgun
#   try:
#       sg = siteshotgun.Shotgun("...")
#   except siteshotgun.SgError, e:
#        print "SgError:", e
#
# OR even simpler:
#   from siteshotgun import *
#   try:
#       sg = Shotgun("...")
#   except SgError, e:
#        print "SgError:", e
#
#
# NOTE: If any of the base class and its derived class share the same name, 
#       (3) needs to be done AFTER (2) so that the derived class will override 
#       its base class in the globals() dictionary.
###############################################################################

import _siteshotgun
import inspect

# (1)
for (_sgClassName, _sgClass) in inspect.getmembers(_siteshotgun, 
                                                   inspect.isclass):
    globals()[_sgClassName] = _sgClass

# (2)
for (_sgClassName, _sgClass) in inspect.getmembers(_siteshotgun.SG, 
                                                   inspect.isclass):
    globals()[_sgClassName] = _sgClass

# (3)
for (_sgClassName, _sgClass) in inspect.getmembers(_siteshotgun.SiteSG, 
                                                   inspect.isclass):
    globals()[_sgClassName] = _sgClass


del _sgClassName
del _sgClass
del inspect
del _siteshotgun

###############################################################################
class SiteShotgunWrapper(SiteShotgun):
    """
    A wrapper around the SiteShotgun class.
    """

    # -------------------------------------------------------------------------
    def entityType(self, classType):
        """
        Converts a class type to its corresponding Shotgun entity type.
        """

        if classType == "SiteReference":
            return "CustomEntity02"
        elif classType == "SiteProject":
            return "Project"
        else:
            return classType

    # -------------------------------------------------------------------------
    def createEntity(self, classType, data, extraReturnFields = List()):
 
        return SiteShotgun.createEntity(self,
                                        self.entityType(classType),
                                        data,
                                        extraReturnFields)

    # -------------------------------------------------------------------------
    def findEntity(self, classType, 
                         filterList = FilterBy(), 
                         extraReturnFields = List(), 
                         retiredOnly = False, 
                         order = SortBy()):

        return SiteShotgun.findEntity(self,
                                      self.entityType(classType),
                                      filterList,
                                      extraReturnFields,
                                      retiredOnly,
                                      order)

    # -------------------------------------------------------------------------
    def findEntities(self, classType, 
                           filterList = FilterBy(), 
                           limit = 0, 
                           extraReturnFields = List(), 
                           retiredOnly = False, 
                           order = SortBy()):

        return SiteShotgun.findEntities(self,
                                        self.entityType(classType),
                                        filterList,
                                        limit,
                                        extraReturnFields,
                                        retiredOnly,
                                        order)

    # -------------------------------------------------------------------------
    def deleteEntity(self, classType, id):

        return SiteShotgun.deleteEntity(self, 
                                        self.entityType(classType), 
                                        id)

