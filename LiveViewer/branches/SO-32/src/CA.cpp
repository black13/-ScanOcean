/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <CA.h>
#include <stdio.h>

/*---------------------------------------------------------------------------*/

CA::CA(QObject* parent)
: QObject(parent)
{

   // Create CA context
   ca_context_create(ca_enable_preemptive_callback);
   m_caContext = ca_current_context();

}

/*---------------------------------------------------------------------------*/

CA::~CA()
{

   // Destroy CA context
   ca_context_destroy();

}

/*---------------------------------------------------------------------------*/

void CA::attach()
{

   ca_attach_context(m_caContext);
   pend();

}

/*---------------------------------------------------------------------------*/

void CA::callback(QString name, char* arr, int sz)
{

   // Copy array for QString
   char* str = new char[sz + 1];
   memset(str, '\0', sz + 1);
   memcpy(str, arr, sz);

   emit update(name, QString(str));

   // Clean-up
   delete [] str;

}

/*---------------------------------------------------------------------------*/

void CA::callback(QString name, double val)
{

   emit update(name, val);

}

/*---------------------------------------------------------------------------*/

void CA::callback(QString name, int val)
{

   emit update(name, val);

}

/*---------------------------------------------------------------------------*/

void CA::clear(QString name)
{

   ca_clear_channel(m_mapCA[name]);

}

/*---------------------------------------------------------------------------*/

void CA::create(QString name, bool flush)
{

   chid id;

   ca_create_channel(name.toLocal8Bit().data(),
                     NULL,
                     NULL,
                     CA_PRIORITY_DEFAULT,
                     &id);

   if (flush == true) {
      pend();
   }

   m_mapCA.insert(name, id);

}

/*---------------------------------------------------------------------------*/

void CA::epicsCallback(struct event_handler_args args)
{

   // Check for CA error
   if (args.status != ECA_NORMAL) {
      return;
   }

   // Check datatype
   switch (args.type) {

   // Get name and value, and call class updater method
   case DBR_STRING:
   {
      const char* name = ca_name(args.chid);
      char* data = (char*) args.dbr;
      //((CA*) args.usr) -> callback(QString(name), (double) (data -> value));
      break;
   }

   case DBR_SHORT:
   {
      const char* name = ca_name(args.chid);
      short* data = (short*) args.dbr;
      ((CA*) args.usr) -> callback(QString(name), (int) (*data));
      break;
   }

   case DBR_FLOAT:
   {
      const char* name = ca_name(args.chid);
      float* data = (float*) args.dbr;
      ((CA*) args.usr) -> callback(QString(name), (float) (*data));
      break;
   }

   case DBR_ENUM:
   {
      const char* name = ca_name(args.chid);
      short* data = (short*) args.dbr;
      ((CA*) args.usr) -> callback(QString(name), (int) (*data));
      break;
   }

   case DBR_CHAR:
   {
      const char* name = ca_name(args.chid);
      char* data = (char*) args.dbr;
      ((CA*) args.usr) -> callback(QString(name), data, args.count);
      break;
   }

   case DBR_LONG:
   {
      const char* name = ca_name(args.chid);
      int* data = (int*) args.dbr;
      ((CA*) args.usr) -> callback(QString(name), (int) (*data));
      break;
   }

   case DBR_DOUBLE:
   {
      const char* name = ca_name(args.chid);
      double* data = (double*) args.dbr;
      ((CA*) args.usr) -> callback(QString(name), (double) (*data));
      break;
   }

   default:
   {
      break;
   }

   }

}

/*---------------------------------------------------------------------------*/

void CA::get(QString name, int* val, bool flush)
{

   ca_get(DBR_INT, m_mapCA[name], val);

   if (flush) {
      pend();
   }

}

/*---------------------------------------------------------------------------*/

void CA::getArray(QString name, char* array, unsigned long sz, bool flush)
{

   chtype dt = ca_field_type(m_mapCA[name]);

   ca_array_get(dt, sz, m_mapCA[name], array);

   if (flush) {
      pend();
   }

}

/*---------------------------------------------------------------------------*/

chtype CA::getFieldType(QString name, bool flush)
{

   chtype type = ca_field_type(m_mapCA[name]);

   if (flush) {
      pend();
   }

   return type;

}

/*---------------------------------------------------------------------------*/

void CA::pend()
{

   ca_pend_io(5.0);

}

/*---------------------------------------------------------------------------*/

void CA::put(QString name, char* array, unsigned int sz, bool flush)
{

   ca_array_put(DBF_CHAR, sz, m_mapCA[name], array);

   if (flush) {
      pend();
   }

}

/*---------------------------------------------------------------------------*/

void CA::put(QString name, double val, bool flush)
{

   ca_put(DBR_DOUBLE, m_mapCA[name], &val);

   if (flush) {
      pend();
   }

}

/*---------------------------------------------------------------------------*/

void CA::put(QString name, int val, bool flush)
{

   ca_put(DBR_INT, m_mapCA[name], &val);

   if (flush) {
      pend();
   }

}

/*---------------------------------------------------------------------------*/

void CA::subscribe(QString name, bool flush)
{

   ca_create_subscription(ca_field_type(m_mapCA[name]),
                          0,
                          m_mapCA[name],
                          DBE_VALUE | DBE_ALARM,
                          CA::epicsCallback,
                          this,
                          NULL);

   if (flush == true) {
      pend();
   }

}

/*---------------------------------------------------------------------------*/
