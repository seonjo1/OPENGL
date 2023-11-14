# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/seonjo/Desktop/opengl/opengl_example/out/build/x64-Debug/dep_stb-prefix/src/dep_stb"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/out/build/x64-Debug/dep_stb-prefix/src/dep_stb-build"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/out/build/x64-Debug/dep_stb-prefix"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/out/build/x64-Debug/dep_stb-prefix/tmp"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/out/build/x64-Debug/dep_stb-prefix/src/dep_stb-stamp"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/out/build/x64-Debug/dep_stb-prefix/src"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/out/build/x64-Debug/dep_stb-prefix/src/dep_stb-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/seonjo/Desktop/opengl/opengl_example/out/build/x64-Debug/dep_stb-prefix/src/dep_stb-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/seonjo/Desktop/opengl/opengl_example/out/build/x64-Debug/dep_stb-prefix/src/dep_stb-stamp${cfgdir}") # cfgdir has leading slash
endif()
