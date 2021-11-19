#include <iostream>
#include <fstream>

#include <xlnt/xlnt.hpp>
#include <nlohmann/json.hpp>
#include <date/tz.h>

constexpr auto SETW_VALUE = 60;

#include "schedule.hpp"
#include "config.hpp"

#include <windows.h>
#include <Lmcons.h>

int main(int argc, char** argv)
{

	TCHAR username[UNLEN + 1];
	DWORD username_size = UNLEN + 1;

	GetUserName((TCHAR*)username, &username_size);
	std::string username_str(username);

	auto DEFAULT_OUTPUT_PATH = "C:\\Users\\" + username_str + "\\schedule.ics";
	auto DEFAULT_CONFIG_PATH = ".\\config.json";

	std::string output_path = DEFAULT_OUTPUT_PATH;
	std::string config_path = DEFAULT_CONFIG_PATH;
	std::string xlsx_path;
	std::string day_one;

	switch (argc)
	{
	case 1:
		std::cout << "Usage: " << std::endl;
		std::cout << "senalpha.exe excel_file.xlsx day_one_date [-c config_file] [-o output_path]" << std::endl;
		exit(0);

	case 2:
		std::cerr << "Error: invalid parameters" << std::endl;
		exit(1);

	default:
		xlsx_path = argv[1];
		day_one = argv[2];

		for (int i = 3; i < argc; i++)
		{
			if (argv[i][0] == '-')
			{
				if (argv[i] == "-c") config_path = argv[i + 1];
				if (argv[i] == "-o") output_path = argv[i + 1];
				i += 1;
			}
		}
	}

	asiimoviet::Config   config(config_path, day_one);
	asiimoviet::Schedule schedule(xlsx_path, config.get_days());

	schedule.process(config);

	std::clog << std::left << std::setw(SETW_VALUE) << "Creating iCalendar File...";
	try
	{
		std::ofstream of_stream(output_path);

		schedule.ical(of_stream);

		of_stream.close();
	}
	catch (std::exception exp)
	{
		std::clog << "Failed" << std::endl << std::endl;
		std::cerr << "Error Occurred While Exporting File: " << exp.what() << std::endl;
		std::cerr << "Exiting..." << std::endl;

		exit(1);
	}
	std::clog << "Success" << std::endl;

	return 0;

}