#include "commands.h"

void generateEncodeCommand(argparse::ArgumentParser &command)
{
    command.add_description("Encode the input given a certain cipher and key");

    command.add_argument("cipher")
        .help("the cipher to use for the encoding")
        .choices("caesar");

    command.add_argument("-O", "--outputfile")
        .help("the output file name for the result");

    auto &keyGroup = command.add_mutually_exclusive_group(true);
    keyGroup.add_argument("-k", "--key")
        .help("the key to use for the encoding");
    keyGroup.add_argument("-K", "--keyfile")
        .help("the key file path to use for the encoding");
    keyGroup.add_argument("-?", "--randomkey")
        .flag()
        .help("a random key will be used for the encoding");

    auto &inputGroup = command.add_mutually_exclusive_group(true);
    inputGroup.add_argument("-I", "--inputfile")
        .help("specify the input file to be encoded");
    inputGroup.add_argument("input")
        .help("the input to be encoded")
        .remaining();
}

void generateDecodeCommand(argparse::ArgumentParser &command)
{
    command.add_description("Decode the input given a certain cipher and key");

    command.add_argument("cipher")
        .help("the cipher to use for the decoding")
        .choices("caesar");

    command.add_argument("-O", "--outputfile")
        .help("the output file name for the result");

    auto &keyGroup = command.add_mutually_exclusive_group(true);
    keyGroup.add_argument("-k", "--key")
        .help("the key to use for the decoding");
    keyGroup.add_argument("-K", "--keyfile")
        .help("the key file path to use for the decoding");

    auto &inputGroup = command.add_mutually_exclusive_group(true);
    inputGroup.add_argument("-I", "--inputfile")
        .help("specify the input file to be decoded");
    inputGroup.add_argument("input")
        .help("the input to be decoded")
        .remaining();
}

void generateCrackCommand(argparse::ArgumentParser &command)
{
    command.add_description("Crack the input given a certain cipher");

    command.add_argument("cipher")
        .help("the cipher to use for the decoding")
        .choices("caesar");

    command.add_argument("-O", "--outputfile")
        .help("the output file name for the result");

    auto &inputGroup = command.add_mutually_exclusive_group(true);
    inputGroup.add_argument("-I", "--inputfile")
        .help("specify the input file to be decoded");
    inputGroup.add_argument("input")
        .help("the input to be decoded")
        .remaining();
}
