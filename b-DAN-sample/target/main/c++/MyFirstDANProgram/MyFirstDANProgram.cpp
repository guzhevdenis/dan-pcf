//+======================================================================
// $HeadURL: https://svnpub.codac.iter.org/codac/iter/codac/dev/units/m-codac-unit-templates/branches/codac-core-6.3/templates/cpp/main/c++/prog/service.cpp.template $
// $Id: service.cpp.template 116150 2021-01-04 09:45:04Z kimh19 $
//
// Project       : CODAC Core System
//
// Description   : MyFirstDANProgram service
//
// Author        : codac-dev
//
// Copyright (c) : 2010-2021 ITER Organization,
//                 CS 90 046
//                 13067 St. Paul-lez-Durance Cedex
//                 France
//
// This file is part of ITER CODAC software.
// For the terms and conditions of redistribution or use of this software
// refer to the file ITER-LICENSE.TXT located in the top level directory
// of the distribution package.
//
//-======================================================================

#include <iostream>
#include <thread>
#include <chrono>


#include <sdd-dan.h> /* contains all CCS DAN library API
definition, etc. */
//if you have extended the data block header for dan, include the
//corresponding header

#include <log.h>

int main(int argc, const char* argv[]) {
  
  std::cout << "This is MyFirstDANProgram program" << std::endl;
  
  dan_DataCore dc=NULL; //Datacore reference declaration
  dan_Source ds=NULL; // DAN source declaration

  dc = dan_initLibrary_icprog("MyFirstDANProgram"); // DAN library initialization
  if (dc == NULL) {

	  log_error("Error during DAN init ");
	  exValue=1;

	  goto END;
  }

  log_info( "DAN INIT OK ");

  //initialize tcn library
  tcn_err = tcn_init();

  if (tcn_err != TCN_SUCCESS)
  {
	  log_error( "TCN init NOK : %s",tcn_strerror(tcn_err));
	  exValue=1;
	  goto END;
  }

  int blockSize = 100; // Block size constant
  int nBlocks =200; // Number of blocks constant
  int sampleSize=8; // Size in bytes of samples
  long sampleCounter=0; // Counter of samples already produced
  int result; // For result values
  // Initialize source with a internal DAQBuffer with a size
  // of blockSize*nBlocks*sampleSize bytes

  ds = dan_publisher_publishSource_withDAQBuffer(dc,
		  	  	  	  	  	  	  	  	  	  	 DummySrc,
												 blockSize*nBlocks*sampleSize);

  if (ds == NULL) {
	  log_final("Error while publishing DAN source %s ", DummySrc);
	  exValue=1;
	  goto END;
  }

  log_info( "DAN PUBLISH SOURCE OK ");

  int samplingRate=1000;
  float *values;
  values = (float *)malloc(blockSize * sampleSize);
  // Open a new stream in the source previously initialized
  // with 1000 samples/second of sampling rate
  // and 0 bytes of initial offset into DAQBuffer.
  dan_publisher_openStream(ds,samplingRate,0);

  DAN_DATA_BLOCK_HEADER_TYPE_IMG blockHead;
  blockHead.pos_x=100;
  blockHead.pos_y=1100;


  while(!toterminate && (tcn_wait_until_hr(till,&tBase,0)==
  TCN_SUCCESS)) {
  // Local function to fill float values

  initBufferWithData((char *)values,
  blockSize*sampleSize,
  sampleCounter);

  // To calculate first timeStamp (only first time)
  if (tBase==0) {
	  res = tcn_get_time(&tBase) - (blockSize * 1000000000 /
			  samplingRate);
  }
  // datablock header structure has been defined in .h
  // header file that was automatically generated from SDD
  // editor. It includes default fields and datablock header
  // extension (pos_x and pos_y) in this case
  /***this part is optional put NULL if you dont need, and
  update dan_config.xml accordingly****/

  blockHead.std_header.dim1=1;
  blockHead.std_header.dim2=1;
  blockHead.std_header.operational_mode=0;
  blockHead.std_header.sampling_rate= samplingRate;
  blockHead.pos_x +=1;
  blockHead.pos_y +=1;
  // Push new data block and its modified header into source
  //put NULL if you didnt define blockHead
  //timestamp is absolute timestamp

  result=dan_publisher_putDataBlock (ds,
		  	  	  	  	  	  	  	 (till),
									 (char *) values,
									 blockSize*sampleSize,
									 (char *)&blockHead);

  // Detected overflow in pass datablock reference queue
  if (result == -1) {
	  	 log_info("%s, Queue overflow with policy %d\n",
	  	  			  DummySrc,dan_publisher_getCheckPolicy(ds));
  }

  // Detected overflow in DAQBuffer
  else if (result == -2) {
	  log_info("%s, DAQ buffer overflow \
 	 			with policy %d\n",
				DummySrc,dan_publisher_getCheckPolicy(ds));
  }

  sampleCounter += blockSize;
  till = till + 1000000L ;

  }

  log_info( "DAN end of acquisition, closing all resources");
  // Closing stream

  dan_publisher_closeStream(ds);

  END:
  // Free local values array

  if (values != NULL) {
	  free(values);
  }
  // Unpublishing source from DAN API

  if (ds != NULL) {
	  dan_publisher_unpublishSource(dc, ds);
  }

  // Closing DAN API library
  if (dc != NULL) {
	  dan_closeLibrary(dc);
  }

  log_info( "DAN end of acquisition, resources are now closed");
  log_flush_queue();
  log_finalize();

  return exValue;

  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << ".";
    std::cout.flush();
  }
}
