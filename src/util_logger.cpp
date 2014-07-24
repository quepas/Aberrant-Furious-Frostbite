#include "util_logger.hpp"

#include <ctime>
#include <chrono>
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>

using std::tm;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::time_t;
using std::put_time;
using std::chrono::system_clock;

namespace aff {
  namespace util {

Logger::Logger(std::string class_name)
  : class_name_(class_name)
{
}

Logger::~Logger()
{
}

void Logger::Info(std::string message, bool show_time /*= true*/)
{
  ShowMessage(" [Info/" + class_name_ + "] ", message, show_time);
}

void Logger::Warn(std::string message, bool show_time /*= true*/)
{
  ShowMessage(" [Warn/" + class_name_ + "] ", message, show_time);
}

void Logger::Error(std::string message, bool show_time /*= true*/)
{
  ShowMessage(" [Error/" + class_name_ + "] ", message, show_time);
}

void Logger::Fatal(std::string message, bool show_time /*= true*/)
{
  ShowMessage(" [Fatal/" + class_name_ + "] ", message, show_time);
}

void Logger::Notice(std::string message, bool show_time /*= true*/)
{
  ShowMessage(" [Notice/" + class_name_ + "] ", message, show_time);
}

string Logger::TimeNow()
{
  system_clock::time_point now = system_clock::now();
  time_t now_c = system_clock::to_time_t(now);

  stringstream time_to_str;  
  tm time_struct;
  localtime_s(&time_struct, &now_c);
  time_to_str << put_time(&time_struct, "%H:%M:%S");
  string result;
  time_to_str >> result;
  return result;
}

void Logger::ShowMessage(
  string header, string message, bool show_time)
{
  cout << (show_time ? TimeNow() : "") << header << message << endl;
}

// ~~ aff::util::Logger
}}
