/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef TXM_SCAN_H
#define TXM_SCAN_H

#include <SStar.h> 

#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

#include <map>

class CACallback;
class Command;

/*---------------------------------------------------------------------------*/

/**
 * It handles all the supported scan style operation on a single PV. The PV
 *
 */
class Scan
{

public:

   static Scan* getInstance();
   /**
    * Execute given command on the PV mentioned in the command
    *
    * @return The execution status, usually 0 is success and any other value
    *         corresponds to an error. In case of error, the client should stop
    *         sending further commands. 
    */

   ~Scan();

   void execute(const Command* cmd);

   /**
    * Clears all the flags sucsh as stop. If a stop was called anytime
    * during the life of this object, the reset should be called at-least
    * once to be able to run any further scans. 
    */
   static void reset();

   /**
    * Atomically set the stop flag on the currently running
    * operation on PV.
    *
    * The PV operations must run in a sequence i.e. at any time a single
    * execute method is running , however the thread
    * that set the flag need not to be the same as the thread running the
    * PVOperation. 
    */
   static void stop();

private:

   // A singleton constructor
   Scan();

   // Non Copyable
   Scan(const Scan&);

   // Non-copyable
   Scan& operator=(const Scan&);

   /**
    * Return a PV object, store the named object and returns the reference
    * to it next time. 
    */
   boost::shared_ptr<PV> getPV(const std::string& pvName);

   /**
    * Returns the pointer to appropriate value associated with the Command/PV.
    *
    * @param cmd - Command
    */
   void* getValue(const Command* cmd);

   /**
    * Wakes up the scan thread when a value changes for a 
    * requested PV.
    *
    * @param isSuccess - If the callback is result a successufl CA operation.
    */
   void onDataChange(bool isSuccess);

   /**
    * Wakes up the scan thread on the completion of 
    * async put. This method is used to do a synchronous
    * pv write with asynPut.
    *
    * @param isSuccess - If the callback is result a successufl CA operation.
    */
   void onReadComplete(bool isSuccess);

   void waitPVCallback(boost::shared_ptr<PV> pv, const Command* cmd);

   /**
    * Helper function to wait on a PV value to be set to the one
    * specified in Command.
    */
   void waitPVSet(boost::shared_ptr<PV> pv, const Command* cmd);

private:

   /**
    * Handle call-back from channel access
    */
   CACallback* m_dataChange;

   CACallback* m_readComplete;

   boost::mutex m_mutex;

   boost::condition_variable m_pvCallback;

   std::map<std::string, boost::shared_ptr<PV> > m_pvList;

   static Scan* s_pInstance;

   /**
    * Once this flag is set to ture, the PVOperation will stop
    * executing. This flag needs to be reset before
    *  TODO say more about use of volatile here
    */
   static volatile bool s_stopFlag;

   /**
    * Use by the Scan to store value associated with current operation
    */
   int m_valueI;
   unsigned int m_valueUI;
   double m_valueD;
   char* m_valueS;

   // Number of elements in our given data type. Usually used for string type pvs.
   int m_count;
 
};

#endif 
