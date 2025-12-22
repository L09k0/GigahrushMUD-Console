set(SOURCES 
	Server.cpp
	Session.cpp
	main.cpp
)

set(HEADERS 
	Server.h
	Session.h
)

add_executable (GigahrushServer ${SOURCES} ${HEADERS})
target_link_libraries(GigahrushServer PRIVATE asio)
target_link_libraries(GigahrushServer PRIVATE nlohmann_json)