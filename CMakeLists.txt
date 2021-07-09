cmake_minimum_required(VERSION 3.20)

project(euler-set-solver)

if (WIN32 AND CMAKE_GENERATOR MATCHES "Visual Studio")
  macro(nuget_add TARGET PKG_NAME VERSION)
    unset(NUGET_COMMAND)
    list(APPEND NUGET_COMMAND install ${PKG_NAME} -Version ${VERSION} -OutputDirectory ${CMAKE_CURRENT_BINARY_DIR}/packages)
    list(APPEND DOTNET_REFS "${CMAKE_CURRENT_BINARY_DIR}/packages/${PKG_NAME}.${VERSION}/lib/net45/${PKG_NAME}.dll")

    execute_process(COMMAND nuget ${NUGET_COMMAND} ENCODING AUTO)
    set_target_properties(${TARGET} PROPERTIES VS_DOTNET_REFERENCES "${DOTNET_REFS}")
  endmacro()


  add_executable(euler-set-solver)

  set(DOTNET_REFS "System;System.Core;System.Drawing")

  set_target_properties(euler-set-solver PROPERTIES COMMON_LANGUAGE_RUNTIME "")
  set_target_properties(euler-set-solver PROPERTIES DOTNET_TARGET_FRAMEWORK_VERSION "v4.8")
  set_target_properties(euler-set-solver PROPERTIES VS_DOTNET_REFERENCES "${DOTNET_REFS}")

  nuget_add(euler-set-solver Wolfram.Alpha 1.0.7)
  nuget_add(euler-set-solver Colorful.Console 1.2.9)
  nuget_add(euler-set-solver Newtonsoft.Json 10.0.3)

  target_sources(euler-set-solver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/converter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/expression.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/set.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/set-op.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/wolfram-wrapper.cpp
  )
  target_include_directories(euler-set-solver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  )
endif()
