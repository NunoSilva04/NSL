cmake_minimum_required(VERSION 3.20)

project(nsl VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(source_files Source/nsl_math.cpp)

add_library(${PROJECT_NAME} STATIC ${source_files})
target_include_directories(${PROJECT_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)



add_library(nsl::nsl ALIAS nsl)

# To install the library and headers
install(TARGETS ${PROJECT_NAME} EXPORT nslTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY Include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/nsl)

# To Install the package
configure_package_config_file(
    cmake/nslConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/nslConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/nsl
)

install(EXPORT nslTargets
    FILE nslTargets.cmake
    NAMESPACE nsl::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/nsl
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/nslConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/nslConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/nslConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/nsl
)


# Uninstallation
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    @ONLY 
)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
)
