#ifndef CLASS_HPP_
#define CLASS_HPP_

#include <iostream>
#include <fstream>

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

		void print()
		{
			std::cout << std::left << std::setw(15) << "Label"     << label     << std::endl;
			std::cout << std::left << std::setw(15) << "Classroom" << classroom << std::endl;
			std::cout << std::left << std::setw(15) << "Dtstart"   << dtstart   << std::endl;
			std::cout << std::left << std::setw(15) << "Dtend"     << dtend     << std::endl;
		}

		void ical(std::ofstream& of_stream)
		{
			of_stream << "BEGIN:VEVENT" << std::endl;
			of_stream << "SUMMARY:"     << label << std::endl;
			of_stream << "DTSTART:"     << date::format("%Y%m%dT%H%M%SZ", dtstart - std::chrono::hours(8)) << std::endl;
			of_stream << "DTEND:"       << date::format("%Y%m%dT%H%M%SZ", dtend   - std::chrono::hours(8)) << std::endl;
			of_stream << "LOCATION:"    << classroom << std::endl;
			of_stream << "END:VEVENT"   << std::endl;
		}
		
	};
}

#endif // defined (CLASS_HPP_)