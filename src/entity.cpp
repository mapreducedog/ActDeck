#include "entity.h"

namespace entity {
    bool has_component(mask entity_mask, mask check_mask)
    {
        return (entity_mask & check_mask) == check_mask;
    }
    
    
}