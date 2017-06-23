#include "file.h"
#include "src/json/json.h"
#include <iostream>
#include <fstream>

namespace io {
namespace file {
    Json::Value getJSON(std::string filename)
    {
        std::fstream fs (filename, std::fstream::in | std::fstream::out);
        Json::Value cardJSON;
        fs >> cardJSON;
        return cardJSON;
    }
    }
}
