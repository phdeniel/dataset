cmake_minimum_required(VERSION 2.6.4)
cmake_policy(SET CMP0017 NEW)

PROJECT(dataset_api C)
set(LIBDATASET_MAJOR_VERSION 0)
set(LIBDATASET_MINOR_VERSION 0)
set(LIBDATASET_PATCH_LEVEL 1)
set(LIBDATASET_EXTRA_VERSION "")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${CMAKE_SOURCE_DIR}/include -fPIC -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(LIBDATASET_BASE_VERSION ${LIBDATASET_MAJOR_VERSION}.${LIBDATASET_MINOR_VERSION}.${LIBDATASET_PATCH_LEVEL})

message( STATUS "cmake version ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" )
message( STATUS "libdataset version ${LIBDATASET_BASE_VERSION}")

option(EXT_BUILD "Get include deps in upper levels" "")

if(EXT_BUILD)
  message(STATUS "EXT_BUILD=${EXT_BUILD}")
  link_directories(${EXT_BUILD}/usr/local/lib)
  include_directories(AFTER ${EXT_BUILD}/usr/local/include)
endif(EXT_BUILD)

# Final tuning

include(CheckIncludeFiles)
include(CheckLibraryExists)

## Check ini_config
check_include_files("ini_config.h" HAVE_INI_CONFIG_H)
find_library(HAVE_INI_CONFIG ini_config)
check_library_exists(
	ini_config
	config_from_file
	""
	HAVE_INI_CONFIG
	)

if((NOT HAVE_INI_CONFIG) OR (NOT HAVE_INI_CONFIG_H))
      message(FATAL_ERROR "Cannot find ini_config")
endif((NOT HAVE_INI_CONFIG) OR (NOT HAVE_INI_CONFIG_H))


## Check for libgit2
check_include_files("git2.h" HAVE_GIT2_H)
find_library(HAVE_GIT2 git2)
check_library_exists(
        git2
        git_commit_lookup
        ""
	HAVE_GIT2
        )

if((NOT HAVE_GIT2) OR (NOT HAVE_GIT2_H))
      message(FATAL_ERROR "Cannot find git2")
endif((NOT HAVE_GIT2) OR (NOT HAVE_GIT2_H))


add_subdirectory(dataset)

# CPack / rpmbuild specific stuff
set(CPACK_PACKAGE_FILE_NAME "libdataset-Source" )
set(CPACK_PACKAGE_VENDOR "DATASET")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "DATASET - Data sets management API for the IO-SEA project")
SET(CPACK_PACKAGE_VERSION_MAJOR ${LIBDATASET_MAJOR_VERSION})
SET(CPACK_PACKAGE_VERSION_MINOR ${LIBDATASET_MINOR_VERSION})
SET(CPACK_PACKAGE_VERSION_PATCH ${LIBDATASET_PATCH_LEVEL})

# Tell CPack the kind of packages to be generated
set(CPACK_GENERATOR "TGZ")
set(CPACK_SOURCE_GENERATOR "TGZ")

set(CPACK_SOURCE_IGNORE_FILES
  "/.git/;/.gitignore/;/build/;/.bzr/;~$;${CPACK_SOURCE_IGNORE_FILES}")

include(CPack)

set(PKG_NAME "${CPACK_PACKAGE_NAME}.tar.gz")
if(NOT WITHIN_IOSEA_NAMESPACE_REPO)
   add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)
endif(NOT WITHIN_IOSEA_NAMESPACE_REPO)


  # Now create a useable specfile
  configure_file(
    "${PROJECT_SOURCE_DIR}/libdataset.spec-in.cmake"
    "${PROJECT_SOURCE_DIR}/libdataset.spec"
  )

  # Create the .pc file
  configure_file(
    "${PROJECT_SOURCE_DIR}/libdataset.pc-in.cmake"
    "${PROJECT_SOURCE_DIR}/libdataset.pc"
  )

set(RPMDEST "--define '_srcrpmdir ${CMAKE_CURRENT_BINARY_DIR}'")

if(NOT WITHIN_IOSEA_NAMESPACE_REPO)
  add_custom_target( rpms DEPENDS dist)
  add_custom_command(TARGET rpms
                    COMMAND sh -c "rpmbuild ${RPMDEST} -ta ${CPACK_SOURCE_PACKAGE_FILE_NAME}.tar.gz"
                    VERBATIM
                    DEPENDS dist)

  add_custom_target( rpm DEPENDS dist)
  add_custom_command(TARGET rpm
                    COMMAND sh -c "rpmbuild ${RPMDEST} -tb ${CPACK_SOURCE_PACKAGE_FILE_NAME}.tar.gz"
                    VERBATIM
                    DEPENDS dist)

  add_custom_target( srpm DEPENDS dist)
  add_custom_command(TARGET srpm
                    COMMAND sh -c "rpmbuild ${RPMDEST} -ts ${CPACK_SOURCE_PACKAGE_FILE_NAME}.tar.gz"
                    VERBATIM
                    DEPENDS dist)
endif(NOT WITHIN_IOSEA_NAMESPACE_REPO)

# INSTALL
install(FILES ${PROJECT_SOURCE_DIR}/libdataset.pc DESTINATION lib)
install(FILES ${PROJECT_SOURCE_DIR}/include/iosea/dataset.h DESTINATION include/iosea)
