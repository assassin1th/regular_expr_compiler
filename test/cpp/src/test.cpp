#include "compiler/cpp/include/lex.h"
#include <iostream>

template <typename T>
std::ostream &
operator << (std::ostream &out, const std::unique_ptr<T> &ptr)
{
    out << *ptr;
    return out;
}

static
void
lex_test ()
{
#define TEST_STRING "hello, world!!"

    compiler::lex lex (TEST_STRING);

    std::unique_ptr <const compiler::token> tok = lex.scan();
    while (tok->tag () != '\0')
    {
        std::cout << tok << std::endl;
        tok = lex.scan();
    }

    std::cout << "src string:" << std::endl <<
                 TEST_STRING   << std::endl;

#undef TEST_STRING
}

int
main (int argc, char *argv[])
{
    std::cout << sizeof (std::unique_ptr<compiler::token>) << std::endl;

    lex_test ();

    return 0;
}

