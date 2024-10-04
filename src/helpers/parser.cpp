#include "parser.h"
#include "dictionary.h"

#include <z/core/join.hpp>
#include <z/core/array.hpp>
#include <z/core/string.hpp>
#include <z/file/read.hpp>
#include <z/file/write.hpp>

using std::vector;
using z::core::join, z::file::read;

void addCommand(argparse::ArgumentParser &program, argparse::ArgumentParser &command, commandDetails cStruct)
{
    std::string desc = cStruct.mainStub + "e the input given a certain cipher and key";
    desc[0] = toupper(desc[0]);
    command.add_description(desc);

    // add cipher
    command
        .add_argument("cipher")
        .help("the cipher to use to " + cStruct.mainStub + "e")
        .choices("caesar", "substitution", "sub");

    // add key
    auto &keyGroup = command.add_mutually_exclusive_group(true);
    keyGroup.add_argument("-k", "--key")
        .help("the key to use (if no key is used, encode will use a random key and decode will crack the code)");
    keyGroup.add_argument("-K", "--keyfile")
        .help("the key file path");
    keyGroup.add_argument("-?", "--" + cStruct.randomKeyName)
        .flag()
        .help(cStruct.randomkeyDescription);

    // add remove spaces
    command.add_argument("-rs", "--removespaces")
        .help("removes spaces from the output")
        .flag();

    // add verbose
    command.add_argument("-V", "--verbose")
        .help("shows verbose output, if available (crack, for instance)")
        .flag();

    // add output
    command
        .add_argument("-O", "--outputfile")
        .help("the output file name for the result");

    // add input
    auto &inputGroup = command.add_mutually_exclusive_group(true);
    inputGroup.add_argument("-I", "--inputfile")
        .help("specify the input file to be " + cStruct.mainStub + "ed");
    inputGroup.add_argument("input")
        .help("the input to be " + cStruct.mainStub + "ed")
        .remaining();

    program.add_subparser(command);
}

// Helpers

parserArgs parse(argparse::ArgumentParser &parser, std::string randKeyName)
{
    // input
    zstring input = parser.present("--inputfile")
                        ? read(parser.get("--inputfile"))
                        : join(parser.get<vector<std::string>>("input"), " ");

    // filename
    std::string filename = "";
    if (parser.present("--outputfile"))
        filename = parser.get("--outputfile");

    // key
    std::string key;

    if (parser["--" + randKeyName] == true)
        key = "";
    else if (parser.present("--keyfile"))
        key = read(parser.get("--keyfile")).cstring();
    else
        key = parser.get("--key");

    // assemble with the easy stuff and return
    return parserArgs{
        parser.get("cipher"),
        key,
        input,
        filename,
        parser["--removespaces"] == true,
        parser["--verbose"] == true};
}
