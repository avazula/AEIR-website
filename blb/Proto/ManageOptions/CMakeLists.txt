# -----------------------------------------------------------------------------
# Author:  IT&Labs - Orange Business Services
# Version: 1.0.0
# Date:    April 2014
# ----------------------------------------------------------------------------- 

# Specifiy all library source files
# ----------------------------------------------------------------------------- 
set(MANAGE_OPTIONS_SRC
    ManageOptions.h
        ManageOptions.cpp
)

# Specifiy target
# ----------------------------------------------------------------------------- 
add_library(ManageOptions STATIC ${MANAGE_OPTIONS_SRC})
target_link_libraries( ManageOptions )


