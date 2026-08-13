### DO NOT DELETE THIS COMMENT: INSERT_ARCHETYPES_HERE ###

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

USE_CYCLUS("tricycle" "fusion_power_plant")
USE_CYCLUS("tricycle" "decay_storage")
INSTALL_CYCLUS_MODULE("tricycle" "")

TARGET_SOURCES(tricycle PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/strt_up_policy.cc"
)

# install header files
FILE(GLOB h_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
