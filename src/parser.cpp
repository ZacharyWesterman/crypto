#include "parser.h"

#include <z/core/join.hpp>
#include <z/file/read.hpp>
#include <z/file/write.hpp>

// TODO: Possibly add all args to both commands and only ignore the irrelevant ones

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
        .help("the key to use");
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

zstring getInput(argparse::ArgumentParser &parser)
{
    if (parser.present("--inputfile"))
        return z::file::read(parser.get("--inputfile"));

    return z::core::join(parser.get<std::vector<std::string>>("input"), " ");
}

zstring getKey(argparse::ArgumentParser &parser, std::string keyFlagName)
{
    if (parser["--" + keyFlagName] == true)
        return "";

    if (parser.present("--keyfile"))
        return z::file::read(parser.get("--keyfile"));

    return zstring(parser.get("--key").c_str());
}

void handleOutput(zstring output, argparse::ArgumentParser &parser)
{
    if (parser.present("--outputfile"))
    {
        z::file::write(output, parser.get("--outputfile"));
        "Written to output file"_u8.writeln(std::cout);
    }
    else
        output.writeln(std::cout);
}
