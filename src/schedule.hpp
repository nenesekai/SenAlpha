#ifndef SCHEDULE_HPP_
#define SCHEDULE_HPP_

#include <iostream>
#include <iomanip>
#include <vector>
#include <xlnt/xlnt.hpp>
#include <date/tz.h>

#include "class.hpp"
#include "config.hpp"
#include "day.hpp"

namespace asiimoviet
{
	class Schedule
	{

	private:

		xlnt::workbook     workbook;
		xlnt::worksheet    worksheet;

		std::vector<Day*>* days;

	public:

		Schedule()
			: days(new std::vector<Day*>())
		{}

		Schedule(std::string path_to_file, std::vector<Day*>* days)
			: days(days)
		{
			load(path_to_file);
		}

		void load(std::string path_to_file)
		{
			std::clog << std::left << std::setw(SETW_VALUE) << "Trying to load xlsx file ...";

			try
			{
				this->workbook.load(path_to_file);
				this->worksheet = this->workbook.active_sheet();
			}
			catch (xlnt::exception exp)
			{
				std::clog << "Failed"           << std::endl  << std::endl;
				std::cerr << "Error Occurred: " << exp.what() << std::endl;
				std::cerr << "Exiting..."                     << std::endl;

				exit(1);
			}

			std::clog << "Success" << std::endl;
		}

		/// <summary>
		/// Go through the sheet using columns in classes as index
		/// Then extract corresponding information
		/// </summary>
		/// <param name="classes">The classes selected by the user</param>
		void process(Config& config)
		{
			std::clog << std::left << std::setw(SETW_VALUE) << "Reading xlsx File for Classes Information ...";

			for (auto column : worksheet.columns())
			{
				Day* day = nullptr;

				// see if this column matches the one in days in config
				for (auto day_iter = days->begin()
					; day_iter < days->end()
					; day_iter++)
				{
					if ((*day_iter)->get_column() == column.front().column().column_string())
					{
						day = *day_iter;
					}
				}

				if (day)
				{
					for (auto cell : column)
					{
						for (auto class_iter = config.getClasses()->begin()
							; class_iter < config.getClasses()->end()
							; class_iter++)
						{
							if (cell.to_string().find(*class_iter) != -1)
							{
								std::string time_str = "";

								// find the time for the corresponding class
								for (int row_i = cell.row()
									; row_i != 0
									; row_i--)
								{
									if (worksheet.cell(day->get_time_column(), row_i).has_value())
									{
										time_str = worksheet.cell(day->get_time_column(), row_i).to_string();
										break;
									}
								}

								// if time is not found, fatal error
								if (time_str.length() == 0) 
								{
									std::cout << "Failed" << std::endl << std::endl;
									std::cerr << "Processing Error: Can\'t find time corresponding to the class"
										<< ", please check your config and the file" << std::endl;
									std::cerr << "Exiting..." << std::endl;

									exit(1);
								}

								// clip the beginning and ending time
								std::string start_str = time_str.substr(0, time_str.find("-"));
								std::string end_str   = time_str.substr(time_str.find("-") + 1);

								auto dtstart = config.getDayOneDate() + date::days(day->get_day_offset()) 
									+ std::chrono::hours(std::stoi(start_str.substr(0, start_str.find(":"))))
									+ std::chrono::minutes(std::stoi(start_str.substr(start_str.find(":") + 1)));
								auto dtend   = config.getDayOneDate() + date::days(day->get_day_offset())
									+ config.get_time(end_str);

								std::string str      = cell.to_string();
								std::string label    = str.substr(0, str.rfind(config.getClassroomConnector()));
								std::string cr       = str.substr(str.rfind(config.getClassroomConnector()) + 1);

								day->get_classes()->push_back(new Class(
									label, cr, dtstart, dtend
								));
							}
						}
					}
				}
			}

			std::clog << "Success" << std::endl;
		}

		/// <summary>
		/// Print all classes in the class
		/// </summary>
		void print_classes()
		{
			std::cout << std::endl;
			
			for (auto day_iter = days->begin()
				; day_iter < days->end()
				; day_iter++)
			{
				std::cout << "Day " << (*day_iter)->get_day_offset() + 1 << std::endl << std::endl;

				for (auto class_iter = (*day_iter)->get_classes()->begin()
					; class_iter < (*day_iter)->get_classes()->end()
					; class_iter++)
				{
					(*class_iter)->print();
					std::cout << std::endl;
				}
				
				std::cout << std::endl;
			}

			std::cout << std::endl;
		}
	};
}

#endif // defined (SCHEDULE_HPP_)
