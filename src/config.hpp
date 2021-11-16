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

		std::vector<std::string>  classes;
		std::vector<Day*>*        days; // this copy of days is one without classes stored

	public:

		bool hasLabel()   { return !cfg_json["label"]  .is_null(); }
		bool hasClasses() { return !cfg_json["classes"].is_null(); }
		bool hasDays()    { return !cfg_json["days"]   .is_null(); }

		Config(std::string path_to_file)
		{
			days = new std::vector<Day*>;

			load(path_to_file);
			init();
		}

		/// <summary>
		/// Get Classes from user configuration files
		/// </summary>
		/// <returns>Classes from user configuration file</returns>
		/// TODO: Make sure there is something in it
		std::vector<std::string> getClasses()
		{
			return classes;
		}

		/// <summary>
		/// Get the pointer to days
		/// </summary>
		/// <returns>Pointer to days</returns>
		std::vector<Day*>* getDays()
		{
			return days;
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
				if (hasLabel())   label   = cfg_json["label"];

				if (hasClasses()) classes = cfg_json["classes"].get<std::vector<std::string>>();
				else throw(std::exception("missing classes from config file"));
				
				if (hasDays())
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
		void printClasses()
		{
			std::cout << std::endl << "Read these classes: " << std::endl;

			for (std::vector<std::string>::iterator iter = classes.begin(); iter < classes.end(); iter++)
				std::cout << *iter << std::endl;

			std::cout << std::endl;
		}

	};
}

#endif // defined (CONFIG_HPP_)