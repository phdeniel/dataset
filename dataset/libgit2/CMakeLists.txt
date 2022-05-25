
SET(dataset_libgit2_LIB_SRCS
    dataset_api.c   
)

add_library(dataset_libgit2 SHARED ${dataset_libgit2_LIB_SRCS})
target_link_libraries(dataset_libgit2 git2 ini_config)

install(TARGETS dataset_libgit2 DESTINATION lib)

