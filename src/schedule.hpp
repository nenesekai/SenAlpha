#ifndef SCHEDULE_HPP_
#define SCHEDULE_HPP_

#include <iostream>
#include <iomanip>
#include <vector>
#include <xlnt/xlnt.hpp>

#include "class.hpp"
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

		Schedule() {}

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
		void extractClasses(std::vector<std::string> classes)
		{
			for (auto column : worksheet.columns())
			{
				Day* day = nullptr;

				// see if this column matches the one in days in config
				for (auto day_iter = days->begin()
					; day_iter < days->end()
					; day_iter++)
				{
					if ((*day_iter)->getColumn() == column.front().column().column_string())
					{
						day = *day_iter;
					}
				}

				if (day)
				{
					for (auto cell : column)
					{
						for (auto class_iter = classes.begin()
							; class_iter < classes.end()
							; class_iter++)
						{
							if (cell.to_string().find(*class_iter) != -1)
							{
								day->getSelectedClasses()->push_back(new Class(
									cell.to_string()
								));
							}
						}
					}
				}
			}
		}

		/// <summary>
		/// Print all classes in the class
		/// </summary>
		void printAllClasses()
		{
			std::cout << std::endl;
			
			for (auto day_iter = days->begin()
				; day_iter < days->end()
				; day_iter++)
			{
				std::cout << "Day " << (*day_iter)->getDayOffset() + 1 << std::endl << std::endl;

				for (auto class_iter = (*day_iter)->getSelectedClasses()->begin()
					; class_iter < (*day_iter)->getSelectedClasses()->end()
					; class_iter++)
				{
					std::cout << "Label:\t" << (*class_iter)->getLabel() << std::endl;
					std::cout << std::endl;
				}
				
				std::cout << std::endl;
			}

			std::cout << std::endl;
		}
	};
}

#endif // defined (SCHEDULE_HPP_)
