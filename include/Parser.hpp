#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>

class Parser
{
    public:
        Parser(int argc, char **argv);
        bool IsValidParm();
        void SetDiningRule();
    private:
        int _argc;
        char **_argv;
        bool IsInvalidCount();
        bool IsWrongType();
};


#endif