
#include <LIColorTransferFunction.h>

#include <iostream>

LIColorTransferFunction::LIColorTransferFunction()
: AbstractColorTransferFunction()
{

   m_redKnots.push_back(std::pair<unsigned char, unsigned char> (0,0));
   m_redKnots.push_back(std::pair<unsigned char, unsigned char> (255,255));

   m_greenKnots.push_back(std::pair<unsigned char, unsigned char> (0,0));
   m_greenKnots.push_back(std::pair<unsigned char, unsigned char> (255,255));

   m_blueKnots.push_back(std::pair<unsigned char, unsigned char> (0,0));
   m_blueKnots.push_back(std::pair<unsigned char, unsigned char> (255,255));

}

LIColorTransferFunction::~LIColorTransferFunction()
{

}

void LIColorTransferFunction::addRedKnot(unsigned char value,
                                         unsigned char colorMapped)
{

   addKnot(m_colorMap,
           &ColorTransferMapping::setRed,
           m_redKnots,
           value,
           colorMapped);

}

void LIColorTransferFunction::addGreenKnot(unsigned char value,
                                          unsigned char colorMapped)
{

   addKnot(m_colorMap,
           &ColorTransferMapping::setGreen,
           m_greenKnots,
           value,
           colorMapped);

}

void LIColorTransferFunction::addBlueKnot(unsigned char value,
                                          unsigned char colorMapped)
{

   addKnot(m_colorMap,
           &ColorTransferMapping::setBlue,
           m_blueKnots,
           value,
           colorMapped);

}



void LIColorTransferFunction::removeRedKnot(unsigned char value)
{

   removeKnot(m_colorMap,
              &ColorTransferMapping::setRed,
              m_redKnots,
              value);

}

void LIColorTransferFunction::removeGreenKnot(unsigned char value)
{

   removeKnot(m_colorMap,
              &ColorTransferMapping::setGreen,
              m_greenKnots,
              value);
}

void LIColorTransferFunction::removeBlueKnot(unsigned char value)
{

   removeKnot(m_colorMap,
              &ColorTransferMapping::setBlue,
              m_blueKnots,
              value);
}

void LIColorTransferFunction::removeKnot(ColorTransferMapping* mapping,
      void (ColorTransferMapping::*fPtr)(int, unsigned char),
      std::list<std::pair<unsigned char, unsigned char> >& knotList,
      unsigned char value)
{

   //Can't remove the start/beginning ones
   if(value != 0 && value != 255)
   {

      std::list<std::pair<unsigned char, unsigned char> >::iterator position;

      bool found = false;
      for(position = knotList.begin();
          position != knotList.end();
          ++position)
      {

         if(position->first == value)
         {
            found = true;
            break;
         }

      }

      if(found)
      {

         --position;
         std::pair<unsigned char, unsigned char> previousKnot = *position;


         ++position;
         ++position;
         std::pair<unsigned char, unsigned char> currentKnot = *position;


         --position;

         knotList.erase(position);

         for(int i = previousKnot.first + 1; i < currentKnot.first; i++ )
         {
            unsigned char ax = previousKnot.first;
            unsigned char ay = previousKnot.second;
            unsigned char bx = currentKnot.first;
            unsigned char by = currentKnot.second;

            unsigned char result = interpolate(ax,ay,bx,by,i);


            (mapping->*fPtr)(i,result);

         }
      }


   }

}

void LIColorTransferFunction::printKnot(std::pair<unsigned char, unsigned char>& knot)
{

   std::cout << "<" << (int) knot.first << "," << (int) knot.second << ">" << std::endl;

}

void LIColorTransferFunction::addKnot(ColorTransferMapping* mapping,
             void (ColorTransferMapping::*fPtr)(int, unsigned char),
             std::list<std::pair<unsigned char, unsigned char> >& knotList,
             unsigned char value,
             unsigned char colorMapped
             )
{

   std::list<std::pair<unsigned char, unsigned char> >::iterator previous;
   std::list<std::pair<unsigned char, unsigned char> >::iterator current;

   current = knotList.begin();
   previous = current;
   ++current;

   bool isDone = false;

   // Until there are knots to explore or the update is done
   for(; current != knotList.end() && !isDone; ++current)
   {
      std::pair<unsigned char, unsigned char> previousKnot = *previous;
      std::pair<unsigned char, unsigned char> currentKnot = *current;

      if(currentKnot.first > value && previousKnot.first < value)
      {
         knotList.insert(
            current,std::pair<unsigned char, unsigned char>(value,
                                                            colorMapped));

         update(previousKnot.first,
                   previousKnot.second,
                   value,
                   colorMapped,
                   currentKnot.first,
                   currentKnot.second,
                   mapping,
                   fPtr);

         //Stop the loop
         isDone = true;

      }
      else if(currentKnot.first == value && previousKnot.first == value)
      {
         //never happens...

         //Stop the loop
         isDone = true;
      }
      else if(currentKnot.first == value)
      {

         //They are the same, no update necessary
         if(currentKnot.second == colorMapped) return;

         //Modify the value
         currentKnot.first = value;
         currentKnot.second = colorMapped;

         //Take the next as current
         ++current;
         currentKnot = *current;

         //Update
         update(previousKnot.first,
                   previousKnot.second,
                   value,
                   colorMapped,
                   currentKnot.first,
                   currentKnot.second,
                   mapping,
                   fPtr);

         //Stop the loop
         isDone = true;

      }
      else if(previousKnot.first == value)
      {

         //They are the same, no update necessary
         if(previousKnot.second == colorMapped) return;

         //Modify the value
         previousKnot.first = value;
         previousKnot.second = colorMapped;

         //Take the previous as previous
         --previous;
         previousKnot = *previous;

         //Update
         update(previousKnot.first,
                   previousKnot.second,
                   value,
                   colorMapped,
                   currentKnot.first,
                   currentKnot.second,
                   mapping,
                   fPtr);

         //Stop the loop
         isDone = true;
      }

      //Move one step forward
      previous = current;

   }
}

unsigned char LIColorTransferFunction::interpolate(unsigned char x1,
                                                   unsigned char y1,
                                                   unsigned char x2,
                                                   unsigned char y2,
                                                   unsigned char value)
{

   unsigned char result = y1 + ((value - x1) * (y2 - y1)) / (x2 - x1);

   return result;

}

void LIColorTransferFunction::update(unsigned char x1,
            unsigned char y1,
            unsigned char mx,
            unsigned char my,
            unsigned char x2,
            unsigned char y2,
            ColorTransferMapping* mapping,
            void (ColorTransferMapping::*fPtr)(int, unsigned char))
{

   //Update pass

   //Set left side
   for(int i = x1 + 1; i < mx; i++)
   {
      unsigned char ax = x1;
      unsigned char ay = y1;
      unsigned char bx = mx;
      unsigned char by = my;

      unsigned char result = interpolate(ax,ay,bx,by,i);

      (mapping->*fPtr)(i,result);

   }

   //Set central color
   (mapping->*fPtr)(mx,my);

   for(int i = mx+1; i < x2; i++)
   {
      unsigned char ax = mx;
      unsigned char ay = my;
      unsigned char bx = x2;
      unsigned char by = y2;

      unsigned char result = interpolate(ax,ay,bx,by,i);

      (mapping->*fPtr)(i,result);
   }

}
