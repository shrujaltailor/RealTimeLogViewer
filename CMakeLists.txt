cmake_minimum_required(VERSION 3.10)
project(RealTimeLogViewer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-libgcc")

# Find Qt5 components
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

# Source files
set(SOURCES
    src/main.cpp
    src/LogViewer.cpp
    src/FileWatcher.cpp
    src/FilterDecorator.cpp
    src/LogFacade.cpp
    src/CaptureCommand.cpp
)

# Header files
set(HEADERS
    src/LogViewer.h
    src/FileWatcher.h
    src/FilterDecorator.h
    src/LogFacade.h
    src/CaptureCommand.h
)

# UI files
set(UIS
    src/LogViewer.ui
)

# Generate UI headers
qt5_wrap_ui(UI_HEADERS ${UIS})

# Include build directory for generated headers
include_directories(${CMAKE_BINARY_DIR})

# Enable AUTOMOC to handle moc files automatically
set(CMAKE_AUTOMOC ON)

# Add executable
add_executable(LogViewer ${SOURCES} ${HEADERS} ${UI_HEADERS})

# Link Qt5 libraries
target_link_libraries(LogViewer Qt5::Core Qt5::Widgets)
