# CMakeList.txt : CMake project for CefImpl, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")

include_directories(.)

set(project_name "CMakeTest")

# Add source to this project's executable.
add_executable (${project_name} "CmakeTest.cpp" "CmakeTest.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${project_name} PROPERTY CXX_STANDARD 20)
endif()



set(copy_source_dir "${CMAKE_SOURCE_DIR}/${project_name}")
set(copy_dest_dir "${CMAKE_BINARY_DIR}/${project_name}")

set(libs_dir "${CMAKE_SOURCE_DIR}/${project_name}/libs")
set(resources_dir "${CMAKE_SOURCE_DIR}/${project_name}/resources")

set(LIBS_SOURCE
	${libs_dir}/libcef.lib
	${libs_dir}/libcef_dll_wrapper.lib
	${libs_dir}/cef_sandbox.lib
)

set(DLL_LIBS
	chrome_elf.dll
	d3dcompiler_47.dll
	libcef.dll
	libEGL.dll
	libGLESv2.dll
	vk_swiftshader.dll
	vulkan-1.dll
)

foreach(DLL_LIB ${DLL_LIBS})
	add_custom_command(
        TARGET ${project_name} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${libs_dir}/${DLL_LIB}
                ${copy_dest_dir}/${DLL_LIB})

		message(STATUS "copying ${libs_dir}/${DLL_LIB} to  ${copy_dest_dir}/${DLL_LIB}")
endforeach()

set(RESOURCES
	chrome_100_percent.pak
	chrome_200_percent.pak
	icudtl.dat
	resources.pak
	v8_context_snapshot.bin
)

foreach(RESOURCES_FILE ${RESOURCES})
	add_custom_command(
        TARGET ${project_name} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${resources_dir}/${RESOURCES_FILE}
                ${copy_dest_dir}/${RESOURCES_FILE})

		message(STATUS "copying ${resources_dir}/${RESOURCES_FILE} to  ${copy_dest_dir}/${RESOURCES_FILE}")
endforeach()

set (LOCAL_FILES
	"${CMAKE_SOURCE_DIR}/${project_name}/resources/locales"
)

file(COPY ${LOCAL_FILES} DESTINATION ${copy_dest_dir})


target_link_libraries(${project_name} ${LIBS_SOURCE}) 