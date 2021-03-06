# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

#[[
	Yall objects compilation
#]]

file(GLOB_RECURSE YALL_SRCS ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/include/*.h)

add_library(yall SHARED ${YALL_SRCS})

if (UNIX)
	# For more infos about the used flags :
	#	* https://stackoverflow.com/questions/3375697/useful-gcc-flags-for-c
	#	* https://kristerw.blogspot.fr/2017/09/useful-gcc-warning-options-not-enabled.html
	# Compile options
	set(_PVT_OPT -Wall -Wextra -Wconversion -ftrapv -Wfloat-equal -Wundef
		-Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes
		-Wwrite-strings -Waggregate-return -Wuninitialized
		-Wduplicated-cond -Wlogical-op -Wnull-dereference -Wdouble-promotion
		-fvisibility=hidden -fPIC)
	set(_PVT_OPT_DEBUG  -O0 -g)
	set(_PVT_OPT_RELEASE -O3 -Werror)
elseif (WIN32)
	# Compile options

	#[[
		* 4204 : non-const initializer
		* 4115 : named type defininition in parenthesis
		* 4127 : constant conditional expression
		* 4255 : no function prototype given
		* 4668 : macro not defined, replaced by 0
		* 4706 : assignment within conditional expression
		* 4710 : function not inlined
		* 4774 : argument is not a string literal
		* 4820 : padding
		* 4996 : "strdup" deprecated
	#]]

	set(_PVT_OPT /wd4204 /wd4115 /wd4127 /wd4255 /wd4668 /wd4706 /wd4710 /wd4774 /wd4820 /wd4996 /Wall)
	set(_PVT_OPT_DEBUG /Od)
	set(_PVT_OPT_RELEASE /W4 /O2 /MP)

	# Compile definitions
	set(_PVT_DEF _CRT_SECURE_NO_WARNINGS)

	set_property(TARGET yall PROPERTY FOLDER "library")
endif ()

target_compile_options(yall
	PRIVATE
		${_PVT_OPT}
		$<$<CONFIG:DEBUG>:${_PVT_OPT_DEBUG}>
		$<$<CONFIG:RELEASE>:${_PVT_OPT_RELEASE}>)

target_compile_definitions(yall
	PRIVATE ${_PVT_DEF})

target_include_directories(yall
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	PRIVATE
		${CMAKE_BINARY_DIR}/generated_headers)

target_link_libraries(yall
	PUBLIC
		pthread::pthread
	PRIVATE
		jansson::jansson)


#[[
    Installing target
#]]

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
	"${CMAKE_BINARY_DIR}/cmake/yall-config-version.cmake"
	VERSION ${YALL_VERSION}
	COMPATIBILITY ExactVersion)

configure_package_config_file(
	"${CMAKE_SOURCE_DIR}/resources/cmake/yall-config.cmake.in"
	"${CMAKE_BINARY_DIR}/cmake/yall-config.cmake"
	INSTALL_DESTINATION lib/cmake/yall)

if (UNIX)
	configure_file(${CMAKE_SOURCE_DIR}/resources/cmake/yall_targets-release.cmake.linux ${CMAKE_BINARY_DIR}/cmake/yall_targets-release.cmake COPYONLY)
else ()
	configure_file(${CMAKE_SOURCE_DIR}/resources/cmake/yall_targets-release.cmake.windows ${CMAKE_BINARY_DIR}/cmake/yall_targets-release.cmake COPYONLY)
endif ()

install(
	FILES ${CMAKE_SOURCE_DIR}/README.md
	DESTINATION share/yall
	CONFIGURATIONS Release)

install(TARGETS yall EXPORT yall_targets
	RUNTIME DESTINATION bin CONFIGURATIONS Release Debug
	ARCHIVE DESTINATION lib CONFIGURATIONS Release Debug
	LIBRARY DESTINATION lib CONFIGURATIONS Release Debug
	INCLUDES DESTINATION include)

install(
	DIRECTORY ${CMAKE_SOURCE_DIR}/include
	DESTINATION ./
	CONFIGURATIONS Debug
	PATTERN "version.h.in" EXCLUDE)

if (WIN32)
	install(
		FILES ${CMAKE_SOURCE_DIR}/external/bin/pthreadVC2.dll
		DESTINATION bin
		CONFIGURATIONS Release)
endif ()

install(
	FILES
		"${CMAKE_BINARY_DIR}/cmake/yall-config.cmake"
		"${CMAKE_BINARY_DIR}/cmake/yall-config-version.cmake"
		"${CMAKE_BINARY_DIR}/cmake/yall_targets-release.cmake"
		"${CMAKE_SOURCE_DIR}/resources/cmake/module/Findpthread.cmake"
	DESTINATION lib/cmake/yall
	CONFIGURATIONS Debug)
	
install(EXPORT yall_targets
	DESTINATION lib/cmake/yall
	NAMESPACE yall::
	CONFIGURATIONS Debug)

if (WIN32)
	install(FILES $<TARGET_PDB_FILE:yall> DESTINATION bin OPTIONAL)
endif ()


#[[
	Packaging
#]]
if (UNIX)
    set(CPACK_GENERATOR "DEB;ZIP;RPM")
elseif (WIN32)
    set(CPACK_GENERATOR "ZIP")
endif ()

set(CPACK_OUTPUT_FILE_PREFIX out/packages)
set(CPACK_PACKAGE_NAME "yall")
set(CPACK_PACKAGE_VERSION_MAJOR ${YALL_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${YALL_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${YALL_VERSION_PATCH})

set(CPACK_COMPILER ${COMPILER})
set(CPACK_YALL_BUILD_TYPE ${CMAKE_BUILD_TYPE})

set(CPACK_PROJECT_CONFIG_FILE ${CMAKE_SOURCE_DIR}/resources/cmake/cpack_config_file.cmake)

include(CPack)