## CMakeLists.txt                                       -*- CMake -*-
##
## Copyright (C) 2006-2017 Christian Schenk
## 
## This file is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published
## by the Free Software Foundation; either version 2, or (at your
## option) any later version.
## 
## This file is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this file; if not, write to the Free Software
## Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
## USA.

set(MIKTEX_CURRENT_FOLDER "${MIKTEX_IDE_MIKTEX_PACKAGE_MANAGER_FOLDER}")

use_static_crt()

set(mpm_sources
  StdAfx.h
  internal.h
  mpm-version.h
  mpm.cpp
)

if(MIKTEX_NATIVE_WINDOWS)
  add_definitions(
    -DUNICODE
    -D_UNICODE
  )
endif()

if(MIKTEX_NATIVE_WINDOWS)
  list(APPEND mpm_sources
    ${MIKTEX_COMPATIBILITY_MANIFEST}
    mpm.rc
  )
endif()

add_executable(mpm ${mpm_sources})

set_property(TARGET mpm PROPERTY FOLDER ${MIKTEX_CURRENT_FOLDER})

if(USE_SYSTEM_LOG4CXX)
  target_link_libraries(mpm MiKTeX::Imported::LOG4CXX)
else()
  target_link_libraries(mpm ${log4cxx_lib_name})
endif()

target_link_libraries(mpm
  ${core_lib_name}
  ${mpm_lib_name}
  miktex-popt-wrapper-static
)

if(MIKTEX_NATIVE_WINDOWS)
  target_link_libraries(mpm
    Wldap32
    shlwapi
    wininet
    winmm
    ws2_32
  )
endif()

install(TARGETS mpm DESTINATION ${MIKTEX_BINARY_DESTINATION_DIR})
