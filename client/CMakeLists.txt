add_executable(client)

target_sources(client PRIVATE
    main.cpp
    client.cpp
)

target_link_libraries(client PRIVATE
    tcpsocket
)
