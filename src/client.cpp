#define SETW_VALUE 40

#include <iostream>

#include <xlnt/xlnt.hpp>
#include <nlohmann/json.hpp>

#include "schedule.hpp"
#include "config.hpp"

// constants for debugging convenience
constexpr auto DEBUG_XLSX_PATH	 = "C:\\Users\\Asiimoviet\\OneDrive\\Desktop\\wk11.xlsx";
constexpr auto DEBUG_CONFIG_PATH = "C:\\Users\\Asiimoviet\\Source\\Repos\\Sen\\SenAlpha\\config.json";

int main()
{
	asiimoviet::Schedule schedule(DEBUG_XLSX_PATH);
	asiimoviet::Config	 config(DEBUG_CONFIG_PATH);

	return 0;
}