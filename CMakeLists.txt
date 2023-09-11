cmake_minimum_required(VERSION 3.22.1)

project(sfml-app)

include(FetchContent)

# Versions
set(SFML_VERSION 2.6.0)
set(IMGUI_VERSION 1.87)
# set(IMGUI_SFML_VERSION 2.3)

# Build everything statically on Windows
# On Linux all deps must be installed manually
set(BUILD_SHARED_LIBS OFF)
if (WIN32)
  set(CMAKE_EXE_LINKER_FLAGS "-static")
endif (WIN32)

# Downloading deps
# SFML
FetchContent_Declare(
  SFML
  URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/SFML
)

# ImGui
FetchContent_Declare(
  imgui
  URL "https://github.com/ocornut/imgui/archive/v${IMGUI_VERSION}.zip"
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/ImGui
)

# ImGui-SFML
FetchContent_Declare(
  imgui-sfml
  GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
  GIT_TAG        2.6.x
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/ImGui-SFML
)

# Midifile
FetchContent_Declare(
  midifile
  GIT_REPOSITORY https://github.com/craigsapp/midifile.git
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/Midifile
)

# Building
# SFML
FetchContent_MakeAvailable(sfml)

# Dear ImGui
FetchContent_MakeAvailable(imgui)

# ImGui-SFML
set(IMGUI_DIR ${imgui_SOURCE_DIR})
option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
option(IMGUI_SFML_IMGUI_DEMO "Build imgui_demo.cpp" ON)
FetchContent_MakeAvailable(imgui-sfml)

# Midifile
FetchContent_MakeAvailable(midifile)

add_executable(sfml-app 
  source/main.cpp
  source/game.cpp
  source/menustate.cpp
  source/playstate.cpp
  source/conductor.cpp
)
target_include_directories(
  sfml-app
  PRIVATE
  include
  libraries/Midifile/include
)
target_link_libraries(
  sfml-app
  PRIVATE
  sfml-graphics
  sfml-window
  sfml-system
  sfml-audio
  ImGui-SFML::ImGui-SFML
  midifile
)