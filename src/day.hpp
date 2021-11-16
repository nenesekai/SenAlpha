#ifndef DAY_HPP_
#define DAY_HPP_

#include "class.hpp"

namespace asiimoviet
{
	class Day
	{

	private:

		int                  day_offset;

		std::string          column;
		std::string          time_column;

		std::vector<Class*>* selected_classes;

	public:

		int getDayOffset()                        { return day_offset; }

		std::string getColumn()                   { return column; }
		std::string getTimeColumn()               { return time_column; }

		std::vector<Class*>* getSelectedClasses() { return selected_classes; }

		Day(int day_offset
			, std::string column
			, std::string time_column)
			: day_offset(day_offset)
			, column(column)
			, time_column(time_column)
			, selected_classes(new std::vector<Class*>())
		{}

	};
}

#endif // defined (DAY_HPP_)