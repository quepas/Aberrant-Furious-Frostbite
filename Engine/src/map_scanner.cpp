#include "map_scanner.hpp"

#include <cctype>
#include <fstream>

using aff::util::Logger;
using std::ifstream;
using std::isalpha;
using std::isdigit;
using std::isspace;
using std::string;

namespace aff {
  namespace map {

Logger Scanner::logger_("Scanner");

Scanner::Scanner(string file_name)
{
  ReadFile(file_name);
}

Scanner::~Scanner()
{

}

const std::vector<Token>& Scanner::ReadFile(const string& file_name)
{
  tokens_.clear();
  ifstream file(file_name);
  if (!file.is_open()) {
    logger_.Error("Can't open map file: " + file_name);
    return tokens_;
  }

  char c = file.get();
  string value = "";
  bool eof = false;
  while (!eof) {
    value = "";
    while (isspace(c)) { c = file.get(); }
    // id or keyword
    if (isalpha(c)) {
      while (isalpha(c) || isdigit(c) || c == '_') { value += c; c = file.get(); }
      if (value == "camera") {
        tokens_.push_back(CreateToken(TokenType::CAMERA));
      }
      else if (value == "skybox") {
        tokens_.push_back(CreateToken(TokenType::SKYBOX));
      }
      else if (value == "entity") {
        tokens_.push_back(CreateToken(TokenType::ENTITY));
      }
      else {
        tokens_.push_back(CreateToken(TokenType::ENTITY_ATTRIB, value));
      }
      logger_.Info("Keyword: " + value);
      getchar();
    }
    // numeric
    else if (c == '-' || isdigit(c)) {
      while (isdigit(c) || c == '.' || c == '-') { value += c; c = file.get(); }
      tokens_.push_back(CreateToken(TokenType::NUMERIC, std::stof(value)));
      logger_.Info("Numeric: " + value);
      getchar();
    }
    // text
    else if (c == '\"') {
      logger_.Info("Text");
      getchar();
    }
    // special symbols
    else {
      logger_.Info(string("Symbol: ") + c);
      getchar();
      TokenType token_type;
      switch (c) {
      case EOF:
        logger_.Info("EOF");
        return tokens_;
      case '[':
        token_type = TokenType::LSQUARE;
        break;
      case ']':
        token_type = TokenType::RSQUARE;
        break;
      case '(':
        token_type = TokenType::LBRACKET;
        break;
      case ')':
        token_type = TokenType::RBRACKET;
        break;
      case ',':
        token_type = TokenType::COMMA;
        break;
      case '=':
        token_type = TokenType::EQ;
        break;
      case ';':
        token_type = TokenType::SEMICOLON;
      default:
        break;
      }
      tokens_.push_back(CreateToken(token_type));
      c = file.get();
    }
  }
  return tokens_;
}

aff::map::Token Scanner::CreateToken(TokenType type)
{
  Token token;
  token.type = type;
  return token;
}

aff::map::Token Scanner::CreateToken(TokenType type, float numeric)
{
  Token token;
  token.type = type;
  token.numeric = numeric;
  return token;
}

aff::map::Token Scanner::CreateToken(TokenType type, std::string text)
{
  Token token;
  token.type = type;
  token.text = text;
  return token;
}

const std::vector<Entry>& Scanner::ParseFile(const std::vector<Token>& tokens)
{
  unsigned int idx = 0;
  while (true) {
    auto token = tokens[idx];

    switch (token.type) {
    case TokenType::CAMERA:
      token = tokens[++idx];
      if (token.type == TokenType::EQ) {
        token = tokens[++idx];
        if (token.type == TokenType::LSQUARE) {
          token = tokens[++idx];
          //if (token.type == )
        }
        else {
          logger_.Error("Should be left square bracket [ here");
        }
      }
      else {
        logger_.Error("Should be equal sign = here");
      }
      break;
    case TokenType::SKYBOX:
      break;
    case TokenType::ENTITY:
      break;
    default:
      logger_.Error("Incorrect ID");
      return entries_;
    }
  }

  return entries_;
}

Entry Scanner::ParseEntry(const Token& token, unsigned int& out_last_idx)
{
  CheckNextTokens(new TokenType []{TokenType::ENTITY_ATTRIB, TokenType::CAMERA});
  return Entry();
}

bool Scanner::CheckNextTokens(TokenType* types)
{
  return true;
}

}}
// ~~ aff::map::Scanner
