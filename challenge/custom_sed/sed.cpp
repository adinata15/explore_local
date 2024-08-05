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
    ADD_SPACE,
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
    INPUT_ERROR,
    FILE_ERROR,
    UNKNOWN_ERROR,
};

std::vector<std::string> read_txt(const std::string &filepath)
{
    std::vector<std::string> data;
    std::string line;
    std::fstream file(filepath, std::ios::out | std::ios::in);

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

ERROR_TYPE write_txt(const std::string &filepath, const std::vector<std::string> &data)
{
    std::string line;
    std::fstream file(filepath, std::ios::in | std::ios::out | std::ios::trunc); // trunc to complete overwrite file

    if (file.is_open())
    {
        for (const std::string &line : data)
        {
            file << line;
            file << std::endl;
        }
    }
    else
    {
        return FILE_ERROR;
    }

    file.close();
    return NO_ERROR;
}

void substitute(std::vector<std::string> &data, const std::string &target, const std::string &replacement, bool is_global)
{
    for (size_t i = 0; i < data.size(); ++i)
    {
        std::string &line = data[i];
        std::regex r_target(target);
        if (is_global)
            line = std::regex_replace(line, r_target, replacement, std::regex_constants::match_any);
        else
            line = std::regex_replace(line, r_target, replacement, std::regex_constants::format_first_only);
    }
}

ERROR_TYPE parsePattern(const std::string &pattern, std::vector<std::string> &tokens)
{
    std::string curr;

    for (size_t i = 0; i < pattern.size(); ++i)
    {
        if (pattern[i] == '/')
        {
            tokens.push_back(curr);
            curr.clear();
        }
        else if (pattern[i] == '\\')
        {
            if (i == pattern.size() - 1)
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

ERROR_TYPE parseOption(int argc, char *argv[], std::unordered_map<OPTIONS, std::string> &options_map, int &idx)
{
    while (idx < argc && argv[idx][0] == '-')
    {
        if (argv[idx][1] == 'i')
        {
            options_map[IN_PLACE] = "i";
        }
        else if (argv[idx][1] == 'G')
        {
            options_map[ADD_SPACE] = "g";
        }
        else if (argv[idx][1] == 'n')
        {
            if (idx >= argc - 1)
                return PARSE_ERROR;

            idx++;
            options_map[LINE_NUM] = argv[idx];
        }
        idx++;
    }
    return NO_ERROR;
}

ERROR_TYPE parseCommand(int argc, char *argv[], std::unordered_map<OPTIONS, std::string> &options_map, std::string &filepath, std::vector<std::string> &pattern_tokens)
{
    if (std::string(argv[0]) != "./ccsed")
    {
        return PARSE_ERROR;
    }

    int idx = 1;
    if (parseOption(argc, argv, options_map, idx) != NO_ERROR)
    {
        return PARSE_ERROR;
    }

    if (idx < argc - 1)
    {
        if (NO_ERROR != parsePattern(argv[idx], pattern_tokens))
        {
            return PARSE_ERROR;
        }
        idx++;
    }

    if (idx != argc - 1)
    {
        return PARSE_ERROR;
    }

    filepath = argv[idx];

    return NO_ERROR;
}

ERROR_TYPE filterData(std::vector<std::string> &data, size_t start, size_t end, const std::string &search_pattern)
{
    if (start <= 0 || end > data.size())
    {
        return INPUT_ERROR;
    }
    std::regex pattern(search_pattern);
    std::vector<std::string> temp;
    for (size_t i = start - 1; i <= end; ++i)
    {
        if (std::regex_search(data[i], pattern))
        {
            temp.push_back(data[i]);
        }
    }
    data = temp;
    return NO_ERROR;
}

void execute(std::unordered_map<OPTIONS, std::string> &options_map, std::string &filename, std::vector<std::string> &pattern_tokens, std::vector<std::string> &data)
{
    data = read_txt(filename);

    size_t s_line = 1, e_line = data.size() - 1;
    std::string search_pattern = ".*";
    if (options_map.find(LINE_NUM) != options_map.end())
    {
        std::cout << "Line options:" << std::endl;
        std::cout << options_map[LINE_NUM] << std::endl;

        if (options_map[LINE_NUM][0] == '/')
        {
            std::string curr;
            for (char c : options_map[LINE_NUM])
            {
                if (c == '/')
                {
                    search_pattern = curr;
                    curr.clear();
                    continue;
                }
                curr += c;
            }
            if (curr == "p")
            {
            }
        }
        else
        {
            std::string curr;
            for (char c : options_map[LINE_NUM])
            {
                if (c == ',')
                {
                    s_line = std::stoi(curr);
                    curr.clear();
                }
                else if (c <= '9' && c >= '0')
                {
                    curr += c;
                }
            }
            e_line = std::stoi(curr);
        }
    }

    filterData(data, s_line, e_line, search_pattern);

    if (pattern_tokens.size() && pattern_tokens[0] == "s")
    {
        substitute(data, pattern_tokens[1], pattern_tokens[2], pattern_tokens.size() > 3 && pattern_tokens[3] == "g");
    }
}

void print_output(std::vector<std::string> &data)
{
    for (size_t i = 0; i < data.size(); ++i)
    {
        std::cout << data[i] << std::endl;
    }
}

int main(int argc, char *argv[])
{
    std::string filename;
    std::unordered_map<OPTIONS, std::string> options_map;
    std::vector<std::string> pattern_tokens, data;
    // std::vector<bool> relavant_data;

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

    if (options_map.find(IN_PLACE) != options_map.end())
    {
        std::cout << "in place !!!" << std::endl;
        write_txt(filename, data);
    }
    else
    {
        print_output(data);
    }

    return 0;
}