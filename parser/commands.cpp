#include "commands.h"
#include "../libs/file.h"

// TODO: Can these easily be covered by tests?

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

void addKey(argparse::ArgumentParser &command, std::string randName, std::string description)
{
    auto &group = command.add_mutually_exclusive_group(true);
    group.add_argument("-k", "--key")
        .help("the key to use");
    group.add_argument("-K", "--keyfile")
        .help("the key file path");
    group.add_argument("-?", "--" + randName)
        .flag()
        .help(description);
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

std::string joinString(const std::vector<std::string> &lst, const std::string &delim) // TODO: Can we get this as a libzed function?
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
void addEncodeCommand(argparse::ArgumentParser &program, argparse::ArgumentParser &command)
{
    command.add_description("Encode the input given a certain cipher and key");

    addCipher(command);
    addOutput(command);
    addKey(command, "randomkey", "a random key will be used");

    command.add_argument("-rs", "--removespaces")
        .help("remove spaces from the output")
        .flag();

    addInput(command);

    program.add_subparser(command);
}

void addDecodeCommand(argparse::ArgumentParser &program, argparse::ArgumentParser &command)
{
    command.add_description("Decode the input given a certain cipher and key");

    addCipher(command);
    addOutput(command);
    addKey(command, "unknownkey", "the cipher will be cracked");

    command.add_argument("-ps", "--preservespaces")
        .help("does not add spaces to the output if they were not in the input")
        .flag();

    command.add_argument("-v", "--verbose")
        .help("shows verbose output, if available (crack, for instance)")
        .flag();

    addInput(command);

    program.add_subparser(command);
}

zstring getParserInput(argparse::ArgumentParser &parser)
{
    if (parser.present("--inputfile"))
        return loadFile(parser.get("--inputfile"));

    return zstring(joinString(parser.get<std::vector<std::string>>("input"), " ").c_str());
}

zstring getParserKey(argparse::ArgumentParser &parser, std::string keyFlagName)
{
    if (parser["--" + keyFlagName] == true)
        return "";

    if (parser.present("--keyfile"))
        return loadFile(parser.get("--keyfile"));

    return zstring(parser.get("--key").c_str());
}

void handleOutput(zstring output, argparse::ArgumentParser &parser)
{
    if (parser.present("--outputfile"))
        (writeFile(output, parser.get("--outputfile")) ? "Written to output file"_u8 : "Something went wrong"_u8).writeln(std::cout);
    else
        output.writeln(std::cout);
}
