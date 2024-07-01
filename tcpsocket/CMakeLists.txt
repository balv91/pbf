add_library(tcpsocket)

target_sources(tcpsocket PRIVATE
    tcpsocket.cpp
)

target_include_directories(tcpsocket INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)
