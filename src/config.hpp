#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <iostream>
#include <iomanip>
#include <fstream>

#include <nlohmann/json.hpp>

namespace asiimoviet
{
	class Config
	{

	private:

		nlohmann::json  cfg_json;

		std::string     label;
		std::string     day1_date;
		std::string     period_indicate_column;

	public:

		bool hasLabel()                { return !cfg_json["label"].is_null(); }
		bool hasDayOneDate()           { return !cfg_json["day1_date"].is_null(); }
		bool hasPeriodIndicateColumn() { return !cfg_json["period_indicate_column"].is_null(); }

		Config(std::string path_to_file)
		{
			load(path_to_file);
			init();
		}

		void load(std::string path_to_file)
		{
			std::clog << std::left << std::setw(SETW_VALUE) << "Trying to load config file ...";
			try
			{
				std::fstream* cfg_file = new std::fstream();

				cfg_file->open(path_to_file);
			   *cfg_file >> cfg_json;
				cfg_file->close();

				delete cfg_file;
			}
			catch (std::exception exp)
			{
				std::cerr << "Failed"                         << std::endl;
				std::cerr << "Error Occurred: " << exp.what() << std::endl;
				std::cerr << "Exiting"                        << std::endl;

				exit(1);
			}
			std::clog << "Success" << std::endl;
		}

		void init()
		{
			if (hasLabel())      this->label = cfg_json["label"];
			if (hasDayOneDate()) this->day1_date = cfg_json["day1_date"];
		}

	};
}

#endif // defined (CONFIG_HPP_)