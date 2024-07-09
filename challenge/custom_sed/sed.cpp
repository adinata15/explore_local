#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <exception>
#include <vector>
#include <sstream>

enum INPUT_TYPE
{
    OPTION_ID = 0,
    PATTERN,
    OPTION_VAL,
    INPUT_FILE,
    UNKNOWN_INPUT_TYPE,
};

enum OPTIONS
{
    IN_PLACE = 0,
    LINE_NUM,
    UNKNOWN_OPTION,
};

enum ACTION_TYPE
{
    SUBS_ACTION = 0,
    PRINT_ACTION,
    UNKNOWN_ACTION,
};

enum ERROR_TYPE
{
    NO_ERROR = 0,
    PARSE_ERROR,
    UNKNOWN_ERROR,
};

std::vector<std::string> read_txt(const std::string &filepath)
{
    std::vector<std::string> data;
    std::string line;
    std::fstream file = std::fstream(filepath, std::ios::in | std::ios::out);

    if (file.is_open())
    {
        while (getline(file, line))
        {
            data.push_back(line);
        }
    }

    file.close();

    return data;
}

void substitute(std::vector<std::string> &data, const std::string &target, const std::string &replacement, bool is_global)
{
    for (std::string &line : data)
    {
        std::regex r_target(target);
        if (is_global)
            line = std::regex_replace(line, r_target, replacement, std::regex_constants::match_any);
        else
            line = std::regex_replace(line, r_target, replacement, std::regex_constants::format_first_only);
    }
}

ERROR_TYPE parsePattern(char *pattern, std::vector<std::string> &tokens)
{
    std::string curr;

    for (size_t i = 0; pattern[i] != NULL; ++i)
    {
        if (pattern[i] == '/')
        {
            tokens.push_back(curr);
            curr.clear();
        }
        else if (pattern[i] == '\\')
        {
            if (pattern[i + 1] == NULL)
            {
                return PARSE_ERROR;
            }
            i++;
            curr += pattern[i];
        }
        else
        {
            curr += pattern[i];
        }
    }

    if (!curr.empty())
    {
        tokens.push_back(curr);
    }
    return NO_ERROR;
}

ERROR_TYPE parseCommand(int argc, char *argv[], std::unordered_map<OPTIONS, std::string> &options_map, std::string &filepath, std::vector<std::string> &pattern_tokens)
{
    if (std::string(argv[0]) != "./ccsed")
    {
        return PARSE_ERROR;
    }

    OPTIONS prev_opt = UNKNOWN_OPTION;
    for (int i = 1; i < argc; ++i)
    {
        // last args assumed to be input file path
        if (i == argc - 1)
        {
            filepath = argv[i];
            continue;
        }

        if (prev_opt != UNKNOWN_OPTION)
        {
            options_map[prev_opt] = argv[i];
            prev_opt = UNKNOWN_OPTION;
            continue;
        }

        std::string input = std::string(argv[i]);
        if (input[0] == '-')
        {
            std::string option = input.substr(1, input.length());
            if (option == "n")
            {
                prev_opt = LINE_NUM;
            }
            else if (option == "i")
            {
                prev_opt = IN_PLACE;
            }
            else
            {
                prev_opt = UNKNOWN_OPTION;
            }
        }
        else
        {
            if (NO_ERROR != parsePattern(argv[i], pattern_tokens))
            {
                return PARSE_ERROR;
            }
        }
    }
    return NO_ERROR;
}

void execute(std::unordered_map<OPTIONS, std::string> &options_map, std::string &filename, std::vector<std::string> &pattern_tokens, std::vector<std::string> &data)
{
    data = read_txt(filename);
    if (pattern_tokens[0] == "s")
    {
        substitute(data, pattern_tokens[1], pattern_tokens[2], pattern_tokens.size() > 3 && pattern_tokens[3] == "g");
    }
}

void print_output(std::vector<std::string> &data)
{
    for (std::string &d : data)
    {
        std::cout << d << std::endl;
    }
}

int main(int argc, char *argv[])
{
    std::string filename;
    std::unordered_map<OPTIONS, std::string> options_map;
    std::vector<std::string> pattern_tokens, data;

    if (NO_ERROR != parseCommand(argc, argv, options_map, filename, pattern_tokens))
    {
        std::cout << "Parse error!" << std::endl;
        return 1;
    }

    // std::cout << "filename: " << filename << std::endl;
    // std::cout << "tokens: ";
    // for (std::string &s : pattern_tokens)
    // {
    //     std::cout << s << " ";
    // }
    // std::cout << std::endl;

    execute(options_map, filename, pattern_tokens, data);
    
    print_output(data);

    return 0;
}