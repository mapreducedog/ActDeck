#include "cards.h"
#include "src/system/constants.h"
#include "src/json/json.h"
#include "src/json/value.h"
#include "src/io/file.h"
#include <array>
#include <fstream>
#include <string>
#include <SFML/Graphics/Glyph.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include <SFML/System/Vector2.hpp>

#define default_pos sf::Vector2f(60,500)
namespace visual
{
namespace cards 
{
    std::array<sf::Font, 3> fontarray;
    typedef void(CardSprite::*jsonApply)(Json::Value);
    

    sf::Vector2f CardSprite::getPosition()
    {
        return this->origin;
        
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
    void CardSprite::attachStats(Json::Value stats)
    {
        const int len_x_pos = 3;
        int x_pos[] = {-50, 0, 50};
        int cur_pos = 0;
        for (int i = 0; i < constants::nr_stats; i++)
            if (stats.isMember(constants::stats[i]))
            {
                
                if(!this->imgfieldtextures[cur_pos].loadFromFile("../data/gun.png"))
                    std::cout << "Error loading file!" << std::endl;//change this later to reflect on actual stat
                this->imgfields[cur_pos].setTexture(this->imgfieldtextures[cur_pos]);
                this->imgfields[cur_pos].setPosition(this->origin + sf::Vector2f(x_pos[cur_pos % len_x_pos], 50));
                this->textfields[cur_pos].setFont(fontarray[imgfields_index]); //as well as this
                this->textfields[cur_pos].setCharacterSize(24);
                this->textfields[cur_pos].setColor(sf::Color::White);
                this->textfields[cur_pos].setString(stats[constants::stats[i]].asString()); //as well as this
                this->textfields[cur_pos].setPosition(this->origin + sf::Vector2f(x_pos[cur_pos % len_x_pos], 50));
                cur_pos++;
            };
            
    }
    
    void CardSprite::attachCardTextFields(Json::Value cardtextfields)
    {
        const int len_x_pos = 3;
        int x_pos[] = {-50, 0, 50};
        int cur_pos = this->nr_children[imgfields_index];
        int start_pos = cur_pos;
        for (int i = 0; i < constants::nr_cardtextfields; i++)
            if (cardtextfields.isMember(constants::cardtextfields[i]))
            {
                this->textfields[cur_pos].setFont(fontarray[textfields_index]);
                this->textfields[cur_pos].setString(cardtextfields[constants::cardtextfields[i]].asString());
                this->textfields[cur_pos].setCharacterSize(24);
                this->textfields[cur_pos].setColor(sf::Color::Black);
                this->textfields[cur_pos].setPosition(this->origin + sf::Vector2f(x_pos[cur_pos % len_x_pos], -50 + (cur_pos - start_pos)*10 ));
                cur_pos++;
            }
        
    }
    
    sf::Text create_text()
    {
        sf::Text textobj;
        textobj.setFont(fontarray[textfields_index]);
        textobj.setString("HIIIIIII!!!!");
        textobj.setCharacterSize(24);
        textobj.setColor(sf::Color::Black);
        textobj.setPosition(default_pos);
        return textobj;
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
    void CardSprite::attachZone(Json::Value cardJson)
    {
        1;
    }
    
    CardSprite::CardSprite(Json::Value cardJSON)
    {
        this->origin = default_pos;
        const int nr_attr = 3;
        std::string attr_to_check[nr_attr] = {"stats", "cardtextfields", "zone"};
        jsonApply attr_function[nr_attr] = { &CardSprite::countStats, &CardSprite::countCardTextFields, &CardSprite::findZone};
        for (int i = 0; i < nr_attr; i++)
        {   
            std::string attr = attr_to_check[i];
            if (cardJSON.isMember(attr))
                (this->*attr_function[i])(cardJSON[attr]);
        }
        this->textfields = new sf::Text[this->nr_children[textfields_index]];
        this->imgfields = new sf::Sprite[this->nr_children[imgfields_index]];
        this->imgfieldtextures = new sf::Texture[this->nr_children[imgfields_index]];
        jsonApply attr_attach_function[nr_attr] = {&CardSprite::attachStats, &CardSprite::attachCardTextFields, &CardSprite::attachZone}; //add zone
        for (int i = 0; i < nr_attr ; i++)
            {   
            std::string attr = attr_to_check[i];
            if (cardJSON.isMember(attr))
                (this->*attr_attach_function[i])(cardJSON[attr]);
            }   
    }
    
    //we define the following four template functions as inline, so that the references are defined in cards.h
    /*
    template <typename T>
    inline void CardSprite::move(sf::Vector2<T> sfvector)
    {
        sf::Transformable* transformables;
        for (int trans_array = 0; trans_array < NRCHILDREN_ARRAYS; trans_array++)
        {
            transformables = *transformable_arrays[trans_array];
            for (int i = 0; i < nr_children[trans_array]; i++)
                transformables[i].move(sfvector);
        }
        origin += sfvector;
    }
    */
    void CardSprite::move(sf::Vector2f sfvector)
    {
        sf::Transformable* transformables;
        for (int trans_array = 0; trans_array < NRCHILDREN_ARRAYS; trans_array++)
        {
            transformables = *transformable_arrays[trans_array];
            for (int i = 0; i < nr_children[trans_array]; i++)
                transformables[i].move(sfvector);
        }
        origin += sfvector;
    }
    
    void CardSprite::move(float xoffset, float yoffset)
    {
        this->move(sf::Vector2f(xoffset,yoffset));
    }
    void CardSprite::setPosition(sf::Vector2f sfvector)
    {
        sf::Vector2f diff = sfvector - origin;
        this->move(diff);
    }

    void CardSprite::setPosition(float x, float y)
    {
        this->setPosition(sf::Vector2f(x, y));
    }

    
    /*
    template <typename T>
    inline void CardSprite::setPosition(sf::Vector2<T> sfvector)
    {
        sf::Vector2f diff = sfvector - origin;
        this->move(diff);
    }
    
    template <typename T>
    inline void CardSprite::setPosition(T x, T y)
    {
        this->setPosition(sf::Vector2<T>(x,y));
    }

    */
    
    
    void CardSprite::draw(sf::RenderTarget& target)
    {
        /*for (int type_field = 0; type_field < NRCHILDREN_ARRAYS; type_field++)
            for (int i = 1; i < this->nr_children[type_field]; i++)
                target.draw(this->drawable_arrays[type_field][i]);
        */
        for (int i = 0; i < this->nr_children[imgfields_index];i++)
            target.draw(this->imgfields[i]);
        for (int i = 0; i < this->nr_children[textfields_index];i++)
            target.draw(this->textfields[i]);
    }

    void initialize()
    {
        //for (int i = 0; i < fontarray.size(); i++)
        //    fontarray[i] = sf::Font;
        
        for (int i = 0; i < fontarray.size(); i++)
            if(!fontarray[i].loadFromFile("/usr/share/fonts/truetype/liberation/LiberationMono-Bold.ttf"))
                std::cout << "Error loading font!" << std::endl;
        
    }
    void cleanup()
    {
        /*for (int i = 0; i < fontarray.size(); i++)
        {
            delete fontarray[i];
            fontarray[i] = NULL;
        }*/
    }
    
}
}


