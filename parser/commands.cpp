#include "commands.h"
#include "../libs/file.h"

// Helpers
void addCipher(argparse::ArgumentParser &command)
{
    command.add_argument("cipher")
        .help("the cipher to use")
        .choices("caesar", "substitution", "sub");
}

void addOutput(argparse::ArgumentParser &command)
{
    command.add_argument("-O", "--outputfile")
        .help("the output file name for the result");
}

void addEncodeKey(argparse::ArgumentParser &command)
{
    auto &group = command.add_mutually_exclusive_group(true);
    group.add_argument("-k", "--key")
        .help("the key to use");
    group.add_argument("-K", "--keyfile")
        .help("the key file path");
    group.add_argument("-?", "--randomkey")
        .flag()
        .help("a random key will be used");
}

void addDecodeKey(argparse::ArgumentParser &command)
{
    auto &group = command.add_mutually_exclusive_group(true);
    group.add_argument("-k", "--key")
        .help("the key to use");
    group.add_argument("-K", "--keyfile")
        .help("the key file path");
    group.add_argument("-?", "--unknownkey")
        .flag()
        .help("the cipher will be cracked");
}

void addInput(argparse::ArgumentParser &command)
{
    auto &group = command.add_mutually_exclusive_group(true);
    group.add_argument("-I", "--inputfile")
        .help("specify the input file to be encoded");
    group.add_argument("input")
        .help("the input to be encoded")
        .remaining();
}

std::string joinString(const std::vector<std::string> &lst, const std::string &delim)
{
    std::string ret;

    for (const auto &s : lst)
    {
        if (!ret.empty())
            ret += delim;

        ret += s;
    }

    return ret;
}

// Mains
// Consider adding remove/preserve spacing option
void addEncodeCommand(argparse::ArgumentParser &program, argparse::ArgumentParser &command)
{
    command.add_description("Encode the input given a certain cipher and key");

    addCipher(command);
    addOutput(command);
    addEncodeKey(command);
    addInput(command);

    program.add_subparser(command);
}

// Consider adding remove/preserve spacing option
void addDecodeCommand(argparse::ArgumentParser &program, argparse::ArgumentParser &command)
{
    command.add_description("Decode the input given a certain cipher and key");

    addCipher(command);
    addOutput(command);
    addDecodeKey(command);
    addInput(command);

    program.add_subparser(command);
}

zstring getParserInput(argparse::ArgumentParser &parser)
{
    if (parser.present("--inputfile"))
        return loadFile(parser.get("--inputfile"));

    return zstring(joinString(parser.get<std::vector<std::string>>("input"), " ").c_str());
}

zstring getParserKey(argparse::ArgumentParser &parser)
{
    if (parser["--randomkey"] == true)
        return "";

    if (parser.present("--keyfile"))
        return loadFile(parser.get("--keyfile"));

    return zstring(parser.get("--key").c_str());
}

void handleOutput(zstring output, argparse::ArgumentParser &parser)
{
    if (parser.present("--outputfile"))
        writeFile(output, parser.get("--outputfile"));
    else
        ("\n"_u8 + output).writeln(std::cout);
}
