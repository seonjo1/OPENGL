# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-build"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/tmp"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-stamp"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src"
  "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/seonjo/Desktop/opengl/opengl_example/build/dep-spdlog-prefix/src/dep-spdlog-stamp${cfgdir}") # cfgdir has leading slash
endif()
