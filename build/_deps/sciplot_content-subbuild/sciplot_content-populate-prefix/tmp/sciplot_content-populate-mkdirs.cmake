# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/duskel/Documents/Github/textures_data/build/_deps/sciplot_content-src"
  "/home/duskel/Documents/Github/textures_data/build/_deps/sciplot_content-build"
  "/home/duskel/Documents/Github/textures_data/build/_deps/sciplot_content-subbuild/sciplot_content-populate-prefix"
  "/home/duskel/Documents/Github/textures_data/build/_deps/sciplot_content-subbuild/sciplot_content-populate-prefix/tmp"
  "/home/duskel/Documents/Github/textures_data/build/_deps/sciplot_content-subbuild/sciplot_content-populate-prefix/src/sciplot_content-populate-stamp"
  "/home/duskel/Documents/Github/textures_data/build/_deps/sciplot_content-subbuild/sciplot_content-populate-prefix/src"
  "/home/duskel/Documents/Github/textures_data/build/_deps/sciplot_content-subbuild/sciplot_content-populate-prefix/src/sciplot_content-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/duskel/Documents/Github/textures_data/build/_deps/sciplot_content-subbuild/sciplot_content-populate-prefix/src/sciplot_content-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/duskel/Documents/Github/textures_data/build/_deps/sciplot_content-subbuild/sciplot_content-populate-prefix/src/sciplot_content-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
