#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <iostream>
#include <iomanip>
#include <fstream>

#include <nlohmann/json.hpp>

#include "day.hpp"

namespace asiimoviet
{
	class Config
	{

	private:

		nlohmann::json            cfg_json;

		std::string               label;
		std::string               time_format;
		std::string               classroom_connector;
		std::string               day_one_date;

		std::vector<std::string>  classes;
		std::vector<Day*>*        days; // this copy of days is one without classes stored

	public:

		bool has_label()               { return !cfg_json["label"]              .is_null(); }
		bool has_classes()             { return !cfg_json["classes"]            .is_null(); }
		bool has_days()                { return !cfg_json["days"]               .is_null(); }
		bool has_classroom_connector() { return !cfg_json["classroom_connector"].is_null(); }
		bool has_day_one_date()        { return !day_one_date.length() == 0; }

		Config(std::string path_to_file)
			: days(new std::vector<Day*>)
		{
			load(path_to_file);
			init();
		}

		Config(std::string path_to_file, std::string day_one_date)
			: day_one_date(day_one_date)
			, days(new std::vector<Day*>)
		{
			load(path_to_file);
			init();
		}

		/// <summary>
		/// Convert time string to time
		/// </summary>
		/// <param name="str">Time in string</param>
		/// <returns>Time in duration</returns>
		std::chrono::duration<int> get_time(std::string str)
		{
			return std::chrono::hours(std::stoi(str.substr(0, str.find(":"))))
				+ std::chrono::minutes(std::stoi(str.substr(str.find(":") + 1)));
		}

		/// <summary>
		/// Get Classes from user configuration files
		/// </summary>
		/// <returns>Classes from user configuration file</returns>
		/// TODO: Make sure there is something in it
		std::vector<std::string>* get_classes()
		{
			return &classes;
		}

		/// <summary>
		/// Get the pointer to days
		/// </summary>
		/// <returns>Pointer to days</returns>
		std::vector<Day*>* get_days()
		{
			return days;
		}

		/// <summary>
		/// Return the classroom connector
		/// </summary>
		/// <returns>classroom_connector</returns>
		std::string get_classroom_connector()
		{
			return classroom_connector;
		}

		/// <summary>
		/// Return the day one date
		/// </summary>
		/// <returns>day one date</returns>
		date::local_days get_day_one_date()
		{
			std::stringstream str_stream(day_one_date);
			
			date::local_days ld;
			str_stream >> date::parse("%Y-%m-%d", ld);

			return ld;
		}

		/// <summary>
		/// Load the configuration file to the json
		/// </summary>
		/// <param name="path_to_file">Path to config</param>
		void load(std::string path_to_file)
		{
			std::clog << std::left << std::setw(SETW_VALUE) << "Trying to load config file ...";
			try
			{
				std::fstream* cfg_file = new std::fstream();

				cfg_file -> open(path_to_file);
			   *cfg_file >> cfg_json;
				cfg_file -> close();

				delete cfg_file;
			}
			catch (std::exception exp)
			{
				std::clog << "Failed"           << std::endl  << std::endl;
				std::cerr << "Error Occurred: " << exp.what() << std::endl;
				std::cerr << "Exiting..."                     << std::endl;

				exit(1);
			}
			std::clog << "Success" << std::endl;
		}

		/// <summary>
		/// Read the configuration
		/// </summary>
		void init()
		{
			std::clog << std::left << std::setw(SETW_VALUE) << "Trying to read from the config...";
			try
			{
				if (has_label())   
					label   = cfg_json["label"];

				if (has_classes()) 
					classes = cfg_json["classes"].get<std::vector<std::string>>();
				else throw(std::exception("missing classes from config file"));

				if (has_classroom_connector())
					classroom_connector = cfg_json["classroom_connector"];
				else throw(std::exception("missing classroom connector from config file"));
				
				if (has_days())
				{
					for (auto day : cfg_json["days"])
					{
						this->days->push_back(new Day(
							  day["day_offset"] .get<int>()
							, day["column"]     .get<std::string>()
							, day["time_column"].get<std::string>()
						));
					}
				}
				else throw(std::exception("missing days from config"));
			}
			catch (std::exception exp)
			{
				std::clog << "Failed"           << std::endl  << std::endl;
				std::cerr << "Error Occurred: " << exp.what() << std::endl;
				std::cerr << "Exiting..."                     << std::endl;

				exit(1);
			}
			std::clog << "Success" << std::endl;
		}

		/// <summary>
		/// Print all classes read from the configuration
		/// </summary>
		/// WARNING: DO NOT USE BEFORE init()
		void print_classes()
		{
			std::cout << std::endl << "Read these classes: " << std::endl;

			for (std::vector<std::string>::iterator iter = classes.begin(); iter < classes.end(); iter++)
				std::cout << *iter << std::endl;

			std::cout << std::endl;
		}

	};
}

#endif // defined (CONFIG_HPP_)