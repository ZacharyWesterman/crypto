#include "parser.h"

#include <z/core/join.hpp>
#include <z/core/array.hpp>
#include <z/core/string.hpp>
#include <z/file/read.hpp>
#include <z/file/write.hpp>

// FIXME: throws some sort of undefined / linker error
// template <typename T>
// zstring processResults(z::core::array<T> results, bool verbose)
// {
//     if (!verbose)
//         return results[0].text;

//     zstring output = "";

//     output += "The best solution ("_u8 + results[0].score +
//               "% confidence with a key of " + results[0].key + ") is:\n  " +
//               results[0].text + "\n";

//     if (results[0].score < 80)
//     {
//         output += "\nLow Confidence! Presenting alternatives...\n\n";

//         for (int i = 1; i < results.length(); i++)
//             output += results[i].summary;
//     }

//     return "\n"_u8 + output.trim() + "\n"; // HACK: What are the actual newline locations?
// }

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

std::string getKey(argparse::ArgumentParser &parser, std::string keyFlagName)
{
    if (parser["--" + keyFlagName] == true)
        return "";

    if (parser.present("--keyfile"))
        return z::file::read(parser.get("--keyfile")).cstring();

    return parser.get("--key");
}

void handleOutput(zstring output, argparse::ArgumentParser &parser)
{
    if (parser.present("--outputfile"))
    {
        z::file::write(output, parser.get("--outputfile"));
    }
    else
        output.writeln(std::cout);
}
