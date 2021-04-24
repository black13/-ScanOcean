/*-----------------------------------------------------------------------------
 * Copyright (c) 2015, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <scan/ScanIfConditionalCommand.h>
#include <utils/ScanExceptions.h>
#include <utils/ChannelAccessExceptions.h>

#include <cstring>
#include <thread>

using namespace std;

/*---------------------------------------------------------------------------*/

ScanIfConditionalCommand::ScanIfConditionalCommand()
:  ScanCommand()
{

   bool_op = BOP_NOT_SET;
   lhsS = NULL;
   rhsS = NULL;

}



ScanIfConditionalCommand::ScanIfConditionalCommand(const std::shared_ptr<ScanIfConditionalCommand>& cmd)
{

   m_trueCommand = cmd->m_trueCommand;
   m_falseCommand = cmd->m_falseCommand;
   bool_op = cmd->bool_op;

}


ScanIfConditionalCommand& ScanIfConditionalCommand::operator=(
   const std::shared_ptr<ScanIfConditionalCommand>& rhs)
{

   m_trueCommand = rhs->m_trueCommand;
   m_falseCommand = rhs->m_falseCommand;
   bool_op = rhs->bool_op;
   return *this;

}


ScanIfConditionalCommand::~ScanIfConditionalCommand()
{

   if (lhsS != NULL)
      delete lhsS;
   lhsS = NULL;
   if (rhsS != NULL)
      delete rhsS;
   rhsS = NULL;

}



void ScanIfConditionalCommand::setFalseCommand(const std::shared_ptr<ScanCommand>& command)
{

   m_falseCommand = command;

}



void ScanIfConditionalCommand::setTrueCommand(const std::shared_ptr<ScanCommand>& command)
{

   m_trueCommand = command;

}

void ScanIfConditionalCommand::setCompValsStr(const char* lhs_e, const char* rhs_e, boolean_operator op)
{

   int llen = std::strlen(lhs_e) + 1;
   lhsS = new char(llen);
   std::strncpy(lhsS, lhs_e, llen-1);
   lhsS[llen-1] = '\0';

   int rlen = strlen(rhs_e) + 1;
   rhsS = new char(rlen);
   strncpy(rhsS, rhs_e, rlen-1);
   rhsS[rlen-1] = '\0';

   bool_op = op;
   compr_type = STRING;
}

void ScanIfConditionalCommand::setCompValsInt(int lhs_e, int rhs_e, boolean_operator op)
{
   lhsI = lhs_e;
   rhsI = rhs_e;
   bool_op = op;
   compr_type = INT;
}

void ScanIfConditionalCommand::setCompValsFloat(float lhs_e, float rhs_e, boolean_operator op)
{
   lhsF = lhs_e;
   rhsF = rhs_e;
   bool_op = op;
   compr_type = FLOAT;
}

void ScanIfConditionalCommand::setCompValsLong(int lhs_e, int rhs_e, boolean_operator op)
{
   lhsL = lhs_e;
   rhsL = rhs_e;
   bool_op = op;
   compr_type = LONG;
}

void ScanIfConditionalCommand::setCompValsDouble(int lhs_e, int rhs_e, boolean_operator op)
{
   lhsD = lhs_e;
   rhsD = rhs_e;
   bool_op = op;
   compr_type = DOUBLE;
}



void ScanIfConditionalCommand::dump(int level)
{

   m_trueCommand->dump(level);
   m_falseCommand->dump(level);

}




void ScanIfConditionalCommand::reset()
{

   Scan::reset();

   m_trueCommand->reset();
   m_falseCommand->reset();

}

void ScanIfConditionalCommand::execute()
{

   bool result = false;
   try
   {

      switch(compr_type)
      {
         case INT:
            result = comp_int();
         break;
         case LONG:
            result = comp_long();
         break;
         case FLOAT:
            result = comp_float();
         break;
         case DOUBLE:
            result = comp_double();
         break;
         case STRING:
            result = comp_string();
         break;
         default:
         break;
      }

      //perform test, if true call trueMacro, else call falseMacro
      if(result)
         m_trueCommand->execute();
      else
         m_falseCommand->execute();

   }
   catch (ScanAbortException& se)
   {
      std::cout<<"Scan aborted"<<std::endl;
      if(result)
         m_trueCommand->dump(0);
      else
         m_falseCommand->dump(0);
      throw;
   }
   catch (ChannelAccessException& ce)
   {
      std::cout<<"Scan failed with channel-access exception"<<std::endl;
      if(result)
         m_trueCommand->dump(0);
      else
         m_falseCommand->dump(0);
      throw;
   }
   catch (std::exception const& i)
   {
      std::cout<<"Scan interuppted"<<std::endl;
      if(result)
         m_trueCommand->dump(0);
      else
         m_falseCommand->dump(0);
      Scan::stop();
      throw ScanAbortException();
   }
}

bool ScanIfConditionalCommand::comp_int()
{
   switch (bool_op)
   {
   case BOP_EQUAL:
      if(lhsI == rhsI)
         return true;
      break;
   case BOP_NOT_EQUAL:
      if(lhsI != rhsI)
         return true;
      break;
   case BOP_LESS_THAN:
      if(lhsI < rhsI)
         return true;
      break;
   case BOP_LESS_EQUAL:
      if(lhsI <= rhsI)
         return true;
      break;
   case BOP_GREATER_THAN:
      if(lhsI > rhsI)
         return true;
      break;
   case BOP_GREATER_EQUAL:
      if(lhsI >= rhsI)
         return true;
      break;
   default:
      break;
   }
   return false;
}

bool ScanIfConditionalCommand::comp_long()
{
   switch (bool_op)
   {
   case BOP_EQUAL:
      if(lhsL == rhsL)
         return true;
      break;
   case BOP_NOT_EQUAL:
      if(lhsL != rhsL)
         return true;
      break;
   case BOP_LESS_THAN:
      if(lhsL < rhsL)
         return true;
      break;
   case BOP_LESS_EQUAL:
      if(lhsL <= rhsL)
         return true;
      break;
   case BOP_GREATER_THAN:
      if(lhsL > rhsL)
         return true;
      break;
   case BOP_GREATER_EQUAL:
      if(lhsL >= rhsL)
         return true;
      break;
   default:
      break;
   }
   return false;
}

bool ScanIfConditionalCommand::comp_float()
{
   switch (bool_op)
   {
   case BOP_EQUAL:
      if(lhsF == rhsF)
         return true;
      break;
   case BOP_NOT_EQUAL:
      if(lhsF != rhsF)
         return true;
      break;
   case BOP_LESS_THAN:
      if(lhsF < rhsF)
         return true;
      break;
   case BOP_LESS_EQUAL:
      if(lhsF <= rhsF)
         return true;
      break;
   case BOP_GREATER_THAN:
      if(lhsF > rhsF)
         return true;
      break;
   case BOP_GREATER_EQUAL:
      if(lhsF >= rhsF)
         return true;
      break;
   default:
      break;
   }
   return false;
}

bool ScanIfConditionalCommand::comp_double()
{
   switch (bool_op)
   {
   case BOP_EQUAL:
      if(lhsD == rhsD)
         return true;
      break;
   case BOP_NOT_EQUAL:
      if(lhsD != rhsD)
         return true;
      break;
   case BOP_LESS_THAN:
      if(lhsD < rhsD)
         return true;
      break;
   case BOP_LESS_EQUAL:
      if(lhsD <= rhsD)
         return true;
      break;
   case BOP_GREATER_THAN:
      if(lhsD > rhsD)
         return true;
      break;
   case BOP_GREATER_EQUAL:
      if(lhsD >= rhsD)
         return true;
      break;
   default:
      break;
   }
   return false;
}

bool ScanIfConditionalCommand::comp_string()
{
   int val = strcmp(lhsS, rhsS);

   switch (bool_op)
   {
   case BOP_EQUAL:
      if(val == 0)
         return true;
      break;
   case BOP_NOT_EQUAL:
      if(val != 0)
         return true;
      break;
   case BOP_LESS_THAN:
      break;
   case BOP_LESS_EQUAL:
      break;
   case BOP_GREATER_THAN:
      break;
   case BOP_GREATER_EQUAL:
      break;
   default:
      break;
   }
   return false;
}

/*---------------------------------------------------------------------------*/
