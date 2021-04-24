
/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef TXM_SCAN_MACRO_COMMAND_H
#define TXM_SCAN_MACRO_COMMAND_H

/*---------------------------------------------------------------------------*/

#include <scan/ScanCommand.h>

#include <boost/shared_ptr.hpp>

#include <vector>

/*---------------------------------------------------------------------------*/

/**
 * Use to group an arbitrary number of ScanCommand object. 
 *
 * Example:
 *
 *  ScanMacroCommand seq_1, seq_2;
 *  // Synchronously set motor PV to 100.0
 *  seq_1.addCommand("ioc:m1.VAL", 100.0, PV_PUT_SYNC);
 *  // Asynchronously trigger the camera
 *  seq_2.addCommand("ioc:cam1:Acquire", 1, PV_PUT_ASYNC);
 *  // Finally call the execute
 *
 *  ScanMacroCommand macro;
 *  macro.addCommand(seq_1);
 *  macro.addCommand(seq_2);
 *
 *  // Now execute both set of sequence commands together. 
 *  macro.execute();
 */

class ScanMacroCommand
: public ScanCommand
{

public:

   /**
    * Default constructor
    */
   ScanMacroCommand();

   /**
    * Copy constructor
    */
   ScanMacroCommand(const boost::shared_ptr<ScanMacroCommand>& cmd);

   ScanMacroCommand& operator=(
      const boost::shared_ptr<ScanMacroCommand>& rhs);

   /**
    * Default destructor
    */
   ~ScanMacroCommand();

   /**
    * Add a ScanCommand at the end of the existing list of commands, these
    * commands are executed in the order they were added to the macro.
    *
    * @param command - A ScanCommand
   */
   void addCommand(const boost::shared_ptr<ScanCommand>& command);

   void dump(int level);

   void execute();

private:
   
   /**
    * Store list of commands. 
    */
   std::vector<boost::shared_ptr<ScanCommand> > m_commandList;

};


/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
