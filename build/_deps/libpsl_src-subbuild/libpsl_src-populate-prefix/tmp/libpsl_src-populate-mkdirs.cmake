# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/raf/Documents/mlbterm/build/_deps/libpsl_src-src")
  file(MAKE_DIRECTORY "/home/raf/Documents/mlbterm/build/_deps/libpsl_src-src")
endif()
file(MAKE_DIRECTORY
  "/home/raf/Documents/mlbterm/build/_deps/libpsl_src-build"
  "/home/raf/Documents/mlbterm/build/_deps/libpsl_src-subbuild/libpsl_src-populate-prefix"
  "/home/raf/Documents/mlbterm/build/_deps/libpsl_src-subbuild/libpsl_src-populate-prefix/tmp"
  "/home/raf/Documents/mlbterm/build/_deps/libpsl_src-subbuild/libpsl_src-populate-prefix/src/libpsl_src-populate-stamp"
  "/home/raf/Documents/mlbterm/build/_deps/libpsl_src-subbuild/libpsl_src-populate-prefix/src"
  "/home/raf/Documents/mlbterm/build/_deps/libpsl_src-subbuild/libpsl_src-populate-prefix/src/libpsl_src-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/raf/Documents/mlbterm/build/_deps/libpsl_src-subbuild/libpsl_src-populate-prefix/src/libpsl_src-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/raf/Documents/mlbterm/build/_deps/libpsl_src-subbuild/libpsl_src-populate-prefix/src/libpsl_src-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
