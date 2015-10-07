# Locate RapidJSON library
# This module defines
# RAPIDJSON_FOUND, if true, library is found
# RAPIDJSON_INCLUDE_DIR, directory path where to find
# 	rapidjson directory with all necessary headers.
# 
# $RAPIDJSONDIR is an environment variable that
# would correspond to the installation path.
#
# TODO: Test it under OSX, Linux
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

find_path(RAPIDJSON_INCLUDE_DIR rapidjson/rapidjson.h
	HINTS
	$ENV{RAPIDJSONDIR}
	PATH_SUFFIXES rapidjson/include include
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(RAPIDJSON REQUIRED_VARS RAPIDJSON_INCLUDE_DIR)