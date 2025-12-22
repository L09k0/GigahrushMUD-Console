set(SOURCES
	Client.cpp
	main.cpp
)

set(HEADERS
	Client.h
)

add_executable(GigahrushClient ${SOURCES} ${HEADERS})
target_link_libraries(GigahrushClient PRIVATE asio)
target_link_libraries(GigahrushClient PRIVATE nlohmann_json)