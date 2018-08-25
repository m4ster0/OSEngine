#include "OSE/Graphics/ResourceID.h"

namespace OSE {

    ResourceID ResourceID::Invalid;

    ResourceID::ResourceID(size_t id) :
        m_ID{ id }
    {

    }

    ResourceID::ResourceID():
        ResourceID{ 0 }
    {

    }

    bool ResourceID::operator==(const ResourceID& other) const
    {
        return m_ID == other.m_ID;
    }

    bool ResourceID::operator!=(const ResourceID& other) const
    {
        return !(*this == other);
    }
}