#ifndef SCHEDULE_HPP_
#define SCHEDULE_HPP_

#include <iostream>
#include <iomanip>
#include <xlnt/xlnt.hpp>

namespace asiimoviet
{
	class Schedule
	{

	private:

		xlnt::workbook  workbook;
		xlnt::worksheet worksheet;

	public:

		Schedule() {}

		Schedule(std::string path_to_file)
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
			catch (xlnt::exception e)
			{
				std::cerr << "Failed" << std::endl;
				std::cerr << "Error Occurred: " << e.what() << std::endl;
				std::cerr << "Exiting..." << std::endl;

				exit(1);
			}

			std::clog << "Success" << std::endl;
		}

	};
}

#endif // defined (SCHEDULE_HPP_)
