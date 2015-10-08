# - Try to find Eigen lib
#
# Once done this will define
#
#  EIGEN_FOUND - system has eigen lib with correct version
#  EIGEN_INCLUDE_DIR - the eigen include directory
#  EIGEN_VERSION - eigen version

# Copyright (c) 2006, 2007 Montel Laurent, <montel@kde.org>
# Copyright (c) 2008, 2009 Gael Guennebaud, <g.gael@free.fr>
# Copyright (c) 2009 Benoit Jacob <jacob.benoit.1@gmail.com>
# Redistribution and use is allowed according to the terms of the 2-clause BSD license.

if(NOT Eigen_FIND_VERSION)
  if(NOT Eigen_FIND_VERSION_MAJOR)
    set(Eigen_FIND_VERSION_MAJOR 2)
  endif(NOT Eigen_FIND_VERSION_MAJOR)
  if(NOT Eigen_FIND_VERSION_MINOR)
    set(Eigen_FIND_VERSION_MINOR 91)
  endif(NOT Eigen_FIND_VERSION_MINOR)
  if(NOT Eigen_FIND_VERSION_PATCH)
    set(Eigen_FIND_VERSION_PATCH 0)
  endif(NOT Eigen_FIND_VERSION_PATCH)

  set(Eigen_FIND_VERSION "${Eigen_FIND_VERSION_MAJOR}.${Eigen_FIND_VERSION_MINOR}.${Eigen_FIND_VERSION_PATCH}")
endif(NOT Eigen_FIND_VERSION)

macro(_eigen_check_version)
  file(READ "${EIGEN_INCLUDE_DIR}/Eigen/src/Core/util/Macros.h" _eigen_version_header)

  string(REGEX MATCH "define[ \t]+EIGEN_WORLD_VERSION[ \t]+([0-9]+)" _eigen_world_version_match "${_eigen_version_header}")
  set(EIGEN_WORLD_VERSION "${CMAKE_MATCH_1}")
  string(REGEX MATCH "define[ \t]+EIGEN_MAJOR_VERSION[ \t]+([0-9]+)" _eigen_major_version_match "${_eigen_version_header}")
  set(EIGEN_MAJOR_VERSION "${CMAKE_MATCH_1}")
  string(REGEX MATCH "define[ \t]+EIGEN_MINOR_VERSION[ \t]+([0-9]+)" _eigen_minor_version_match "${_eigen_version_header}")
  set(EIGEN_MINOR_VERSION "${CMAKE_MATCH_1}")

  set(EIGEN_VERSION ${EIGEN_WORLD_VERSION}.${EIGEN_MAJOR_VERSION}.${EIGEN_MINOR_VERSION})
  if(${EIGEN_VERSION} VERSION_LESS ${Eigen_FIND_VERSION})
    set(EIGEN_VERSION_OK FALSE)
  else(${EIGEN_VERSION} VERSION_LESS ${Eigen_FIND_VERSION})
    set(EIGEN_VERSION_OK TRUE)
  endif(${EIGEN_VERSION} VERSION_LESS ${Eigen_FIND_VERSION})

  if(NOT EIGEN_VERSION_OK)

    message(STATUS "Eigen version ${EIGEN_VERSION} found in ${EIGEN_INCLUDE_DIR}, "
                   "but at least version ${Eigen_FIND_VERSION} is required")
  endif(NOT EIGEN_VERSION_OK)
endmacro(_eigen_check_version)

if (EIGEN_INCLUDE_DIR)

  # in cache already
  _eigen_check_version()
  set(EIGEN_FOUND ${EIGEN_VERSION_OK})

else (EIGEN_INCLUDE_DIR)
  find_path(EIGEN_INCLUDE_DIR NAMES eigen3/Eigenvalues eigen/Eigenvalues
      PATHS ${EIGEN_ROOT} $ENV{EIGEN_ROOT}
      PATH_SUFFIXES include
    )

  if(EIGEN_INCLUDE_DIR)
    _eigen_check_version()
  endif(EIGEN_INCLUDE_DIR)

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(Eigen DEFAULT_MSG EIGEN_INCLUDE_DIR EIGEN_VERSION_OK)

  mark_as_advanced(EIGEN_INCLUDE_DIR)

endif(EIGEN_INCLUDE_DIR)

