cmake_minimum_required(VERSION 3.20)

project(euler-set-solver)

#
# Windows with Visual Studio based generators only(?)
#
if (WIN32 AND CMAKE_GENERATOR MATCHES "Visual Studio")

#region macros

  #
  # just get list of all subdirectories for a given directory
  #
  # list of all subdirectories will be stored in the ${SUBDIRS} variable
  #
  macro(get_subdirs DIR)
    file(GLOB CHILDREN RELATIVE ${DIR} ${DIR}/*)
    set(DIRLIST "")

    foreach(CHILD ${CHILDREN})
      if(IS_DIRECTORY ${DIR}/${CHILD})
        list(APPEND DIRLIST ${CHILD})
      endif()
    endforeach()

    set(SUBDIRS ${DIRLIST})
  endmacro()

  #
  # find most suitable prebuild binary for a given downloaded NuGet package
  # from the "${CMAKE_CURRENT_BINARY_DIR}/packages/" directory that lower
  # than the greatest .NET Framework version for this project
  #
  # ${DOTNETF_VERSION} varaible must be set, for example:
  # set(DOTNETF_VERSION "v4.5")
  #
  # path to the suitable binary will be stored in the ${SUITABLE_BINARY} variable;
  # in case a suitable binary is not found, an error will be generated
  #
  macro(nuget_pkg_find_suitable PKG_NAME PKG_VERSION)
    set(DOTNETF_MAX ${DOTNETF_VERSION})
    string(REPLACE "v" "" DOTNETF_MAX ${DOTNETF_MAX})
    string(REPLACE "." "" DOTNETF_MAX ${DOTNETF_MAX})

    set(LIBX_NETF_VERSION 0)

    set(PKG_DIR ${CMAKE_CURRENT_BINARY_DIR}/packages/${PKG_NAME}.${PKG_VERSION}/lib)
    get_subdirs(${PKG_DIR})

    # TODO: fix 3-to-2-digit comparison: for example, "net451" must be lower than "net46"
    foreach(LIBX_DIR ${SUBDIRS})
      set(CURRENT_NETF_VERSION "")
      string(REPLACE "net" "" CURRENT_NETF_VERSION ${LIBX_DIR})

      if ((CURRENT_NETF_VERSION GREATER LIBX_NETF_VERSION) AND (CURRENT_NETF_VERSION LESS_EQUAL DOTNETF_MAX))
        set(LIBX_NETF_VERSION ${CURRENT_NETF_VERSION})
      endif()
    endforeach()

    if (NOT LIBX_NETF_VERSION EQUAL 0)
      set(SUITABLE_BINARY ${PKG_DIR}/net${LIBX_NETF_VERSION}/${PKG_NAME}.dll)
      message("\nFound suitable ${PKG_NAME} binary - ${SUITABLE_BINARY}\n")
    else()
      message(FATAL_ERROR "\nCannot found suitable ${PKG_NAME} binary for a given .NET Framework version(${DOTNETF_VERSION})\n")
    endif()
  endmacro()

  #
  # install NuGet package into "${CMAKE_CURRENT_BINARY_DIR}/packages/"
  # directory and add suitable reference for a given target
  #
  # result value is not provided
  #
  macro(nuget_pkg_add TARGET PKG_NAME PKG_VERSION)
    unset(NUGET_COMMAND)
    list(APPEND NUGET_COMMAND install ${PKG_NAME} -Version ${PKG_VERSION} -OutputDirectory ${CMAKE_CURRENT_BINARY_DIR}/packages)
    execute_process(COMMAND nuget ${NUGET_COMMAND} ENCODING AUTO)

    nuget_pkg_find_suitable(${PKG_NAME} ${PKG_VERSION})
    # append found suitable package binary to the
    # current .NET Framework references list
    list(APPEND DOTNET_REFS ${SUITABLE_BINARY})

    set_target_properties(${TARGET} PROPERTIES VS_DOTNET_REFERENCES "${DOTNET_REFS}")
  endmacro()

#endregion

  add_executable(euler-set-solver)
  target_compile_features(euler-set-solver PRIVATE cxx_std_17)

  # .NET Framework only(?)
  set(DOTNETF_VERSION "v4.8")
  # standart .NET references
  set(DOTNET_REFS "System;System.Core;System.Drawing")

  set_target_properties(euler-set-solver PROPERTIES COMMON_LANGUAGE_RUNTIME "")
  set_target_properties(euler-set-solver PROPERTIES DOTNET_TARGET_FRAMEWORK_VERSION "${DOTNETF_VERSION}")
  set_target_properties(euler-set-solver PROPERTIES VS_DOTNET_REFERENCES "${DOTNET_REFS}")

  # nuget_pkg_add(euler-set-solver Wolfram.Alpha 1.0.7)
  # nuget_pkg_add(euler-set-solver Newtonsoft.Json 10.0.3)
  nuget_pkg_add(euler-set-solver Colorful.Console 1.2.9)

  target_sources(euler-set-solver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/converter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/expression.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/set.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/set-operator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app.cpp
  )
  target_include_directories(euler-set-solver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  )

endif()
