
#ifndef FETCHAREADETECTOR_H_
#define FETCHAREADETECTOR_H_

#include <Source.h>
#include <Operation.h>
#include <AbstractImageBuffer.h>
#include <Image.h>

#include <SStar.h>
#include <CAEmitDataChangeHandler.h>

/**
 * Implementation of a source that fetches from the AreaDetector simulation
 */
class FetchAreaDetectorOperation
: public Source,
  public Operation
{

public:
   /**
    * Constructor
    *
    * @param prefix ChannelAccess prefix for the area detector
    * @param output OutputBuffer
    */
   FetchAreaDetectorOperation(std::string prefix, AbstractImageBuffer* output);

   /**
    * Destructor
    */
   virtual ~FetchAreaDetectorOperation();

   /**
    * Execute the operation
    */
   void execute();

private:

   /**
    * Function called by a subscription to the area detector index PV.
    * This function calls the 'update' function of the stage containing
    * the operation to notify that a new image has arrived
    */
   void newIndex(int index);

   /**
    * Channel access prefix
    */
   std::string m_name;

   /**
    * Data change handler
    */
   CAEmitDataChangeHandler<int,FetchAreaDetectorOperation>* m_dataChange;

   /**
    * Data PV
    */
   boost::shared_ptr<PV> m_ArrayData;

   /**
    * Id PV
    */
   boost::shared_ptr<PV> m_UniqueId_RBV;

   /**
    * PV
    */
   boost::shared_ptr<PV> m_ArraySize0_RBV;

   /**
    * PV
    */
   boost::shared_ptr<PV> m_ArraySize1_RBV;

   /**
    * PV
    */
   boost::shared_ptr<PV> m_ArraySize2_RBV;

   /**
    * PV
    */
   boost::shared_ptr<PV> m_ColorMode_RBV;

};

#endif
