/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_PV_RESOURCES_H
#define SSTAR_PV_RESOURCES_H

/*---------------------------------------------------------------------------*/

#include <memory>

/*---------------------------------------------------------------------------*/

class PVSharedResources;
class PVSpecificResources;

/**
 * Class which encapsulated the PV resources
 */
class PVResources
{

public:

   /**
    * Constructor
    *
    * @param pSharedResources Smart-Pointer to the shared resources
    */
   PVResources(const std::shared_ptr<PVSharedResources>& pSharedResources);

   /**
    * Destructor
    */
   ~PVResources();

   /**
    * Get the shared resources
    *
    * @return PV Shared Resources
    */
   const std::shared_ptr<PVSharedResources>& getSharedResources();

   /**
    * Get the specific resources
    *
    * @return PV Specific Resources
    */
   const std::shared_ptr<PVSpecificResources>& getSpecificResources();

private:

   /**
    * Shared Resources
    */
   std::shared_ptr<PVSharedResources> m_pSharedResources;

   /**
    * Specific Resources
    */
   std::shared_ptr<PVSpecificResources> m_pSpecificResources;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
