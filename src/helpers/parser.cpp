#include "parser.h"
#include "dictionary.h"

#include <z/core/join.hpp>
#include <z/core/array.hpp>
#include <z/core/string.hpp>
#include <z/file/read.hpp>
#include <z/file/write.hpp>

using std::vector;
using z::core::join, z::file::read;

void setupProgram(argparse::ArgumentParser &program)
{
    program.add_description("a cryptography program");

    program
        .add_argument("mode")
        .help("whether we're encoding or decoding")
        .choices("encode", "decode");

    // add cipher
    program
        .add_argument("cipher")
        .help("the cipher to use to")
        .choices("caesar", "substitution", "sub");

    // add key
    auto &keyGroup = program.add_mutually_exclusive_group();
    keyGroup.add_argument("-k", "--key")
        .help("the key to use (if no key is used, encode will use a random key and decode will crack the code)");
    keyGroup.add_argument("-K", "--keyfile")
        .help("the path to the file containing the key");

    // add remove spaces
    program.add_argument("-rs", "--removespaces")
        .help("removes spaces from the output")
        .flag();

    // add verbose
    program.add_argument("-V", "--verbose")
        .help("shows verbose output, if available (crack, for instance)")
        .flag();

    // add output
    program
        .add_argument("-O", "--outputfile")
        .help("the output file name for the result");

    // add input
    auto &inputGroup = program.add_mutually_exclusive_group(true);
    inputGroup.add_argument("-I", "--inputfile")
        .help("specify the input file");
    inputGroup.add_argument("-p", "--piped")
        .help("accept piped input")
        .flag();
    inputGroup.add_argument("input")
        .help("the input (if a file isn't specified)")
        .remaining();
}

programArgs parse(argparse::ArgumentParser &program)
{
    // input
    zstring input;
    if (program.present("--inputfile"))
        input = read(program.get("--inputfile"));
    else if (program.present("input"))
        input = join(program.get<vector<std::string>>("input"), " ");
    else if (program["--piped"] == true)
        input.readall(std::cin);

    // filename
    std::string filename = "";
    if (program.present("--outputfile"))
        filename = program.get("--outputfile");

    // key
    std::string key;

    if (program.present("--keyfile"))
        key = read(program.get("--keyfile")).cstring();
    else if (program.present("--key"))
        key = program.get("--key");
    else
        key = "";

    // assemble with the easy stuff and return
    return programArgs{false,
                       program.get("mode") == "encode",
                       program.get("cipher"),
                       key,
                       input,
                       filename,
                       program["--removespaces"] == true,
                       program["--verbose"] == true};
}
