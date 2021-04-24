/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_LOOP_H
#define SSTAR_LOOP_H

/*---------------------------------------------------------------------------*/

/**
 * The loop provides iterator like methods for producing values between an 
 *  initial value (inclusive) and end value (inclusive) based on the step size.
 *
 *  Loop is used by the ScanLoopCommand to produce values for setting PVs. 
 *  e.g. moving the motor 
 */
template <class T>
class Loop 
{

public:

   /**
    * Intiaialize the loop with initial and end values and step
    * size to zero.
    */
   Loop();

   /**
    * Initialize the loop with given intiale, end and step values.
    *
    * @param first - Initial value
    * @param step - Step size
    * @param last = The end value.
    */
   Loop(const T& first, const T& step, const T& last);

   /**
    * Get the intial value
    */
   const T& first() const;

   /**
    * Get the next value in the iteration. Make sure to call 
    * hasNext() before calling this method. Otherwise the values
    * can go above end value.
    */
   const T& getNext();
   
   /**
    * The loop has more values.
    *
    * @return True - if calling getNext() method will produce a valid
    *   value between initial and end (both inclusive), false otherwise.
    */
   bool hasNext();

   /**
    * Returns the end value.
    */
   const T& last() const;
   
   /**
    * Reset internal counters to the original state. Loop can
    * be re-evaluated after calling this method.
    */
   void reset();

   /**
    * Re-define the loop.
    *
    * @param first - Initial value
    * @param step - Step size
    * @param last - End value.
    */
   void setLoop(const T& first, const T& step, const T& last);

   /**
    * The currently configured step size.
    */
   const T& step() const;

private:

   T m_first;

   T m_last;

   T m_step;

   T m_current;

};

/*---------------------------------------------------------------------------*/

template <class T>
Loop<T>::Loop()
{

   m_first = 0;
   m_last = 0;
   m_step = 0;
   m_current = 0;

}

/*---------------------------------------------------------------------------*/

template <class T>
Loop<T>::Loop(const T& first, const T& step, const T& last)
{

   setLoop(first, step, last);

}

/*---------------------------------------------------------------------------*/

template <class T>
const T& Loop<T>::first() const
{
   
   return m_first;
}

/*---------------------------------------------------------------------------*/

template <class T>
const T& Loop<T>::getNext()
{

   m_current += m_step;
   return m_current;

}

/*---------------------------------------------------------------------------*/

template <class T>
bool Loop<T>::hasNext()
{

   return (m_current + m_step) <= m_last;

}

/*---------------------------------------------------------------------------*/

template <class T>
const T& Loop<T>::last() const
{

   return m_last;

}

/*---------------------------------------------------------------------------*/

template <class T>
void Loop<T>::reset()
{
   
   m_current = m_first - m_step;

}

/*---------------------------------------------------------------------------*/

template <class T>
void Loop<T>::setLoop(const T& first, const T& step, const T& last)
{

   m_first = first;
   m_last = last;
   m_step = step;

   m_current = m_first - m_step;

}

/*---------------------------------------------------------------------------*/

template <class T>
const T& Loop<T>::step() const
{
   
   return m_step;

}

/*---------------------------------------------------------------------------*/

#endif
