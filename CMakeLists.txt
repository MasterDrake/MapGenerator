cmake_minimum_required(VERSION 3.21.2)

set(VCPKG_LIBRARY_LINKAGE static)


if (WIN32)
	#set(VCPKG_TARGET_TRIPLET x64-windows)
	include("$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
elseif (UNIX)
	set(VCPKG_TARGET_TRIPLET x64-linux)
 	include("/home/ilies/GameDev/Libraries/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

project(MapGeneratorProject VERSION 0.1.0 LANGUAGES CXX)

include(CTest)
enable_testing()

add_library(DiskSampling include/DiskSampling/PoissonDiskSampling.h src/DiskSampling/PoissonDiskSampling.cpp)
add_library(MarkovChain include/MarkovChain/MarkovChain.h src/MarkovChain/MarkovChain.cpp)
add_library(MapGenerator include/MapGenerator/Structures.h include/MapGenerator/Quadtree.h include/MapGenerator/Map.h include/MapGenerator/dDelaunay.h include/MapGenerator/Math/LineEquation.h include/MapGenerator/Math/Vec2.h
                         src/MapGenerator/Structures.cpp src/MapGenerator/Map.cpp src/MapGenerator/dDelaunay.cpp src/MapGenerator/Math/LineEquation.cc src/MapGenerator/Math/Vec2.cpp)


add_executable(MapGeneratorEx MapGeneratorSource.cpp)
add_executable(MarkovNamesEx MarkovChainSource.cpp)

target_compile_features(MarkovNamesEx PUBLIC cxx_std_11)
target_compile_features(MapGeneratorEx PUBLIC cxx_std_11)

target_include_directories(DiskSampling PUBLIC include)
target_include_directories(MarkovChain PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_include_directories(MapGenerator PUBLIC include)


target_link_libraries(MapGeneratorEx PUBLIC MapGenerator DiskSampling MarkovChain)
target_link_libraries(MarkovNamesEx PUBLIC MarkovChain)

find_package(unofficial-noise CONFIG REQUIRED)
find_package(unofficial-noiseutils CONFIG REQUIRED)

if(WIN32)
	target_link_libraries(MapGenerator PUBLIC unofficial::noise::noise)
	target_link_libraries(MapGenerator PUBLIC unofficial::noiseutils::noiseutils)
elseif(UNIX)
	target_link_libraries(MapGenerator PUBLIC unofficial::noise::noise-static)
	target_link_libraries(MapGenerator PUBLIC unofficial::noiseutils::noiseutils-static)
endif()

# Find and link SFML components
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(MapGenerator PUBLIC sfml-system sfml-network sfml-graphics sfml-window)

find_package(ImGui-SFML CONFIG REQUIRED)
target_link_libraries(MapGenerator PRIVATE ImGui-SFML::ImGui-SFML)

# Link SFML main implementation
if(WIN32)
	target_link_libraries(MapGenerator PUBLIC sfml-main)
elseif(UNIX)
endif()


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
