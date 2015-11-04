#==============================================================================
# Copyright (c) 2015 Frozen Team.
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation 
# the rights to use, copy, modify, merge, publish, distribute, sublicense, 
# and/or sell copies of the Software, and to permit persons to whom the 
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included 
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
# SOFTWARE.
#==============================================================================
# Locate GLEW library
#
# This module defines:
# GLEW_FOUND, if true, library is found
# GLEW_INCLUDE_DIR, directory path where to find
# 	rapidjson directory with all necessary headers.
# GLEW_LIBRARY, the name of the library to link against.
# GLEW_LIBRARY_DEBUG, the name of the debug library to link against.
# 
# $GLEW_ROOT is an environment variable that
# would point to the installation path.

set(GLEW_PATHS ${GLEW_ROOT} $ENV{GLEW_ROOT} )

# TODO: Suffix must be -d. Workaround for now.
set(GLEW_DEBUG_LIB_SUFFIX d)

find_path(GLEW_INCLUDE_DIR GL/glew.h 
	PATH_SUFFIXES include PATHS ${GLEW_PATHS}
)

find_library(GLEW_LIBRARY NAMES libglew32 
	PATH_SUFFIXES lib 
	PATHS ${GLEW_PATHS}
)

find_library(GLEW_LIBRARY_DEBUG NAMES "libglew32${GLEW_DEBUG_LIB_SUFFIX}"
	PATH_SUFFIXES lib
	PATHS ${GLEW_PATHS}
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(GLEW REQUIRED_VARS GLEW_INCLUDE_DIR GLEW_LIBRARY GLEW_LIBRARY_DEBUG)