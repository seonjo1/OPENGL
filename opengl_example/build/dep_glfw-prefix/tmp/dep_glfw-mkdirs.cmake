# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep_glfw-prefix/src/dep_glfw"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep_glfw-prefix/src/dep_glfw-build"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep_glfw-prefix"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep_glfw-prefix/tmp"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep_glfw-prefix/src/dep_glfw-stamp"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep_glfw-prefix/src"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep_glfw-prefix/src/dep_glfw-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep_glfw-prefix/src/dep_glfw-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep_glfw-prefix/src/dep_glfw-stamp${cfgdir}") # cfgdir has leading slash
endif()
