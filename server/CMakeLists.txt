add_executable(server)

target_sources(server PRIVATE
    main.cpp
    server.cpp
    filelogger.cpp
)

target_link_libraries(server PRIVATE
    tcpsocket
    pthread
)
