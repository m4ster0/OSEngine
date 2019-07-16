#pragma once

namespace ose::memory { class IMemoryResource; }

namespace ose::memory {

    /**
     * Gets default memory resource
     * This function is not thread-safe
     * @return Pointer to default memory resource
     */
    IMemoryResource* getDefaultResource();

    /**
     * Sets default memory resource 
     * This function is not thread-safe
     * @param resource new default memory resource to be set
     * @return Previous default memory resource or current if resource is nullptr
    */
    IMemoryResource* setDefaultResource(IMemoryResource* resource);

}