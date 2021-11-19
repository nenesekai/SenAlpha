add_executable(SenAlpha client.cpp)

target_link_libraries(SenAlpha 
	PRIVATE 
		date::date 
		nlohmann_json 
		nlohmann_json::nlohmann_json 
		xlnt::xlnt)