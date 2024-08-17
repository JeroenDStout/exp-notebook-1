#
# Initial set-up
#

cmake_minimum_required(VERSION 3.15)

# Packages
include(cmake/generic/vcpkg.cmake)

# Project
project(notebook)
include(cmake/generic/project.cmake)
include(cmake/generic/publish.cmake)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Languages
include(cmake/generic/cxx.cmake)
include(cmake/generic/python.cmake)

# Support
include(cmake/generic/artefacts.cmake)
include(cmake/generic/sources.cmake)

# 3rd party
include(cmake/generic/uwebsockets.cmake)

# Subprojects
add_subdirectory(src/version)
add_subdirectory(src/server)

# Publication
finalise_publish()
