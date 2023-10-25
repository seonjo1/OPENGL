# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep_glad-prefix/src/dep_glad"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep_glad-prefix/src/dep_glad-build"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep_glad-prefix"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep_glad-prefix/tmp"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep_glad-prefix/src/dep_glad-stamp"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep_glad-prefix/src"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep_glad-prefix/src/dep_glad-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep_glad-prefix/src/dep_glad-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep_glad-prefix/src/dep_glad-stamp${cfgdir}") # cfgdir has leading slash
endif()
