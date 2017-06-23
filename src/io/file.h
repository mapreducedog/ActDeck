#ifndef FILE_HEADER
#define FILE_HEADER
#include "src/json/json.h"
#include "src/json/value.h"



namespace io
{
namespace file
{
    Json::Value getJSON(std::string filename);
}
}
#endif
