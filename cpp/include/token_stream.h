#ifndef LEXER_H_
#define LEXER_H_

#include "token.h"
#include <memory>
#include <string>
#include <istream>

std::istream &
operator>> (std::istream &in, std::shared_ptr <const token> &ptr);

#endif // LEXER_H_
