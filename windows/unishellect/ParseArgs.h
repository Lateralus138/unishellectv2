#pragma once
#ifndef PARSEARGS_H
#define PARSEARGS_H

#include <vector>
#include <string>
#include <filesystem>

struct args_
{
  bool ioIsMono;
  bool isDefaultConfig;
  std::filesystem::path configFile;
};
extern struct args_ args;

class ParseArgs
{
private:
  int argC;
  char ** argV;
  std::vector<std::string_view> argS;
public:
  ParseArgs(int argc_, char ** argv_)
  {
    parseArgs(argc_, argv_);
  }
  void parseArgs(int argc_, char ** argv_)
  {
    setArgC(argc_);
    setArgV(argv_);
    setArgS();
  }
  void setArgC(int argc_)
  {
    argC = argc_;
  }
  int getArgC()
  {
    return argC;
  }
  void setArgV(char ** argv_)
  {
    argV = argv_;
  }
  char ** getArgV()
  {
    return argV;
  }
  void setArgS()
  {
    argS = std::vector<std::string_view>(argV + 0, argV + argC);
  }
  std::vector<std::string_view> getArgS()
  {
    return argS;
  }
  void parse(int min, int max);
};

#endif
