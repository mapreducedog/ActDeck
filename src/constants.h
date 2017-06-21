#ifndef CONSTANTS_HEADER
#define CONSTANTS_HEADER
#include <string>
#include <array>

namespace constants { 

    enum zones_enum 
    {
        out = 0,
        hand,
        field,
        market,
        nr_zones,
    };
    std::array<std::string, nr_zones>  zones = {
    {"out",
    "hand",
    "field",
    "market" 
        
    }};

    enum cardtypes_enum 
    {
        troop,
        shot,
        influence,
        nr_cardtypes
    };
    
    std::array<std::string, nr_cardtypes> cardtypes = {
    {
        "troop",
        "shot",
        "influence"
    }};
    enum stats_enum 
    {
        atk,
        tim,
        def,
        spc,
        nr_stats
    };
    
     std::array<std::string, nr_stats> stats = {
    {
        "atk",
        "tim",
        "def",
        "spc"
    }};
    enum cardtextfields_enum
    {
        cardname,
        cardtext,
        flavortext,
        nr_cardtextfields
    };
    std::array<std::string, nr_cardtextfields> cardtextfields = {
    {
        "cardname",
        "cardtext",
        "flavortext"
    }};
    
}
#endif
