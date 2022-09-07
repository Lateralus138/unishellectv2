#include "globals.h"
#include <iostream>
#include <random>

namespace Globals
{
  namespace Functions
  {
    int random_in_range(int begin, int end)
    {
      std::random_device rdev;
      std::mt19937 generator(rdev());
      std::uniform_int_distribution<> distribute(begin, end);
      return distribute(generator);
    }
    int random_color_int(bool fullRange)
    {
      int
        darkLow   = 30,
        darkHigh  = 37,
        lightLow  = 90,
        lightHigh = 97;
      if (fullRange == false)
      {
        darkLow++;
        darkHigh--;
        lightLow++;
        lightHigh--;
      }
      return
      (
        random_in_range(0,1)?
        random_in_range(darkLow, darkHigh):
        random_in_range(lightLow, lightHigh)
      );
    }
    void check_arg_max(int argc, char *argv[])
    {
      try
      {
        if (argc > (Globals::Variables::Values::ARGMAX + 1))
        {
          throw std::runtime_error(Globals::Variables::Messages::ERRORMESSAGES[++Globals::Variables::Errors::error]);
        }
      }
      catch (std::runtime_error & rerr)
      {
        std::cerr << rerr.what() << '\n';
        std::exit(Globals::Variables::Errors::error);
      }
    }
    std::filesystem::path defaultPathOrThrow()
    {
      try
      {
        const char *HOMEPATH = getenv("HOME");
        if (HOMEPATH == NULL)
        {
          Globals::Variables::Errors::error = 2;
          throw std::runtime_error(Globals::Variables::Messages::ERRORMESSAGES[Globals::Variables::Errors::error]);
        }
        std::string configPathStr = std::string(HOMEPATH);
        configPathStr.append("/.config/UniShellect/unishellect.json");
        return std::filesystem::path(configPathStr);
      }
      catch (std::runtime_error &err)
      {
        std::cerr << err.what() << '\n';
        std::exit(Globals::Variables::Errors::error);
      }
    }
    int getIntegerInput(int maxIndex)
    {
      std::string input;
      bool isMatch = false;
      int number = -1;
      while ((!isMatch) || ((number < 0) || (number > maxIndex)))
      {
        getline(std::cin, input);
        isMatch = std::regex_match(input, Globals::Variables::Regex::R_UINT);
        if (isMatch)
        {
          number = std::stoi(input);
        }
        if ((number < 0) || (number > maxIndex))
        {
          std::cerr << "\r\'" << number << "\' is not within the range, (Ctrl+C to cancel): ";          
        }
        if (!isMatch)
        {
          std::cerr << "\r\'" << input << "\' is not a choice, please try again (Ctrl+C to cancel): ";
        }
      }
      return std::stoi(input);
    }
    std::string formattedSelectionMESSAGE(bool isMono, int SHELLMAPSZ)
    {
      std::string MESSAGE = "Make your selection [";
      if (!isMono)
      {
        MESSAGE.append("\x1b[");
        MESSAGE.append(std::to_string(random_color_int(false)));
        MESSAGE.append("m");
      }
      MESSAGE.append("0");
      if (!isMono)
      {
        MESSAGE.append("\x1b[m");
      }
      MESSAGE.append("-");
      if (!isMono)
      {
        MESSAGE.append("\x1b[");
        MESSAGE.append(std::to_string(random_color_int(false)));
        MESSAGE.append("m");
      }
      MESSAGE.append(std::to_string(SHELLMAPSZ - 1));
      if (!isMono)
      {
        MESSAGE.append("\x1b[m");
      }
      MESSAGE.append("]: ");
      return MESSAGE;
    }
    std::string formattedListMESSAGE(bool isMono, int index, std::map<int, Shell> shellMap)
    {
      std::string MESSAGE;
      MESSAGE.append("[");
      if (!isMono)
      {
        MESSAGE.append("\x1b[");
        MESSAGE.append(std::to_string(random_color_int(false)));
        MESSAGE.append("m");
      }
      MESSAGE.append(std::to_string(index));
      if (!isMono)
      {
        MESSAGE.append("\x1b[m");
      }
      MESSAGE.append("] ");
      MESSAGE.append(shellMap[index].Title);
      MESSAGE.append("\n");
      return MESSAGE;
    };
    void signal_handler(int signum)
    {
      Globals::Variables::Errors::error = ((signum == 2)?3:signum);
      std::cerr << '\n' << Globals::Variables::Messages::ERRORMESSAGES[Globals::Variables::Errors::error] << '\n';
      std::exit(Globals::Variables::Errors::error);
    }

  };
  namespace Variables
  {
    namespace Regex
    {
      const std::regex R_UINT("^[0-9]+$");
    };
    namespace Errors
    {
      int error = 0;
    };
    namespace Messages
    {
      const char * SUCCESS  = "Success...";
      const char * TMA      = "Too many options passed to this program...";
      const char * NOHOME   = "Could not get the value of HOME from the environment...";
      const char * USRCNC   = "User cancelled/interrupted...";
      std::map<int, const char *> ERRORMESSAGES =
      {
        {0, SUCCESS},
        {1, TMA},
        {2, NOHOME},
        {3, USRCNC}
      };
    };
    namespace Values
    {
      const int ARGMAX = 256;
    };
  };
};
