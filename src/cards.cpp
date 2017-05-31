#include "cards.h"
#include "json/json.h"
#include "json/value.h"
#include <array>
#include <fstream>
#include <string>
#include <SFML/Graphics/Glyph.hpp>
#include <SFML/Graphics/Text.hpp>

namespace cards 
{
typedef void(CardSprite::*jsonApply)(Json::Value);
    
    
    Json::Value getJSON(std::string filename)
    {
        std::fstream fs (filename, std::fstream::in | std::fstream::out);
        Json::Value cardJSON;
        fs >> cardJSON;
        return cardJSON;
        
    }
    
    CardSprite::~CardSprite()
    {
        if (this->textfields)
        {
            delete [] textfields;
            this->textfields = NULL;
        }
        if (this->imgfields)
        {
            delete [] imgfields;
            this->textfields = NULL;
        }
        if (this->imgfieldtextures)
        {
            delete [] imgfields;
            this->imgfieldtextures = NULL;
        }
    }
    
    std::array<sf::Font*, 3> fontarray = {{&textfont, &titlefont, &numberfont}};
    void CardSprite::countStats(Json::Value stats)
    {
        for (int i = 0; i < constants::nr_stats; i++)    
            if (stats.isMember(constants::stats[i]))
            {
                this->nr_children[0]++;
                this->nr_children[1]++;
                this->which_fields |= (1 << i);
            }
    }
    void CardSprite::drawStats(Json::Value stats)
    {
        for (int i = 0; i < constants::nr_stats; i++)
            
        
        
    }
    void CardSprite::countCardTextFields(Json::Value cardtextfields)
    {
        for (int i = 0; i < constants::nr_cardtextfields; i++)
            if (cardtextfields.isMember(constants::cardtextfields[i]))
            {
                this->nr_children[textfields_index]++;
                this->which_fields |= 1 << (constants::nr_stats + i);
            }

    }
    void CardSprite::findZone(Json::Value zonevalue)
    {
        std::string zone_str = zonevalue.asString();
        for (int i = 0; i < constants::nr_zones ; i++)
            if (zone_str == constants::zones[i])
            {
                this->zone = i;
                return;
            }
    }
    
    CardSprite::CardSprite(Json::Value cardJSON)
    {
        const int nr_attr = 3;
        std::string attr_to_check[nr_attr] = {"stats", "cardtextfields", "zone"};
        jsonApply attr_function[nr_attr] = { CardSprite::countStats, CardSprite::countCardTextFields, CardSprite::findZone};
        for (int i = 0; i < nr_attr; i++)
        {   
            std::string attr = attr_to_check[i];
            if (cardJSON.isMember(attr))
                (this->*attr_function[i])(cardJSON[attr]);
        }
            
            

        
        }
    }
    
    
    template <typename T>
    void CardSprite::move(sf::Vector2<T> sfvector)
    {
        sf::Transformable* transformables;
        for (int trans_array = 0; trans_array < NRCHILDREN_ARRAYS; trans_array++)
        {
            transformables = transformable_arrays[trans_array];
            for (int i = 0; i < nr_children[trans_array]; i++)
                transformables[i].move(sfvector);
        }
        origin += sfvector;
    }
    
    template <typename T>
    void CardSprite::move(T xoffset, T yoffset)
    {
        sf::Transformable* transformables;
        for (int trans_array = 0; trans_array < NRCHILDREN_ARRAYS; trans_array++)
        {
            transformables = transformable_arrays[trans_array];
            for (int i = 0; i < nr_children[trans_array]; i++)
                transformables[i].move(xoffset, yoffset);
        }
        origin += sf::Vector2<T>(xoffset, yoffset);
    }
    
    template <typename T>
    void CardSprite::setPosition(sf::Vector2<T> sfvector)
    {
        sf::Vector2f diff = sfvector - origin;
        this->move(diff);
    }

    
    
    void initialize()
    {
        for (sf::Font* f : fontarray)
            f->loadFromFile("/usr/share/fonts/truetype/liberation/LiberationMono-Bold.ttf");
        
    }
    
}

