#include header and source files for builing a shared library
include_directories(
#${CMAKE_SOURCE_DIR}/source
${CMAKE_SOURCE_DIR}/source/EUAna
${CMAKE_SOURCE_DIR}/source/EUTree
${CMAKE_SOURCE_DIR}/source/EUData
)

ROOT_GENERATE_DICTIONARY(EUAnaDict
${CMAKE_SOURCE_DIR}/source/EUAna/EUAna.h
${CMAKE_SOURCE_DIR}/source/EUAna/EUAnaBeta.h
${CMAKE_SOURCE_DIR}/source/EUAna/EUAnaIso.h
${CMAKE_SOURCE_DIR}/source/EUAna/EUAnaDecay.h
${CMAKE_SOURCE_DIR}/source/EUAna/EUAnaPID.h
${CMAKE_SOURCE_DIR}/source/EUAna/EUAnaMat.h
)

ROOT_GENERATE_DICTIONARY(EUTreeDict
${CMAKE_SOURCE_DIR}/source/EUTree/EUTree.h
${CMAKE_SOURCE_DIR}/source/EUTree/EUTreeBeta.h
${CMAKE_SOURCE_DIR}/source/EUTree/EUTreeDecay.h
${CMAKE_SOURCE_DIR}/source/EUTree/EUTreeIso.h
)


ROOT_GENERATE_DICTIONARY(EUDataDict
${CMAKE_SOURCE_DIR}/source/EUData/EUData.h
${CMAKE_SOURCE_DIR}/source/EUData/EUDataBeam.h
${CMAKE_SOURCE_DIR}/source/EUData/EUDataSi.h
${CMAKE_SOURCE_DIR}/source/EUData/EUDataGe.h
)

#generate a shared library including dictionaries
add_library(EUROOT SHARED
${CMAKE_SOURCE_DIR}/source/EUAna/EUAna.cc
${CMAKE_SOURCE_DIR}/source/EUAna/EUAnaBeta.cc
${CMAKE_SOURCE_DIR}/source/EUAna/EUAnaIso.cc
${CMAKE_SOURCE_DIR}/source/EUAna/EUAnaDecay.cc
${CMAKE_SOURCE_DIR}/source/EUAna/EUAnaPID.cc
${CMAKE_SOURCE_DIR}/source/EUAna/EUAnaMat.cc
EUAnaDict.cxx

${CMAKE_SOURCE_DIR}/source/EUTree/EUTree.cc
${CMAKE_SOURCE_DIR}/source/EUTree/EUTreeBeta.cc
${CMAKE_SOURCE_DIR}/source/EUTree/EUTreeDecay.cc
${CMAKE_SOURCE_DIR}/source/EUTree/EUTreeIso.cc
EUTreeDict.cxx

${CMAKE_SOURCE_DIR}/source/EUData/EUData.cc
${CMAKE_SOURCE_DIR}/source/EUData/EUDataBeam.cc
${CMAKE_SOURCE_DIR}/source/EUData/EUDataSi.cc
${CMAKE_SOURCE_DIR}/source/EUData/EUDataGe.cc
EUDataDict.cxx
)

target_link_libraries(EUROOT ${ROOT_LIBRARIES})
