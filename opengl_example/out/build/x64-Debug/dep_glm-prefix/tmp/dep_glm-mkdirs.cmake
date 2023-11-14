# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/seonjo/Desktop/opengl/opengl_example/out/build/x64-Debug/dep_glm-prefix/src/dep_glm"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/out/build/x64-Debug/dep_glm-prefix/src/dep_glm-build"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/out/build/x64-Debug/dep_glm-prefix"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/out/build/x64-Debug/dep_glm-prefix/tmp"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/out/build/x64-Debug/dep_glm-prefix/src/dep_glm-stamp"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/out/build/x64-Debug/dep_glm-prefix/src"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/out/build/x64-Debug/dep_glm-prefix/src/dep_glm-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/seonjo/Desktop/opengl/opengl_example/out/build/x64-Debug/dep_glm-prefix/src/dep_glm-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/seonjo/Desktop/opengl/opengl_example/out/build/x64-Debug/dep_glm-prefix/src/dep_glm-stamp${cfgdir}") # cfgdir has leading slash
endif()
