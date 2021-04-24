
/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef TXM_SCAN_COMMAND_H
#define TXM_SCAN_COMMAND_H

/*---------------------------------------------------------------------------*/

#include <string>
#include <memory>

/*---------------------------------------------------------------------------*/

/**
 * An abstract base class for defining a Scan command. 
 *
 * The derived classes must implement execute method that invoke
 * action on external entity such as process variables or PVs.
 */
class ScanCommand 
{
public:
  
   ScanCommand();

   virtual ~ScanCommand();

   /*
    * Print sequence of commands. 
    * Useful for debugging purpose
    *
    * @param level - For nested level of commands, this variable must
    *                should represent the level of this command. 
    */
   virtual void dump(int level=0) = 0;

   /**
    * Pure virtual method that must be overidden
    * by dervied comand. 
    *
    * This method handle execution of the operation on external entities such as 
    * process variables. 
    */
   virtual void execute() = 0;

   virtual void reset() = 0;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
