#include header and source files
include_directories(
${CMAKE_SOURCE_DIR}/source
${CMAKE_SOURCE_DIR}/source/EUTree
${CMAKE_SOURCE_DIR}/source/EUAna
${CMAKE_SOURCE_DIR}/source/EUData
)

#generate an executable file
add_executable (si_ge_merge si_ge_merge.cpp)
EXECUTE_PROCESS(COMMAND root-config --libs OUTPUT_VARIABLE ROOT_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CMAKE_EXE_LINKER_FLAGS ${ROOT_LD_FLAGS})
target_link_libraries (si_ge_merge LINK_PUBLIC EUROOT)

add_executable (beta_beam_merge beta_beam_merge.cpp)
EXECUTE_PROCESS(COMMAND root-config --libs OUTPUT_VARIABLE ROOT_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CMAKE_EXE_LINKER_FLAGS ${ROOT_LD_FLAGS})
target_link_libraries (beta_beam_merge LINK_PUBLIC EUROOT)

add_executable (betadecay betadecay.cpp)
EXECUTE_PROCESS(COMMAND root-config --libs OUTPUT_VARIABLE ROOT_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CMAKE_EXE_LINKER_FLAGS ${ROOT_LD_FLAGS})
target_link_libraries (betadecay LINK_PUBLIC EUROOT)


