#ifndef CLASS_HPP_
#define CLASS_HPP_

#include <iostream>

namespace asiimoviet
{
	class Class
	{
		
	private:

		std::string label;
		
	public:

		Class() {}
		Class(std::string label) : label(label) {}

		std::string getLabel() { return label; }

		void print()
		{
			std::cout << "Label:\t" << label << std::endl;
		}
		
	};
}

#endif // defined (CLASS_HPP_)