#ifndef CLASS_HPP_
#define CLASS_HPP_

#include <iostream>

#include "date/tz.h"

namespace asiimoviet
{
	class Class
	{
		
	private:

		std::string label;
		std::string classroom;
		
		std::chrono::time_point<date::local_t, std::chrono::seconds> dtstart;
		std::chrono::time_point<date::local_t, std::chrono::seconds> dtend;
		
	public:

		Class() {}

		Class(std::string label) : label(label) {}

		Class(std::string label, std::string classroom)
			: label(label)
			, classroom(classroom)
		{}

		Class(std::string label
			, std::string classroom
			, std::chrono::time_point<date::local_t, std::chrono::seconds> dtstart
			, std::chrono::time_point<date::local_t, std::chrono::seconds> dtend)
			: label(label)
			, classroom(classroom)
			, dtstart(dtstart)
			, dtend(dtend)
		{}

		std::string getLabel() { return label; }

		void print()
		{
			std::cout << std::left << std::setw(15) << "Label"     << label     << std::endl;
			std::cout << std::left << std::setw(15) << "Classroom" << classroom << std::endl;
			std::cout << std::left << std::setw(15) << "Dtstart"   << dtstart   << std::endl;
			std::cout << std::left << std::setw(15) << "Dtend"     << dtend     << std::endl;
		}
		
	};
}

#endif // defined (CLASS_HPP_)