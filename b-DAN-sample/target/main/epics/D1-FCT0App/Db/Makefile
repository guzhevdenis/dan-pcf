TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

#----------------------------------------------------
#  Optimization of db files using dbst (DEFAULT: NO)
#DB_OPT = YES

#----------------------------------------------------
# Create and install (or just install) into <top>/db
# databases, templates, substitutions like this
DB += PCF0-D1-FCT0-SYSM-iocD1-FCT0-PCF0CORE.db
DB += PCF0-D1-FCT0-SYSM-iocD1-FCT0-PCF0SYSM.db
DB += PSH0-D1-FCT0-SYSM-iocD1-FCT0-PSH0CORE.db
DB += PSH0-D1-FCT0-SYSM-iocD1-FCT0-PSH0SYSM.db

# Automagically install .proto files
DB += $(notdir $(wildcard ../*.proto))

#----------------------------------------------------
# If <anyname>.db template is not named <anyname>*.template add
# <anyname>_template = <templatename>

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
