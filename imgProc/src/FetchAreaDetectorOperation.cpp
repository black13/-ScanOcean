
#include <FetchAreaDetectorOperation.h>

#include <Stage.h>

FetchAreaDetectorOperation::FetchAreaDetectorOperation(std::string name, AbstractImageBuffer* output)
: Source(output),
  m_name(name)
{

   m_dataChange = new CAEmitDataChangeHandler<int,FetchAreaDetectorOperation>
      (this,&FetchAreaDetectorOperation::newIndex);



   ChannelAccess* ca = ChannelAccess::getInstance();
   m_UniqueId_RBV = ca->getPV(m_name + "UniqueId_RBV",1,5);
   m_UniqueId_RBV->subscribeDataChangeEvent(m_dataChange);


}

FetchAreaDetectorOperation::~FetchAreaDetectorOperation()
{

   m_UniqueId_RBV->unsubscribeDataChangeEvent(m_dataChange);
   if(m_dataChange != NULL) delete m_dataChange;

}

void FetchAreaDetectorOperation::newIndex(int index)
{

   getParent()->update();

}

void FetchAreaDetectorOperation::execute()
{


   ChannelAccess* ca = ChannelAccess::getInstance();

   m_ArraySize0_RBV = ca->getPV(m_name + "ArraySize0_RBV",1,5);
   m_ArraySize1_RBV = ca->getPV(m_name + "ArraySize1_RBV",1,5);
   m_ArraySize2_RBV = ca->getPV(m_name + "ArraySize2_RBV",1,5);
   m_ColorMode_RBV = ca->getPV(m_name + "ColorMode_RBV",1,5);
   m_ArrayData = ca->getPV(m_name + "ArrayData",1,5);


   int width = 0;
   int height = 0;
   int depth = 0;
   int colorMode = 0;
   CAGetTotalCopy<int> widthReader(&width);
   CAGetTotalCopy<int> heightReader(&height);
   CAGetTotalCopy<int> depthReader(&depth);
   CAGetTotalCopy<int> colorModeReader(&colorMode);
   m_ArraySize0_RBV->synGet(1,&widthReader);
   m_ArraySize1_RBV->synGet(1,&heightReader);
   m_ArraySize2_RBV->synGet(1,&depthReader);
   m_ColorMode_RBV->synGet(1,&colorModeReader);

   // Image size check
   if (width <= 0 || height <= 0) {
      std::cout << "ERROR" << std::endl;
      return;
   }

   // Image depth check
   if (depth < 0 || depth > 1) {
      std::cout << "ERROR" << std::endl;
      return;
   }

   // Color mode check
   if (colorMode != 0) {
      std::cout << "ERROR" << std::endl;
      return;
   }

   Image<unsigned char> * destImage = m_outputBuffer->getImageForWrite();

   if(destImage != NULL)
   {
      CAGetTotalCopy<unsigned char> arrayDataReader((*destImage)());
      m_ArrayData->synGet(destImage->getWidth() * destImage->getHeight(),
                          &arrayDataReader);

      m_outputBuffer->disposeImageForWrite(destImage);
   }



}
