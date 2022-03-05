TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#========================================

#========================================
# Build the IOC application

PROD_IOC = D1-FCT0
# D1-FCT0.dbd will be created and installed
DBD += D1-FCT0.dbd

# D1-FCT0.dbd will be made up from these files:
-include $(EPICS_ROOT)/mk/codac-common.mk


# Add all the support libraries needed by this IOC
-include $(EPICS_ROOT)/mk/picmg.mk

D1-FCT0_DBD += $(CODAC_DBD)
D1-FCT0_LIBS += $(CODAC_LIBS)

# # SNCSEQ
# <sncProgram>_SNCFLAGS += +r -c +d
# D1-FCT0_DBD += <sncProgram>.dbd
# D1-FCT0_SRCS += <sncProgram>.stt
# D1-FCT0_LIBS += seq pv


# D1-FCT0_registerRecordDeviceDriver.cpp derives from D1-FCT0.dbd
D1-FCT0_SRCS += D1-FCT0_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
D1-FCT0_SRCS_DEFAULT += D1-FCT0Main.cpp
D1-FCT0_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#D1-FCT0_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

#=============================
# Include SNL program makefile snippets

-include ../*.snlprog

#=============================
#=============================
# Include user.mk makefile snippets

-include ../user.mk

#=============================

# Finally link to the EPICS Base libraries
D1-FCT0_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
#----------------------------------------

