#include <iostream>

#include <xlnt/xlnt.hpp>
#include <nlohmann/json.hpp>
#include <date/tz.h>

constexpr auto SETW_VALUE = 60;

#include "schedule.hpp"
#include "config.hpp"

// constants for debugging convenience
constexpr auto DEBUG_DAY_ONE     = "2021-11-15";
constexpr auto DEBUG_OUTPUT_PATH = "C:\\Users\\Asiimoviet\\Desktop\\schedule.ical";
constexpr auto DEBUG_XLSX_PATH   = "C:\\Users\\Asiimoviet\\OneDrive\\Desktop\\wk12.xlsx";
constexpr auto DEBUG_CONFIG_PATH = "C:\\Users\\Asiimoviet\\Source\\Repos\\Sen\\SenAlpha\\config.json";

int main()
{
	asiimoviet::Config   config(DEBUG_CONFIG_PATH, DEBUG_DAY_ONE);
	asiimoviet::Schedule schedule(DEBUG_XLSX_PATH, config.getDays());

	config.getDayOneDate();

	schedule.process(config);

	return 0;
}