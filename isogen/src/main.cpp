#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <utility>

#include "defs.h"
#include "generator.h"
#include "helper.h"
#include "fat16/fat16.h"

#include "byte8/byte8.h"

using namespace std;

auto show_help()->void;
auto parse_args(int argc, const char* args[])->normArgs;
auto pair_args(normArgs args)->pairedArgs;
auto gen_info(ISOinfo& iso, pairedArgs args)->void;
auto check_info(const ISOinfo* const iso)->void;

int main(int argc, const char* args[]) {
	// Check if commands are passed.
    if (argc <= 1) {
        std::cout << "Usage: isogen --help or -h\n";
        exit(1);
    }
	
    ISOinfo ISO;
    auto p_args = normArgs{parse_args(argc, args)};
    auto paired_args = pairedArgs{pair_args(p_args)};
	gen_info(ISO, paired_args);
	check_info(&ISO);
	generate_iso(ISO);
    cout << "ISO generated successfully.\n";
    
    return 0;
}

auto parse_args(int argc, const char* args[])->normArgs {
    normArgs res;
    args++;
    for (int i = 0; i < argc-1; i++)
        res.push_back(*(args++));
    return res;
}

auto pair_args(normArgs args)->pairedArgs {
    pairedArgs result;
    
    for (auto arg : args)
        if (result.empty()) // first arguments, add to result.
            result.push_back(make_pair(arg, vector<string>()));
        else if (arg[0] == '-')  // its an argument.
      result.push_back(make_pair(arg, vector<string>()));
        else  if(arg[0] != '-') // it's an argument's param, not an arg.
            result[result.size()-1].second.push_back(arg);
    return result;
}

auto gen_info(ISOinfo& info, pairedArgs args)->void {
    for (auto arg : args) {
        // Check if argument is valid.
        if (mappedArgs.find(arg.first) == end(mappedArgs)) {
            cout << "Unrecognized argument: " << arg.first << "\n";
            exit(1);
        }

        auto argument = mappedArgs[arg.first]; // string, int
        auto argument_params = vector<string>{arg.second};
        switch (argument) {
        case CMDArgs::FS : {            

            // Check for filesystem argument params.
            if (argument_params.empty()) {
                cout << "Can't have unspecified filesystem.\n";
                exit(1);
            }
            if (argument_params.size() > 1) {
                cout << "Can't have more than one filesystem specified.\n";
                exit(1);
            }

            // Check for filesystem id.
            if (mappedFileSysNames.find(argument_params[0]) == end(mappedFileSysNames)) {
                cout << "Unrecognized FileSystem specified: " << argument_params[0] << "\n";
                exit(1);
            }
            
            auto filesystem_id =int{mappedFileSysNames[argument_params[0]]};
            info._fs = static_cast<FileSystems>(filesystem_id);
            break;
}
        case CMDArgs::BT0_LOC: {
            // Check for boot0 location argument params.
            if (argument_params.empty()) {
                cout << "Can't have unspecified boot0 location.\n";
                exit(1);
            }
            if (argument_params.size() > 1) {
                cout << "Can't have more than one boot0 location.\n";
                exit(1);
            }

            info._boot0_loc = argument_params[0];
            break;
        }
        case CMDArgs::BT1_LOC: {
            // Check for boot1 location argument params.
            if (argument_params.empty()) {
                cout << "Can't have unspecfied boot1 location.\n";
                exit(1);
            }
            if (argument_params.size() > 1) {
                cout << "Can't have more than one boot1 location.\n";
                exit(1);
            }

            info._boot1_loc = argument_params[0];
            break;
        }
        case CMDArgs::ISODIR_LOC: {
            // Check for iso directory lcoation argument params.
            if (argument_params.empty()) {
                cout << "Can't have unspefied isodir location.\n";
                exit(1);
            }
            if (argument_params.size() > 1) {
                cout << "Can't have more than one isodir location.\n";
                exit(1);
            }

            info._dir_loc = argument_params[0];
            break;
        }
        case CMDArgs::OUTPUT_LOC: {
            // Check for output argument params.
            if (argument_params.empty()) {
                cout << "Can't have unspecified output location.\n";
                exit(1);
            }
            if (argument_params.size() > 1) {
                cout << "Can't have more than one output location.\n";
                exit(1);
            }

            info._output_loc = argument_params[0];
            break;
            }
        case CMDArgs::ISO_SIZE: {
            // Check for size arguemnt params.
            if (argument_params.empty()) {
                cout << "Can't have unspecified size.\n";
                exit(1);
            }
            if (argument_params.size() > 1) {
                cout << "Can't have more than one size.\n";
                exit(1);
            }

            if (atoi(argument_params[0].c_str()) <= 0) {
                cout << "Size must be greater than zero.\n";
                exit(1);
            }

            info._buffSize = atoi(argument_params[0].c_str());
            break;
        }
        };
    }
}

auto check_info(const ISOinfo* const info)->void {
    bool err = false;
    if (info->_fs == -1) {
        cout << "File system must be specified.\n";
        err = true;
    }
    if (info->_boot0_loc == "") {
        cout << "Boot0 location must be specified.\n";
        err = true;
    }
    if (info->_boot1_loc == "") {
        cout << "Boot1 location must be specified.\n";
        err = true;
    }
    if (info->_output_loc == "") {
        cout << "ISO output location must be specified.\n";
        err = true;
    }
    if (info->_buffSize == 0) {
        cout << "ISO Size must be specied.\n";
        err = true;
    }

    if (err) {
        cout << "Try isogen --help or -h for help.\n";
        exit(1);
    }
}
