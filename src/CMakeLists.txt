add_executable(SenAlpha client.cpp "day.hpp" "schedule.hpp.bak" )

target_link_libraries(SenAlpha 
	PRIVATE 
		date::date 
		date::date-tz 
		nlohmann_json 
		nlohmann_json::nlohmann_json 
		xlnt::xlnt)