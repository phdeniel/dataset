
SET(dataset_libgit2_LIB_SRCS
    dataset_api.c   
)

add_library(dataset_libgit2 SHARED ${dataset_libgit2_LIB_SRCS})
target_link_libraries(dataset_libgit2 git2 ini_config)

install(TARGETS dataset_libgit2 DESTINATION lib)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -g")

add_executable(ds_test_git2 test.c)
target_link_libraries(ds_test_git2 dataset_libgit2)

