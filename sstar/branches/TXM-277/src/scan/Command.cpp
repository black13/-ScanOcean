/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <scan/Command.h>

#include <iostream>

using namespace std;


/*---------------------------------------------------------------------------*/

Command::Command(const std::string& pv, int value, Operation op)
{

   init(pv, op, SSTAR_INT, value, 0, 0.0, "");

}

/*---------------------------------------------------------------------------*/

Command::Command(const std::string& pv, unsigned int value, Operation op)
{

   init(pv, op, SSTAR_UINT, 0, value, 0.0, "");

}

/*---------------------------------------------------------------------------*/

Command::Command(const std::string& pv, double value, Operation op)
{

   init(pv, op, SSTAR_DOUBLE, 0, 0, value, "");

}

/*---------------------------------------------------------------------------*/

Command::Command(const std::string& pv, 
                 const std::string& value, 
                 Operation op)
{

   init(pv, op, SSTAR_STRING, 0, 0, 0, value);

}

/*---------------------------------------------------------------------------*/

Command::Command(const Command& cmd)
{

   init(cmd.getPVName(),
        cmd.getOperation(),
        cmd.getType(),
        cmd.getValueI(),
        cmd.getValueUI(),
        cmd.getValueD(),
        cmd.getValueS());

}

/*---------------------------------------------------------------------------*/

Command& Command::operator=(const Command& cmd)
{

   init(cmd.getPVName(),
        cmd.getOperation(),
        cmd.getType(),
        cmd.getValueI(),
        cmd.getValueUI(),
        cmd.getValueD(),
        cmd.getValueS());

   return *this;

}

/*---------------------------------------------------------------------------*/

Command::~Command()
{


}

/*---------------------------------------------------------------------------*/

Command::DataType Command::getType() const
{

   return m_dataType;

}

/*---------------------------------------------------------------------------*/

Command::Operation Command::getOperation() const
{

   return m_operation;

}

/*---------------------------------------------------------------------------*/

const std::string& Command::getPVName() const
{

   return m_pvName;

}

/*---------------------------------------------------------------------------*/

double Command::getValueD() const
{

   return m_dataD;

}

/*---------------------------------------------------------------------------*/

int Command::getValueI() const
{

   return m_dataI;

}  

/*---------------------------------------------------------------------------*/

const std::string& Command::getValueS() const
{

   return m_dataS;

}

/*---------------------------------------------------------------------------*/

int Command::getValueUI() const
{

   return m_dataUI;
}

/*---------------------------------------------------------------------------*/

void Command::init(const std::string& pv, 
                   Operation op,
                   DataType type,
                   int vi,
                   unsigned int uvi,
                   double di,
                   const std::string& ds)
{

   m_pvName = pv;
   m_operation = op;
   m_dataType = type;
   m_dataI = vi;
   m_dataUI = uvi;
   m_dataD = di;
   m_dataS = ds;

}

/*---------------------------------------------------------------------------*/

void Command::print(int gaps) const
{
   for (int i=0; i<gaps; i++)
   {
      cout<<"  ";
   }

   switch(m_operation)
   {
      case PV_PUT_SYNC:
        cout<<"synPut "<<m_pvName<<" = ";
        break;
      case PV_PUT_ASYNC:
        cout<<"asynPut "<<m_pvName<< " = ";
        break;
      case PV_WAIT:
        cout<<"while ("<<m_pvName<<" ) != ";
        break;
   }

   switch (m_dataType)
   {
      case SSTAR_INT:
        cout<<m_dataI;
        break;
      case SSTAR_UINT:
        cout<<m_dataUI;
        break;
      case SSTAR_DOUBLE:
        cout<<m_dataD;
        break;
      case SSTAR_STRING:
        cout<<m_dataS;
        break;
      default:
        cout<<"{Error: Invalid Data Type}";
   }

   cout<<";"<<std::endl;

}


/*---------------------------------------------------------------------------*/

void Command::setType(DataType t)
{

   m_dataType = t;

}

/*---------------------------------------------------------------------------*/

void Command::setOperation(Operation op)
{

   m_operation = op;

}

/*---------------------------------------------------------------------------*/

void Command::setPVName(const std::string& pv, DataType dt)
{

   m_pvName = pv;
   m_dataType =dt;

}

/*---------------------------------------------------------------------------*/

void Command::setValueD(double d)
{

   m_dataD = d;

}

/*---------------------------------------------------------------------------*/

void Command::setValueI(int i)
{

   m_dataI = i;

}

/*---------------------------------------------------------------------------*/

void Command::setValueS(const std::string& s)
{

   m_dataS = s;

}

/*---------------------------------------------------------------------------*/

void Command::setValueUI(unsigned int i)
{

   m_dataUI = i;

}

/*---------------------------------------------------------------------------*/

