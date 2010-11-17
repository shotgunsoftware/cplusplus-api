###############################################################################
# Attempt to make some sense out of the namespaces sip generates
#
# Before:
#   import _shotgun
#   import _siteshotgun
#   try:
#       sg = _siteshotgun.SiteSG.Shotgun("...")
#   except _shotgun.SgError, e:
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
#     "SG" and "SiteSG", respectively. If no base class and its derived classe
#     share the same name and you'd like to remove the namespaces, you'll need to
#     handle both "_shotgun.SG" and "_siteshotgun.SiteSG", which means both "Part1"
#     and "Part2" are needed.
#
# (3) If "_siteshotgun" and "_shotgun" use different namespaces, and if any
#     of the base and its derived class share the same name, "Part2" needs
#     to be done AFTER "Part1" so that the derived class will override its
#     base class in the globals() dictionary.
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

#############################
# Part2: _siteshotgun.TipSG #
#############################
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

