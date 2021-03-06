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
# Locate cppformat library
#
# This module defines:
# CPPFORMAT_FOUND, if true, library is found
# CPPFORMAT_INCLUDE_DIR, directory path where to find
# 	rapidjson directory with all necessary headers.
# CPPFORMAT_LIBRARY, the name of the library to link against.
# CPPFORMAT_LIBRARY_DEBUG, the name of the debug library to link against.
# 
# $CPPFORMAT_ROOT is an environment variable that
# would point to the installation path.

set(CPPFORMAT_PATHS	${CPPFORMAT_ROOT}
					$ENV{CPPFORMAT_ROOT}
)

if(NOT DEFINED DEBUG_LIB_SUFFIX)
	set(DEBUG_LIB_SUFFIX -d)
endif()

find_path(CPPFORMAT_INCLUDE_DIR cppformat/format.h 
	PATH_SUFFIXES include PATHS ${CPPFORMAT_PATHS}
)

find_library(CPPFORMAT_LIBRARY NAMES cppformat 
	PATH_SUFFIXES lib 
	PATHS ${CPPFORMAT_PATHS}
)

find_library(CPPFORMAT_LIBRARY_DEBUG NAMES cppformat${DEBUG_LIB_SUFFIX}
	PATH_SUFFIXES lib
	PATHS ${CPPFORMAT_PATHS}
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(CPPFORMAT REQUIRED_VARS CPPFORMAT_INCLUDE_DIR CPPFORMAT_LIBRARY CPPFORMAT_LIBRARY_DEBUG)
