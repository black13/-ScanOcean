
/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_COMMAND_H
#define SSTAR_COMMAND_H

/*---------------------------------------------------------------------------*/

#include <string>

/*---------------------------------------------------------------------------*/

class Command 
{

public:

   enum DataType {
      SSTAR_SHORT,
      SSTAR_UINT,
      SSTAR_INT,
      SSTAR_LONG,
      SSTAR_FLOAT,
      SSTAR_DOUBLE,
      SSTAR_STRING
   };

   enum Operation {
      PV_PUT_SYNC,
      PV_PUT_ASYNC,
      PV_WAIT
   };

   /**
    * Construct a command, set the PV data type as integer. 
    *
    * @param pv - Name of the process variable.
    * @param value - An integer value - pv data type should be int. 
    * @param op - Ty pe of operation to perform
    */
   explicit Command(const std::string& pv, int value, Operation op=PV_PUT_ASYNC);

   /**
    * Construct a command, set the PV data type as integer. 
    *
    * @param pv - Name of the process variable.
    * @param value - An unsigned integer value - pv data type should be int. 
    * @param op - Ty pe of operation to perform
    */
   explicit Command(const std::string& pv, 
                    unsigned int value, 
                    Operation op=PV_PUT_ASYNC);

   /**
    * Construct a command, set the PV data type as double. 
    *
    * @param pv - Name of the process variable.
    * @param value - A double value - pv data type should be double or float. 
    * @param op - Ty pe of operation to perform
    */
   explicit Command(const std::string& pv, 
                    double value, 
                    Operation op=PV_PUT_ASYNC);

    /**
    * Construct a command, set the PV data type as double. 
    *
    * @param pv - Name of the process variable.
    * @param value - A string value - pv data type should be char. 
    * @param op - Ty pe of operation to perform
    */
   explicit Command(const std::string& pv, 
                    const std::string& value, 
                    Operation op=PV_PUT_ASYNC);

   /**
    * Copy constructor
    */
   Command(const Command& cmd);

   /**
    * Assignment operator
    */
   Command& operator=(const Command& cmd);

   /**
    * Deletes the command
    */
   ~Command();

   /**
    * Get PV type (int, double ...)
    * 
    * @return value of type DataType
    */
   DataType getType() const;

   /**
    *  Get PV operation associate with this command
    *
    *  @Return Operation enum
    */
   Operation getOperation() const;

   /**
    * Return the name of the PV associated with this command
    *
    * @return Name of pv.
    */
   const std::string& getPVName() const;

   /**
    * Get the double value, stored in the command
    */
   double getValueD() const;

   /**
    * Get the integer value.
    */
   int getValueI() const;

   /**
    * Get the string value
    */
   const std::string& getValueS() const;

   /**
    * Get the unsigned integer value.
    */
   int getValueUI() const;

   /**
    * Print the operation of this command with desired amoutn of spaces.
    * 
    * @param gap - Indent spaces = gap * 2;
    */
   void print(int gap) const;

   /**
    * Set the data-type of the PV associated with this object.
    *
    * @param type DataType enum value.
    */
   void setType(DataType type);

   /**
    * Set the desired operation value
    *
    * @param op Operation enum value.
    */
   void setOperation(Operation op);

   /**
    * Set the PV name, along with the data type of the pv.
    * Since the pv and its type might be associated very
    * strongly, the setter force the update to the type
    * of the pv. 
    *
    * @param pv - Name of the pv
    * @param dt - DataType enum.
    */
   void setPVName(const std::string& pv, DataType dt);

   /**
    * Set the double value.
    */
   void setValueD(double d);

   /**
    * Set the integer value.
    */
   void setValueI(int i);
   
   /**
    * Set the integer value.
    */
   void setValueS(const std::string& s);

   /**
    * Set the unsigned integer value.
    */
   void setValueUI(unsigned int i);

private:

   Command();
  
   /** 
    * Internal method to initialize the instance.
    */
   void init(const std::string& pv, 
        Operation op,
        DataType dt,
        int vi,
        unsigned int uvi,
        double di,
        const std::string& ds);

private:
   
   /**
    * Name of the PV
    */
   std::string m_pvName;

   /**
    * Type of operation to perform
    */
   Operation m_operation;

   /**
    * Data type of the PV
    */
   DataType m_dataType;

   /**
    * Integer value - used if pv value type is int
    */
   int m_dataI;

   /**
    * Unsigned integer value
    */
   unsigned m_dataUI;

   /**
    * Double value - used if pv value type is double or float
    */
   double m_dataD;

   /**
    * String data type
    */
   std::string m_dataS;

};

#endif

