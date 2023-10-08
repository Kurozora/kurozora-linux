#pragma once
#include <ctime>
#include <string>
#include <sstream>
#include <algorithm>

namespace kurozora::utils::time
{
		inline std::string parse_time(std::time_t* unix_timestamp)
		{
				std::tm time;
				localtime_r(unix_timestamp, &time);
				std::stringstream ss;
				ss << "Expected " << time.tm_mday << " ";
				switch (time.tm_mon)
				{
				case 0:
						ss << "January ";
						break;
				case 1:
						ss << "February ";
						break;
				case 2:
						ss << "March ";
						break;
				case 3:
						ss << "April ";
						break;
				case 4:
						ss << "May ";
						break;
				case 5:
						ss << "June ";
						break;
				case 6:
						ss << "July ";
						break;
				case 7:
						ss << "August ";
						break;
				case 8:
						ss << "September ";
						break;
				case 9:
						ss << "October ";
						break;
				case 10:
						ss << "November ";
						break;
				case 11:
						ss << "December ";
						break;
				}
				ss << std::to_string(time.tm_year + 1900);
				return ss.str();
		}
}
