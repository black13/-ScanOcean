/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#ifndef SSTAR_LOOP_H
#define SSTAR_LOOP_H

/*---------------------------------------------------------------------------*/

template <class T>
class Loop 
{

public:

   Loop();

   Loop(const T& first, const T& step, const T& last);

   const T& first() const;

   const T& getNext();
   
   bool hasNext();

   const T& last() const;
   
   void reset();

   void setLoop(const T& first, const T& step, const T& last);

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
