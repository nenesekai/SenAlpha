#include <iostream>

#include <xlnt/xlnt.hpp>
#include <nlohmann/json.hpp>

constexpr auto SETW_VALUE = 40;

#include "schedule.hpp"
#include "config.hpp"

// constants for debugging convenience
constexpr auto DEBUG_XLSX_PATH   = "C:\\Users\\Asiimoviet\\OneDrive\\Desktop\\wk11.xlsx";
constexpr auto DEBUG_CONFIG_PATH = "C:\\Users\\Asiimoviet\\Source\\Repos\\Sen\\SenAlpha\\config.json";

int main()
{
	asiimoviet::Config   config(DEBUG_CONFIG_PATH);
	asiimoviet::Schedule schedule(DEBUG_XLSX_PATH, config.getDays());

	schedule.extractClasses(config.getClasses());
	schedule.printAllClasses();

	return 0;
}