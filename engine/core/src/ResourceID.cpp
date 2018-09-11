#include "OSE/Graphics/ResourceID.h"

namespace OSE {

    ResourceID ResourceID::Invalid;

    ResourceID::ResourceID(size_t id, ResourceType type) :
        m_ID{ id }, m_Type{ type }
    {

    }

    ResourceID::ResourceID():
        ResourceID{ 0, ResourceType::None }
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