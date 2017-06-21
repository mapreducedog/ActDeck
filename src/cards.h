#ifndef CARDS_HEADER
#define CARDS_HEADER
#define NRCHILDREN_ARRAYS 2

#include <string>
#include <array>
#include "json/json.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>



namespace cards {
    
    Json::Value getJSON(char* filename);
    enum children_array_index {
        textfields_index = 0,
        imgfields_index = 1,
    };

    class CardSprite {
    private:
        unsigned int id;
        unsigned int nr_children[NRCHILDREN_ARRAYS] = {0,0}; //nr_textfields, nr_imgfields
        unsigned int which_fields = 0;
        unsigned int zone = 0;
        sf::Vector2f origin;
            

        sf::Text* textfields = NULL; //also includes numeric fields, such as atk, def
        sf::Sprite* imgfields = NULL;
        sf::Texture* imgfieldtextures = NULL;
        sf::Transformable** transformable_arrays[NRCHILDREN_ARRAYS] = { (sf::Transformable**) &textfields, (sf::Transformable**) &imgfields}; //convenience for looping over text and imgfields for moving around
        sf::Drawable* drawable_arrays[NRCHILDREN_ARRAYS] =  { (sf::Drawable*) &textfields, (sf::Drawable*) &imgfields};
        void countCardTextFields(Json::Value cardtextfields);
        void countStats(Json::Value stats);
        void attachStats(Json::Value stats);
        void attachCardTextFields(Json::Value cardtextfields);
        void findZone(Json::Value zonevalue);
        void attachZone(Json::Value cardJson);


    public: 
        CardSprite(Json::Value cardJSON);
        ~CardSprite();
        void draw(sf::RenderTarget& target);
        /*
        template <typename T>
        void move(sf::Vector2<T> sfvector);
        template <typename T>
        void move(T xoffset, T yoffset);
        template <typename T>
        void setPosition(sf::Vector2<T> sfvector);
        template <typename T>
        void setPosition(T x, T y);
        */
        void move(sf::Vector2f sfvector);
        void move(float xoffset, float yoffset);
        void setPosition(sf::Vector2f sfvector);
        void setPosition(float x, float y);
        
        bool hasField(int type_field, std::string field_name);
        sf::Vector2f getPosition();
        //sf::Vector2f getPosition(int corner);
        
    };
    
    sf::Text create_text();
    
    namespace function {
        enum function {
        none = 0,
        create = 1,
        
        };
    }
    void initialize();
    void cleanup();
    Json::Value getJSON(std::string filename);

}
#endif
