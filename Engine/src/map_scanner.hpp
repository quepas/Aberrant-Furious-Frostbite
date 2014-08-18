#pragma once

#include "util_logger.hpp"

#include <string>
#include <map>
#include <vector>

namespace aff {
  namespace map {

enum class EntryType
{
  CAMERA,
  SKYBOX,
  ENTITY
};

struct Entry
{
  EntryType type;
  std::map<std::string, float> numbers;
  std::map<std::string, std::string> text;
};

enum class TokenType
{
  ENTITY_ATTRIB,
  ENTITY_ID,
  ENTITY_TYPE,
  CAMERA,
  SKYBOX,
  ENTITY,
  NUMERIC,
  TEXT,
  EQ,
  COMMA,
  LSQUARE,
  RSQUARE,
  LBRACKET,
  RBRACKET,
  SEMICOLON
};

struct Token
{
  TokenType type;
  std::string text;
  float numeric;
};

class Scanner
{
public:
  Scanner(std::string file_name);
  ~Scanner();

private:
  const std::vector<Token>& ReadFile(const std::string& file_name);
  const std::vector<Entry>& ParseFile(const std::vector<Token>& tokens);
  Entry ParseEntry(const Token& token, unsigned int& out_last_idx);

  bool CheckNextTokens(TokenType* types);

  Token CreateToken(TokenType type);
  Token CreateToken(TokenType type, float numeric);
  Token CreateToken(TokenType type, std::string text);

  std::vector<Token> tokens_;
  std::vector<Entry> entries_;

  static util::Logger logger_;
};

}}
// ~~ aff::map::Scanner
