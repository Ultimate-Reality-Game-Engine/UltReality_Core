# CMakeList.txt : UltReality::UltReality_Managers

project(UltReality_Managers VERSION 1.0.0)

# Create options that are dependent onthis project being top level
option(ULTREALITY_MANAGERS_VERBOSE "Enable verbose messages for UtilitiesStatic" ${PROJECT_IS_TOP_LEVEL})

message(STATUS "ULTREALITY_MANAGERS_VERBOSE: ${ULTREALITY_MANAGERS_VERBOSE}")

# Target Creation *********************************************************************************
#**************************************************************************************************

option(ULTREALITY_MANAGERS_DEBUG "Enable CMake related debug messages" OFF)

file(GLOB_RECURSE Managers_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/*/src/*.cpp")
file(GLOB Managers_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

#message(STATUS "Managers_DIRS: ${Managers_DIRS}")
#message(STATUS ${Managers_SOURCE})

if(NOT DEFINED ULTREALITY_MANAGERS_BUILD)
	set(ULTREALITY_MANAGERS_BUILD ON)
endif()

if(ULTREALITY_MANAGERS_BUILD)
	# Create the UtilitiesStatic target
	if(Managers_SOURCE)
		add_library(UltReality_Managers STATIC ${Managers_SOURCE})

		# Set up include directories for the shared library target
		foreach(dir ${Managers_DIRS})
			if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${dir}/include")
				if(ULTREALITY_MANAGERS_DEBUG)	
					message(STATUS "Adding include directory: ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/include")
				endif()
				target_include_directories(UltReality_Managers PUBLIC 
					$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${dir}/include> 
 					$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/UltReality_Managers/${dir}> # This is used when the library is installed
				)
			endif()

			if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${dir}/inl")
				if(ULTREALITY_MANAGERS_DEBUG)	
					message(STATUS "Adding inl directory: ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/inl")
				endif()
				target_include_directories(UltReality_Managers PUBLIC 
					$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${dir}/inl> 
 					$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/UltReality_Managers/${dir}> # This is used when the library is installed
				)
			endif()
		endforeach()

		# Link libraries to the target
		target_link_libraries(UltReality_Managers RendererInterface)

		set_target_properties(UltReality_Managers PROPERTIES 
			VERSION ${PROJECT_VERSION} 
			SOVERSION ${PROJECT_VERSION_MAJOR}
		)

# End Target Creation *****************************************************************************
#**************************************************************************************************

# Installation and Packing Configuration **********************************************************
#**************************************************************************************************

		# Install the targets
		install(
			TARGETS UltReality_Managers RendererInterface
			EXPORT UltReality_Managers_Targets 
			ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} # Static libraries/import libraries (.lib files for .dll linking) 
			LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} # Shared libraries (.so) 
			RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # .exe or .dll 
			PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # Headers/include directories marked as PUBLIC 
			PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # Headers/include directories marked as PRIVATE
		)

		# Create the targets CMake file which contains the above definitions
		install(
			EXPORT UltReality_Managers_Targets 
			FILE UltReality_Managers_Targets.cmake 
			NAMESPACE UltReality:: 
			DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/UltReality_Managers
		)

		# Install the actual includes
		foreach(dir ${Managers_DIRS})
			if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${dir}/include")
				install(
					DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${dir}/include/"
					DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/UltReality_Managers/${dir}"
				)
			endif()

			if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${dir}/inl")
				install(
					DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${dir}/inl/"
					DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/UltReality_Managers/${dir}"
				)
			endif()
		endforeach()

		# Generate and install the package version config files
		include(CMakePackageConfigHelpers)
		write_basic_package_version_file(
			"UltReality_Managers_ConfigVersion.cmake" 
			VERSION ${PROJECT_VERSION} 
			COMPATIBILITY SameMajorVersion
		)
		configure_package_config_file(
			"${CMAKE_CURRENT_SOURCE_DIR}/cmake_config/UltReality_Managers_Config.cmake.in" 
			"${CMAKE_CURRENT_BINARY_DIR}/UltReality_Managers_Config.cmake" 
			INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/UltReality_Managers
		)

		# Install the CMake config files
		install(
			FILES "${CMAKE_CURRENT_BINARY_DIR}/UltReality_Managers_ConfigVersion.cmake" 
			"${CMAKE_CURRENT_BINARY_DIR}/UltReality_Managers_Config.cmake" 
			DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/UltReality_Managers
		)

		# Define Package install paths
		set(INCLUDEDIR_FOR_PKG_CONFIG "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
		set(LIBDIR_PKG_CONFIG "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")

		# Create and install the package config file
		configure_file(
			"${CMAKE_CURRENT_SOURCE_DIR}/cmake_config/UltReality_Managers.pc.in" 
			"${CMAKE_CURRENT_BINARY_DIR}/UltReality_Managers.pc" @ONLY
		)

		# Install the package config file
		install(
			FILES "${CMAKE_CURRENT_BINARY_DIR}/UltReality_Managers.pc" 
			DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
		)
	endif()
endif()

# A version that is often used to denote a specific build of the software, including revisions, builds, or other metadata
set(PACKAGE_VERSION_BUILD "${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}")

set(PACKAGE_VERSION "${PROJECT_VERSION}-${PACKAGE_VERSION_BUILD}")

set(CPACK_PACKAGE_DIRECTORY "${CMAKE_SOURCE_DIR}/out/package")

set(CPACK_PACKAGE_NAME "UltReality_Managers")
set(CPACK_PACKAGE_VERSION "${PACKAGE_VERSION}")

set(CPACK_PACKAGE_VENDOR "Andrew Todd")
set(CPACK_PACKAGE_CONTACT "andrewdanieltodd@gmail.com")
include(CPack)

if(ULTREALITY_MANAGERS_VERBOSE)
	message(STATUS "PACKAGE_VERSION is: ${PACKAGE_VERSION}")
	message(STATUS "PACKAGE_FILE_NAME is: ${CPACK_PACKAGE_FILE_NAME}")
endif()

# End Installation and Packing Configuration ******************************************************
#**************************************************************************************************

# Create Unit Test Groups *************************************************************************
#**************************************************************************************************
if (ULTREALITY_CORE_BUILD_TESTS)
	if(ULTREALITY_MANAGERS_DEBUG)
		message(STATUS "Building test suit for Utilities UltReality_Managers")
	endif()

	set(ULTREALITY_MANAGERS_TEST_DIRS "")

	foreach(dir ${Managers_DIRS})
		if(IS_DIRECTORY "${dir}/tests")
			list(APPEND ULTREALITY_MANAGERS_TEST_DIRS "${dir}/tests")
		endif()
		if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${dir}/tests")
				if(ULTREALITY_MANAGERS_DEBUG)	
					message(STATUS "Adding test directory: ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/tests")
				endif()
				list(APPEND ULTREALITY_MANAGERS_TEST_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/${dir}/tests")
			endif()
	endforeach()

	# Do not install GTest when packaging Utilities targets
	set(INSTALL_GTEST OFF)
	
	# Add all the tests directories
	foreach(tests_dir ${ULTREALITY_MANAGERS_TEST_DIRS})
		if(ULTREALITY_MANAGERS_DEBUG)
			message(STATUS "Adding Sub-Directory: ${tests_dir}")
		endif()
		add_subdirectory("${tests_dir}")
	endforeach()
endif()
# End Create Unit Test Groups *********************************************************************
#**************************************************************************************************