#pragma once

#include <string>

namespace aff {
  namespace util {

class Logger
{
public:
  Logger(std::string class_name);
  virtual ~Logger();

  virtual void Info(std::string message, bool show_time = true);
  virtual void Warn(std::string message, bool show_time = true);
  virtual void Error(std::string message, bool show_time = true);
  virtual void Fatal(std::string message, bool show_time = true);
  virtual void Notice(std::string message, bool show_time = true);

  static std::string TimeNow();
protected:
  std::string class_name_;

  void ShowMessage(std::string header, std::string message, bool show_time);
};

// ~~ aff::util::Logger
}}
