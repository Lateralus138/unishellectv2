#pragma once
#ifndef Globals_H
#define Globals_H
#include <map>
#include <filesystem>
#include <regex>

struct Shell
{
  std::string Title;
  std::string Path;
  std::string Args;
};

namespace Globals
{
  namespace Functions
  {
    extern int random_in_range(int begin, int end);
    extern int random_color_int(bool fullRange);
    extern void check_arg_max(int argc, char *argv[]);
    extern std::filesystem::path defaultPathOrThrow();
    extern int getIntegerInput(int maxIndex);
    extern std::string formattedSelectionMESSAGE(bool isMono, int SHELLMAPSZ);
    extern std::string formattedListMESSAGE(bool isMono, int index, std::map<int, Shell> shellMap);
    extern  void signal_handler(int signum);
  };
  namespace Variables
  {
    namespace Regex
    {
      extern const std::regex R_UINT;
    };
    namespace Errors
    {
      extern int error;
    };
    namespace Messages
    {
      extern const char * SUCCESS;
      extern const char * TMA;
      extern const char * PROCNODIR;
      extern std::map <int, const char *> ERRORMESSAGES;
    };
    namespace Values
    {
      extern const int ARGMAX;
    };
  };
};

#endif
