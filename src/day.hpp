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

		std::vector<Class*>* classes;

	public:

		int get_day_offset()               { return day_offset; }

		std::string get_column()           { return column; }
		std::string get_time_column()      { return time_column; }

		std::vector<Class*>* get_classes() { return classes; }

		Day(int day_offset
			, std::string column
			, std::string time_column)
			: day_offset(day_offset)
			, column(column)
			, time_column(time_column)
			, classes(new std::vector<Class*>())
		{}

	};
}

#endif // defined (DAY_HPP_)