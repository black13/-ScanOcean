/*-----------------------------------------------------------------------------
 * Copyright (c) 2012, UChicago Argonne, LLC
 * See LICENSE file.
 *---------------------------------------------------------------------------*/

#include <Stage.h>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

/*---------------------------------------------------------------------------*/

Stage::Stage()
: Thread()
{

   // Generate default stage name as a UUID
   boost::uuids::uuid uuid = boost::uuids::random_generator()();
   m_stageId = boost::lexical_cast<std::string>(uuid);

   // Set input and output buffers
   m_inputBuffer = NULL;
   m_outputBuffer = NULL;

}

/*---------------------------------------------------------------------------*/

Stage::~Stage()
{

}

/*---------------------------------------------------------------------------*/

void Stage::setInputBuffer(Buffer* buffer)
{

   m_inputBuffer = buffer;
   m_inputBuffer -> registerDestination(m_stageId);

}

/*---------------------------------------------------------------------------*/

void Stage::setOutputBuffer(Buffer* buffer)
{

   m_outputBuffer = buffer;

}

/*---------------------------------------------------------------------------*/
