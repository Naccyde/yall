# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

if (UNIX)
    find_path(criterion_INCLUDE_DIR
        NAMES criterion/criterion.h
        PATHS ${criterion_HINTS} / /usr /usr/local
        PATH_SUFFIXES include)
        
    find_library(criterion_LIBRARY
        NAMES criterion
        PATHS ${criterion_HINTS} / /usr /usr/local
        PATH_SUFFIXES lib)
elseif (WIN32)
    find_path(criterion_INCLUDE_DIR
        NAMES criterion/criterion.h
        PATHS ${criterion_HINTS} C:/
        PATH_SUFFIXES include)

    find_library(criterion_LIBRARY
        NAMES criterion
        PATHS ${criterion_HINTS} C:/
        PATH_SUFFIXES lib)
endif ()

set(criterion_INCLUDE_DIRS "${criterion_INCLUDE_DIR}")
set(criterion_LIBRARIES "${criterion_LIBRARY}")

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    criterion
    REQUIRED_VARS
        criterion_INCLUDE_DIRS
        criterion_LIBRARIES)

set(criterion_FOUND "${CRITERION_FOUND}")

if(criterion_FOUND)
    message(STATUS "> criterion found")
    if (NOT TARGET criterion::criterion)
        add_library(criterion::criterion UNKNOWN IMPORTED)
    endif()

    set_target_properties(criterion::criterion PROPERTIES
        IMPORTED_LOCATION "${criterion_LIBRARIES}"
        INTERFACE_INCLUDE_DIRECTORIES "${criterion_INCLUDE_DIRS}")
    
    message(STATUS ">\t${criterion_LIBRARIES}")
    message(STATUS ">\t${criterion_INCLUDE_DIRS}")
else ()
    message(STATUS "> criterion not found")
endif ()

mark_as_advanced(criterion_INCLUDE_DIRS)
mark_as_advanced(criterion_LIBRARIES)
