#pragma once

#include <string>
#include <windows.h>

namespace aff {
  namespace util {

enum class ConsoleColor
{
  Default = 7,
  Warning = 14,
  Fatal = 71,
  Error = 4
};

class Logger
{
public:
  Logger(std::string class_name);
  virtual ~Logger();

  virtual void Info(std::string message, bool show_time = true) const;
  virtual void Warn(std::string message, bool show_time = true) const;
  virtual void Error(std::string message, bool show_time = true) const;
  virtual void Fatal(std::string message, bool show_time = true) const;
  virtual void Notice(std::string message, bool show_time = true) const;

  static std::string TimeNow();
protected:
  std::string class_name_;

  void ShowMessage(std::string header, std::string message, bool show_time) const;
  void SetTextColor(ConsoleColor color) const;
};

// ~~ aff::util::Logger
}}
