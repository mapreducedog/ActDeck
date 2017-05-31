#ifndef ENTITY_HEADER
#define ENTITY_HEADER
typedef unsigned int id;
typedef unsigned int mask;
namespace entity{
    namespace attribute {
        enum attribute {
            none = 0,
            hp = 1 << 0,
            atk = 1 << 1,
            time = 1 << 2,
            card = 1 << 3,
            controller = 1 << 4,
            position = 1 << 5,
        };       
    }
    bool has_component(mask entity_mask, mask check_mask);
    
}


#endif