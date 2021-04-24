
/*-----------------------------------------------------------------------------
 * Copyright (c) 2015, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef TXM_SCAN_IFCONDITIONAL_COMMAND_H
#define TXM_SCAN_IFCONDITIONAL_COMMAND_H

/*---------------------------------------------------------------------------*/

#include <scan/ScanCommand.h>
#include <utils/ScanExceptions.h>
#include <utils/ChannelAccessExceptions.h>
#include <memory>
#include <thread>
#include <scan/Scan.h>

/*---------------------------------------------------------------------------*/



//template <class T>
class ScanIfConditionalCommand : public ScanCommand
{

public:

   enum boolean_operator{BOP_NOT_SET,
                         BOP_EQUAL,
                         BOP_NOT_EQUAL,
                         BOP_LESS_THAN,
                         BOP_LESS_EQUAL,
                         BOP_GREATER_THAN,
                         BOP_GREATER_EQUAL};

   /**
    * Default constructor
    */
   ScanIfConditionalCommand();

   /**
    * Copy constructor
    */
   ScanIfConditionalCommand(const std::shared_ptr<ScanIfConditionalCommand>& cmd);

   /**
    * @brief operator =
    * @param rhs
    * @return
    */
   ScanIfConditionalCommand& operator=(
      const std::shared_ptr<ScanIfConditionalCommand>& rhs);

   /**
    * Default destructor
    */
   ~ScanIfConditionalCommand();

   /**
    * set a ScanCommand if condition is true
    *
    * @param command - A ScanCommand
   */
   void setTrueCommand(const std::shared_ptr<ScanCommand>& command);

   /**
    * @brief set scan command for false
    * @param command
    */
   void setFalseCommand(const std::shared_ptr<ScanCommand>& command);

   /**
    * @brief dump
    * @param level
    */
   void dump(int level);

   /**
    * @brief execute
    */
   void execute();

   /**
    * @brief reset
    */
   void reset();

   void setCompValsStr(const char* lhs_e, const char* rhs_e, boolean_operator op);

   void setCompValsInt(int lhs_e, int rhs_e, boolean_operator op);

   void setCompValsFloat(float lhs_e, float rhs_e, boolean_operator op);

   void setCompValsLong(int lhs_e, int rhs_e, boolean_operator op);

   void setCompValsDouble(int lhs_e, int rhs_e, boolean_operator op);

private:
   
   bool comp_int();

   bool comp_long();

   bool comp_float();

   bool comp_double();

   bool comp_string();

   enum compare_type {INT, FLOAT, STRING, LONG, DOUBLE};

   compare_type compr_type;

   char* lhsS, *rhsS;

   long lhsL, rhsL;

   int lhsI, rhsI;

   float lhsF, rhsF;

   double lhsD, rhsD;

   boolean_operator bool_op;

   /**
    * @brief m_trueCommand
    */
   std::shared_ptr<ScanCommand> m_trueCommand;

   /**
    * @brief m_falseCommand
    */
   std::shared_ptr<ScanCommand> m_falseCommand;

};


/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
