/*
 * LIColorTransferFunction.h
 *
 *  Created on: Oct 9, 2012
 *      Author: afaraldo
 */

#ifndef LICOLORTRANSFERFUNCTION_H_
#define LICOLORTRANSFERFUNCTION_H_

#include <AbstractColorTransferFunction.h>

#include <list>
#include <utility>

//TODO Better testing more this class. There might be corner-cases I did not
//     consider in the implementation
/**
 * Implementation of an AbstractColorTransferFunction. The color mapping
 * is modified providing knots. Value are linearly interpolated and the
 * mapping object is updated accordingly
 */
class LIColorTransferFunction
: public AbstractColorTransferFunction
{

public:
   /**
    * Constructor
    */
   LIColorTransferFunction();

   /**
    * Destructor
    */
   virtual ~LIColorTransferFunction();

   /**
    * Add a knot to the red channel
    *
    * @param value X-coordinate of the knot
    * @param colorMappend Y-coordinate of the knot
    */
   void addRedKnot(unsigned char value, unsigned char colorMapped);

   /**
    * Add a knot to the green channel
    *
    * @param value X-coordinate of the knot
    * @param colorMappend Y-coordinate of the knot
    */
   void addGreenKnot(unsigned char value, unsigned char colorMapped);

   /**
    * Add a knot to the blue channel
    *
    * @param value X-coordinate of the knot
    * @param colorMappend Y-coordinate of the knot
    */
   void addBlueKnot(unsigned char value, unsigned char colorMapped);

   /**
    * Remove a knot from the red channel (if any)
    *
    * @param value X-coordinate of the knot
    */
   void removeRedKnot(unsigned char value);

   /**
    * Remove a knot from the green channel (if any)
    *
    * @param value X-coordinate of the knot
    */
   void removeGreenKnot(unsigned char value);

   /**
    * Remove a knot from the blue channel (if any)
    *
    * @param value X-coordinate of the knot
    */
   void removeBlueKnot(unsigned char value);

private:

   /**
    * Debuggin accessory
    */
   void printKnot(std::pair<unsigned char, unsigned char>& knot);

   /**
    * List of red knots
    */
   std::list<std::pair<unsigned char, unsigned char> > m_redKnots;

   /**
    * List of green knots
    */
   std::list<std::pair<unsigned char, unsigned char> > m_greenKnots;

   /**
    * List of blue knots
    */
   std::list<std::pair<unsigned char, unsigned char> > m_blueKnots;

   /**
    * Accessory to interpolate
    *
    * @param x1 X-coordinate of the starting point
    * @param y1 Y-coordinate of the starting point
    * @param x2 X-coordinate of the ending point
    * @param y2 Y-coordinate of the ending point
    * @param value X-coordinate of the value whose Y-coordinate we want to
    *              interpolate
    */
   unsigned char interpolate(unsigned char x1,
                             unsigned char y1,
                             unsigned char x2,
                             unsigned char y2,
                             unsigned char value);

   /**
    * Add a knot and update the color mapping
    */
   void addKnot(ColorTransferMapping* mapping,
                void (ColorTransferMapping::*fPtr)(int, unsigned char),
                std::list<std::pair<unsigned char, unsigned char> >& knotList,
                unsigned char value,
                unsigned char colorMapped
                );

   /**
    * Remove a knot and update the color mapping
    */
   void removeKnot(ColorTransferMapping* mapping,
         void (ColorTransferMapping::*fPtr)(int, unsigned char),
         std::list<std::pair<unsigned char, unsigned char> >& knotList,
         unsigned char value);

   /**
    * Update the color mapping
    */
   void update(unsigned char x1,
               unsigned char y1,
               unsigned char mx,
               unsigned char my,
               unsigned char x2,
               unsigned char y2,
               ColorTransferMapping* mapping,
               void (ColorTransferMapping::*fPtr)(int, unsigned char));


};

#endif /* LICOLORTRANSFERFUNCTION_H_ */
