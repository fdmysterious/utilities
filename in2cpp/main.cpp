// Turns data from stdin into a c++ array header.
// Usage   : buf2cpp tabName
// Example : cat file | buf2cpp tabName > tab.inc.hpp

#include <iostream>
#include <string>
#include <cstdint>

const char evilTab[] {
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
};

int main(int argc, const char *argv[])
{
    std::string name = argc < 2 ? "data" : std::string(argv[1]);
    std::string NAME = name;
    for( auto & c : NAME ) c = toupper(c);

    std::cout << "#ifndef HEADER_" << NAME << std::endl << "#define HEADER_" << NAME << std::endl
              << "#include <cstdint>"     << std::endl
              << "namespace " << name << std::endl << "{" << std::endl
              << "    const std::uint8_t data[] {"
    ;

    char  c;
    std::uint64_t count; //number of bytes in the stream
    for( count = 0 ; std::cin.get( c ) ; count++ )
    {
        if( count ) std::cout << ", ";
        if( !(count % 10) ) std::cout << std::endl << "        ";

        std::cout << "0x" << evilTab[(c & 0xF0) >> 4] << evilTab[c & 0x0F];
    }

    std::cout << std::endl << "    };" << std::endl
              << "    const std::uint64_t size = " << count << ";" << std::endl
              << "}" << std::endl
              << "#endif" << std::endl
    ;

    return 0;
}

