#pragma once

#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <string>

namespace OSE {

    struct Event
    {
        virtual ~Event() {  };
    };

}