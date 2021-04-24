/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef CA_H
#define CA_H

/*---------------------------------------------------------------------------*/

#include <cadef.h>

#include <QMap>
#include <QObject>
#include <QString>

/*---------------------------------------------------------------------------*/

/**
 * @brief EPICS Channel Access class.
 */
class CA
: public QObject
{

   Q_OBJECT

public:

   /**
    * Default constructor
    *
    * @param parent - the Qt parent object
    */
   CA(QObject* parent = 0);

   /**
    * Destructor
    */
   ~CA();

   /**
    * Attach context for using channel access from a thread.
    */
   void attach();

   /**
    * Clear a PV by name.
    *
    * @param name - PV name
    */
   void clear(QString name);

   /*
    * Create a PV by name.
    *
    * @param name - PV to connect
    * @param flush - Wait for pend IO to complete if true, don't wait if false.
    */
   void create(QString name, bool flush = true);

   /*
    * Perform a ca_get() for an int.
    *
    * @param name - PV
    * @param val - Memory to place data read from PV
    * @param flush - Wait for pend IO to complete if true, don't wait if false.
    */
   void get(QString name, int* val, bool flush = true);

   /**
    * Perform a ca_array_get(). Uses the EPICS type associated with the PV
    * in the ca_array_get() call.
    *
    * @param name - PV
    * @param array - Memory to place data read from PV
    * @param sz - Size of array
    * @param flush - Wait for pend IO to complete if true, don't wait if false.
    */
   void getArray(QString name,
                 char* array,
                 unsigned long sz,
                 bool flush = true);

   /*
    * Get the EPICS type for a PV.
    *
    * @param name - PV
    * @param flush - Wait for pend IO to complete if true, don't wait if false.
    */
   chtype getFieldType(QString name, bool flush = true);

   /**
    * Pend IO.
    */
   void pend();

   /*
    * Perform a ca_put() with an array of chars.
    *
    * @param name - PV
    * @param array - Array to put
    * @param sz - Size of array to put
    * @param flush - Wait for pend IO to complete if true, don't wait if false.
    */
   void put(QString name, char* array, unsigned int sz, bool flush = true);

   /*
    * Perform a ca_put() with a single double.
    *
    * @param name - PV
    * @param val - Value to put
    * @param flush - Wait for pend IO to complete if true, don't wait if false.
    */
   void put(QString name, double val, bool flush = true);

   /*
    * Perform a ca_put() with a single int.
    *
    * @param name - PV
    * @param val - Value to put
    * @param flush - Wait for pend IO to complete if true, don't wait if false.
    */
   void put(QString name, int val, bool flush = true);

   /**
    * Create a monitor subscription on a PV. The channel must have been created
    * using create().
    *
    * @param name - PV
    * @param flush - Wait for pend IO to complete if true, don't wait if false.
    */
   void subscribe(QString name, bool flush = true);

signals:

   /**
    * Signal emitted by a double monitor.
    *
    * @param name - PV
    * @param val - updated PV value
    */
   void update(QString name, double val);

   /**
    * Signal emitted by an int monitor.
    *
    * @param name - PV
    * @param val - updated PV value
    */
   void update(QString name, int val);

   /**
    * Signal emitted by a char or char* monitor.
    *
    * @param name - PV
    * @param val - updated PV value
    */
   void update(QString name, QString val);

private:

   /**
    * Class callback for char* PVs called by epicsCallback()
    *
    * @param name - PV
    * @param arr - updated char array
    * @param sz - size of updated array
    */
   void callback(QString name, char* arr, int sz);

   /**
    * Class callback for double PVs called by epicsCallback()
    *
    * @param name - PV
    * @param val - updated double value
    */
   void callback(QString name, double val);

   /**
    * Class callback for int PVs called by epicsCallback()
    *
    * @param name - PV
    * @param val - updated int value
    */
   void callback(QString name, int val);

   /**
    * EPICS subscription callback for PV
    *
    * @param args - See EPICS reference documentation
    */
   static void epicsCallback(struct event_handler_args args);

private:

   /**
    * Current CA Context
    */
   ca_client_context* m_caContext;

   /**
    * Map of PV names to chids
    */
   QMap<QString, chid> m_mapCA;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
