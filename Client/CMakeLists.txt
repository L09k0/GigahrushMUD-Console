set(SOURCES
	Client.cpp
	main.cpp
)

set(HEADERS
	Client.h
	Parser.h
)

add_executable(GigahrushClient-Console ${SOURCES} ${HEADERS})

set(aud_dir "${CMAKE_SOURCE_DIR}/thirdparty/audiere-1.9.4-win32/")
target_link_libraries(GigahrushClient-Console PRIVATE "${aud_dir}/lib/audiere.lib")
target_include_directories(GigahrushClient-Console PRIVATE "${aud_dir}/include")
target_link_libraries(GigahrushClient-Console PRIVATE asio)
target_link_libraries(GigahrushClient-Console PRIVATE nlohmann_json)
target_link_libraries(GigahrushClient-Console PRIVATE ${aud_dir}/lib/audiere.lib)
