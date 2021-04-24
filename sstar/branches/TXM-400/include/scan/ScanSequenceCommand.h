
/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef TXM_SCAN_SEQUENCE_COMMAND_H
#define TXM_SCAN_SEQUENCE_COMMAND_H

/*---------------------------------------------------------------------------*/

#include <scan/ScanCommand.h>
#include <scan/Command.h>

#include <boost/shared_ptr.hpp>

#include <string>
#include <vector>

/*---------------------------------------------------------------------------*/

/**
 * Represents a group of scan commands. These commands get executed using Scan
 *  object in the order in which they were added to this object.
 *
 * Example 1.
 *   ScanSequenceCommand seq;
 *   // Move the motor 1 to 100 and wait for the call-back
 *   seq.addCommand("ioc.m1.VAL", 100, Command::PV_PUT_SYNC);
 *   // Set the camera to acquire and not wait for any call-back
 *   seq.addCommand("ioc.cam1.acquire", 1, Command::PV_PUT_ASYNC);
 *   // Wait for the camera to stop acquisition
 *   seq.addCommand("ioc.cam1.acquire", 0, Command::PV_WAIT);
 *
 *   // move the motor, set the camera to acquire and wait for the 
 *   // acquisition to stop. 
 *   seq.execute();
 */
class ScanSequenceCommand
: public ScanCommand
{
public:

   /**
    * Default constructor
    */
   ScanSequenceCommand();

   /**
    * Copy constructor
    */
   ScanSequenceCommand(const boost::shared_ptr<ScanSequenceCommand>& rhs);

   /**
    * Assignment operator
    */
   ScanSequenceCommand& operator=(
      const boost::shared_ptr<ScanSequenceCommand>& rhs);

   /**
    * Destructor
    */
   ~ScanSequenceCommand();
   /**
    * Add a PV command for integer PV types
    *
    * @param pvName - Name of the PV
    * @param data - Integer value to use during the specific operation
    * @param op - One of the supported operations. See Command::Operation
    */
    void addCommand(const std::string& pvName, int data, Command::Operation op);
  
    /**
    * Add a PV command for unsigned integer PV types
    *
    * @param pvName - Name of the PV
    * @param data - Unsigned Integer value to use during the specific operation
    * @param op - One of the supported operations. See Command::Operation
    */
   void addCommand(const std::string& pvName, 
                   unsigned int data, 
                   Command::Operation op);
   
    /**
    * Add a PV command for double PV types
    *
    * @param pvName - Name of the PV
    * @param data - double value to use during the specific operation
    * @param op - One of the supported operations. See Command::Operation
    */
   void addCommand(const std::string& pvName, 
                   double data, 
                   Command::Operation op);

    /**
    * Add a PV command for string PV types
    *
    * @param pvName - Name of the PV
    * @param data - string value to use during the specific operation
    * @param op - One of the supported operations. See Command::Operation
    */
   void addCommand(const std::string& pvName, 
                   const std::string& data, 
                   Command::Operation op);


   /**
    * Print the sequence of commands in this command on std out.
    *
    * @param level - The amount of indentation to use. 
    */
   void dump(int level);

   /**
    * Execute the scan using Scan object.
    */
   void execute();

private:
   
   // The command list
   std::vector<Command> m_commandList;

};

#endif
