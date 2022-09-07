#include "ParseArgs.h"
#include <iostream>
#include <regex>
#include <vector>

args_ args;

void ParseArgs::parse(int min, int max)
{
  const std::regex R_HELP("^-([hH]|-[hH][eE][lL][pP])$");
  const std::regex R_CONF("^-([cC]|-[cC][oO][nN][fF][iI][gG])$");
  const std::regex R_MONO("^-([mM]|-[mM][oO][nN][oO][cC][hH][rR][oO][mM][eE])$");
  const std::vector<std::string> BOX =
  {
    u8"\u250C", u8"\u2500", u8"\u2510", u8"\u2502",
    u8"\u2514", u8"\u2518", u8"\u251C", u8"\u2524"
  };
  bool skip = false;
  for (int i = min; i < max; i++)
  {
    if (skip)
    {
      skip = false;
      continue;
    }
    std::string thisArg = argV[i];
    if (std::regex_match(thisArg, R_HELP))
    {
      std::string line;
      for (int i = 0; i < 48; i++) line += BOX[1];
      const std::string HELPMESSAGE =
          BOX[0] + line + BOX[2] + "\n" +
          BOX[3] + " UniShellect                                    " + BOX[3] + "\n" +
          BOX[6] + line + BOX[7] + "\n" +
          BOX[3] + " USAGE: unishellect [OPTIONS [FILE]...]...      " + BOX[3] + "\n" +
          BOX[3] + " Load a menu of shells/files from a provided    " + BOX[3] + "\n" +
          BOX[3] + " JSON configuration file. The default is:       " + BOX[3] + "\n" +
          BOX[3] + " $HOME/.config/UniShellect/unishellect.json     " + BOX[3] + "\n" +
          BOX[3] + " in Linux and:                                  " + BOX[3] + "\n" +
          BOX[3] + " \%USERPROFILE%\\\\.config\\\\UniShellect-           " + BOX[3] + "\n" +
          BOX[3] + " \\\\unishellect.json                             " + BOX[3] + "\n" +
          BOX[3] + " in Windows.                                    " + BOX[3] + "\n" +
          BOX[6] + line + BOX[7] + "\n" +
          BOX[3] + " OPTIONS: switches and arguments                " + BOX[3] + "\n" +
          BOX[3] + "   -h,--help       This HELP message.           " + BOX[3] + "\n" +
          BOX[3] + "   -c,--config     Load an alternate config     " + BOX[3] + "\n" +
          BOX[3] + "                   file.                        " + BOX[3] + "\n" +
          BOX[3] + "   -m,--monochrome All output is monochrome;    " + BOX[3] + "\n" +
          BOX[3] + "                   no color.                    " + BOX[3] + "\n" +
          BOX[6] + line + BOX[7] + "\n" +
          BOX[3] + " Exit Codes: Error codes and their meanings.    " + BOX[3] + "\n" +
          BOX[3] + "   0   No errors.                               " + BOX[3] + "\n" +
          BOX[3] + "   1   Too many options passed to the           " + BOX[3] + "\n" +
          BOX[3] + "       program.                                 " + BOX[3] + "\n" +
          BOX[3] + "   2   Could not get the value of HOME from     " + BOX[3] + "\n" +
          BOX[3] + "       the environment.                         " + BOX[3] + "\n" +
          BOX[3] + "   3   User cancelled/interrupted.              " + BOX[3] + "\n" +
          BOX[3] + "   4   No FILE/argument provided for the        " + BOX[3] + "\n" +
          BOX[3] + "       -c,--config OPTION.                      " + BOX[3] + "\n" +
          BOX[3] + "   101 Error while parsing JSON in a config     " + BOX[3] + "\n" +
          BOX[3] + "       file.                                    " + BOX[3] + "\n" +
          BOX[3] + "   *   Any additional errors are related to     " + BOX[3] + "\n" +
          BOX[3] + "       opening and reading from the provided    " + BOX[3] + "\n" +
          BOX[3] + "       config file.                             " + BOX[3] + "\n" +
          BOX[4] + line + BOX[5] + "\n";
      std::cout << HELPMESSAGE;
      std::exit(0);
    }
    if (std::regex_match(thisArg, R_CONF))
    {
      try
      {
        std::string nextArg = argV[i + 1];
        args.configFile = std::filesystem::path(nextArg);
        args.isDefaultConfig = false;
        skip = true;
      }
      catch (std::logic_error & lerr)
      {
        const std::string message =
                "No option provided for '" + thisArg + "'.\n[" + lerr.what() + "]\n";
        std::cerr << message;
        std::exit(4);
      }
      continue;   
    }
    if (std::regex_match(thisArg, R_MONO))
    {
      args.ioIsMono = true;
      continue;
    }
  }
}
