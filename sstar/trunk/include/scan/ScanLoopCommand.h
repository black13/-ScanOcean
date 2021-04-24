/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef TXM_SCAN_LOOP_COMMAND_H
#define TXM_SCAN_LOOP_COMMAND_H

/*---------------------------------------------------------------------------*/

#include <scan/Command.h>
#include <scan/ScanCommand.h>
#include <scan/Loop.h>

#include <memory>

#include <vector>

/*---------------------------------------------------------------------------*/

/**
 * Changes a PV value in a loop and execute a sequence of scan commands in 
 *   each iteration.
 *
 * The currently supported data type for loop PV is double. The object
 * resets the Loop at the end of the scan. This feature is useful
 * when implementing nested loop. After each iteration of inner most
 * loop, the Loop is set to its initial value.
 *
 * Example 1:
 *  // TO move a motor PV go from 0 to 100 in step of 10
 *  Loop<double> loop(0.0, 10.0, 100);
 *  ScanLoopCommand loopCmd("ioc.m1.VAL", loop);
 *  loopCmd->execute();
 *
 * Examples 2:
 *  // If we also want to change another PV in each iteration of the loop
 *  // e.g acquire camera image and wait for the acquire to be done. 
 *  std::shared_ptr<ScanSequenceCommand> ptr(new ScanSequenceCommand());
 *  ptr->addCommand("acquire", 1, Command::PV_PUT_SYNC);
 *  ptr->addCommand("acquire", 0, Command::PV_WAIT);
 *
 *  loopCmd->addCommand(ptr);
 *  loopCmd->execute();
 */
class ScanLoopCommand
: public ScanCommand
{

public:

   /**
    * Construct a scan loop command with given PV and loop.
    *
    * @param pv - PV whose value to change based on the loop.
    * @param loop - Loop 
    */
   ScanLoopCommand(const std::string& pv, Loop<double> loop);

   /**
    * Construct a scan loop command with loop only. This mean 
    *  we do not set a pv to the value of the loop
    *
    * @param loop - Loop 
    */
   ScanLoopCommand(Loop<double> loop);

   /**
    * Copy constructor
    */
   ScanLoopCommand(const std::shared_ptr<ScanLoopCommand>& loop);

   /**
    * Assignment constructor
    */
   ScanLoopCommand& operator=(
      const std::shared_ptr<ScanLoopCommand>& command);

   /**
    * Destructor.
    */
   ~ScanLoopCommand();

   /**
    * Add a command to end of an existing list of commands to execute
    * in each iteration of loop.
    *
    * @param command - A command implementing Scan interface.
    */
   void addCommand(const std::shared_ptr<ScanCommand>& command);

   /**
    * Print the loop on standard output with 'level' number of indentation
    * spaces.
    *
    * @param level - Number of indentation spaces.
    */
   void dump(int level);

   /**
    * Execute the scan.
    *
    * The scan runs from the starting value of loop variable until the Loop's
    * hasNext() method returns false. In each iteration it sets the value of
    * the loop-pv (passed at construction time) based on the current value of the
    * Loop (see Loop getNext()). After setting the loop pv's value it goes through
    * the list of added command and execute them in the order in which those
    * commands were added.
    */
   void execute();

   void reset();

private:

   /**
   * if initialized with PV string or not
   */   
   bool m_hasPv;

   std::vector<std::shared_ptr<ScanCommand> > m_commandList;
  
   //PV operation that will run in a loop
   std::string m_loopPV;

   Loop<double> m_loopVariable;

};


/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
