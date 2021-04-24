
#ifndef COLORTRANSFERMAPPING_H_
#define COLORTRANSFERMAPPING_H_

//TODO The class should be generalized to handle different kind of mapping
/**
 * Class that encapsulate the mapping between a 1 channel image and a
 * 3 channel image
 */
class ColorTransferMapping
{

public:
   /**
    * Constructor
    */
   ColorTransferMapping();

   /**
    * Destructor
    */
   virtual ~ColorTransferMapping();

   /**
    * Get the red color
    *
    * @param index Value between 0 and 255
    */
   unsigned char getRed(int index);

   /**
    * Get the blue color
    *
    * @param index Value between 0 and 255
    */
   unsigned char getBlue(int index);

   /**
    * Get the green color
    *
    * @param index Value between 0 and 255
    */
   unsigned char getGreen(int index);

   /**
    * Set all the red channel to the specified value
    *
    * @param value Value between 0 and 255
    */
   void setAllRed(unsigned char value);

   /**
    * Set all the blue channel to the specified value
    *
    * @param value Value between 0 and 255
    */
   void setAllBlue(unsigned char value);

   /**
    * Set all the green channel to the specified value
    *
    * @param value Value between 0 and 255
    */
   void setAllGreen(unsigned char value);

   /**
    * Set the red channel ad the provided index to the specified value
    *
    * @param index Index between 0 and 255
    * @param value Value between 0 and 255
    */
   void setRed(int index, unsigned char value);

   /**
    * Set the blue channel ad the provided index to the specified value
    *
    * @param index Index between 0 and 255
    * @param value Value between 0 and 255
    */
   void setBlue(int index, unsigned char value);

   /**
    * Set the green channel ad the provided index to the specified value
    *
    * @param index Index between 0 and 255
    * @param value Value between 0 and 255
    */
   void setGreen(int index, unsigned char value);

   // TODO Provide iterators to computer more efficients operations
private:

   bool isValidValue(int index);

   /**
    * Red mapping
    */
   unsigned char m_redMapping[256];

   /**
    * Green mapping
    */
   unsigned char m_greenMapping[256];

   /**
    * Blue mapping
    */
   unsigned char m_blueMapping[256];

};


#endif
