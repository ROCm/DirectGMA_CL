
//
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//


#include "CL/opencl.h"
#include "iostream"
#include <fstream>
#include <stdio.h>
#include <string.h>


#define DATASIZE 40*1024*1024

using namespace std;


clEnqueueWaitSignalAMD_fn            clEnqueueWaitSignalAMD = NULL;
clEnqueueWriteSignalAMD_fn           clEnqueueWriteSignalAMD = NULL;
clEnqueueMakeBuffersResidentAMD_fn   clEnqueueMakeBuffersResidentAMD = NULL;

const char*  getOpenCLErrorCodeStr(int errorCode)
{

  switch (errorCode)
  {
  case CL_DEVICE_NOT_FOUND:
    return "CL_DEVICE_NOT_FOUND";
  case CL_DEVICE_NOT_AVAILABLE:
    return "CL_DEVICE_NOT_AVAILABLE";
  case CL_COMPILER_NOT_AVAILABLE:
    return "CL_COMPILER_NOT_AVAILABLE";
  case CL_MEM_OBJECT_ALLOCATION_FAILURE:
    return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
  case CL_OUT_OF_RESOURCES:
    return "CL_OUT_OF_RESOURCES";
  case CL_OUT_OF_HOST_MEMORY:
    return "CL_OUT_OF_HOST_MEMORY";
  case CL_PROFILING_INFO_NOT_AVAILABLE:
    return "CL_PROFILING_INFO_NOT_AVAILABLE";
  case CL_MEM_COPY_OVERLAP:
    return "CL_MEM_COPY_OVERLAP";
  case CL_IMAGE_FORMAT_MISMATCH:
    return "CL_IMAGE_FORMAT_MISMATCH";
  case CL_IMAGE_FORMAT_NOT_SUPPORTED:
    return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
  case CL_BUILD_PROGRAM_FAILURE:
    return "CL_BUILD_PROGRAM_FAILURE";
  case CL_MAP_FAILURE:
    return "CL_MAP_FAILURE";
  case CL_MISALIGNED_SUB_BUFFER_OFFSET:
    return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
  case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
    return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
  case CL_INVALID_VALUE:
    return "CL_INVALID_VALUE";
  case CL_INVALID_DEVICE_TYPE:
    return "CL_INVALID_DEVICE_TYPE";
  case CL_INVALID_PLATFORM:
    return "CL_INVALID_PLATFORM";
  case CL_INVALID_DEVICE:
    return "CL_INVALID_DEVICE";
  case CL_INVALID_CONTEXT:
    return "CL_INVALID_CONTEXT";
  case CL_INVALID_QUEUE_PROPERTIES:
    return "CL_INVALID_QUEUE_PROPERTIES";
  case CL_INVALID_COMMAND_QUEUE:
    return "CL_INVALID_COMMAND_QUEUE";
  case CL_INVALID_HOST_PTR:
    return "CL_INVALID_HOST_PTR";
  case CL_INVALID_MEM_OBJECT:
    return "CL_INVALID_MEM_OBJECT";
  case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
    return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
  case CL_INVALID_IMAGE_SIZE:
    return "CL_INVALID_IMAGE_SIZE";
  case CL_INVALID_SAMPLER:
    return "CL_INVALID_SAMPLER";
  case CL_INVALID_BINARY:
    return "CL_INVALID_BINARY";
  case CL_INVALID_BUILD_OPTIONS:
    return "CL_INVALID_BUILD_OPTIONS";
  case CL_INVALID_PROGRAM:
    return "CL_INVALID_PROGRAM";
  case CL_INVALID_PROGRAM_EXECUTABLE:
    return "CL_INVALID_PROGRAM_EXECUTABLE";
  case CL_INVALID_KERNEL_NAME:
    return "CL_INVALID_KERNEL_NAME";
  case CL_INVALID_KERNEL_DEFINITION:
    return "CL_INVALID_KERNEL_DEFINITION";
  case CL_INVALID_KERNEL:
    return "CL_INVALID_KERNEL";
  case CL_INVALID_ARG_INDEX:
    return "CL_INVALID_ARG_INDEX";
  case CL_INVALID_ARG_VALUE:
    return "CL_INVALID_ARG_VALUE";
  case CL_INVALID_ARG_SIZE:
    return "CL_INVALID_ARG_SIZE";
  case CL_INVALID_KERNEL_ARGS:
    return "CL_INVALID_KERNEL_ARGS";
  case CL_INVALID_WORK_DIMENSION:
    return "CL_INVALID_WORK_DIMENSION";
  case CL_INVALID_WORK_GROUP_SIZE:
    return "CL_INVALID_WORK_GROUP_SIZE";
  case CL_INVALID_WORK_ITEM_SIZE:
    return "CL_INVALID_WORK_ITEM_SIZE";
  case CL_INVALID_GLOBAL_OFFSET:
    return "CL_INVALID_GLOBAL_OFFSET";
  case CL_INVALID_EVENT_WAIT_LIST:
    return "CL_INVALID_EVENT_WAIT_LIST";
  case CL_INVALID_EVENT:
    return "CL_INVALID_EVENT";
  case CL_INVALID_OPERATION:
    return "CL_INVALID_OPERATION";
  case CL_INVALID_GL_OBJECT:
    return "CL_INVALID_GL_OBJECT";
  case CL_INVALID_BUFFER_SIZE:
    return "CL_INVALID_BUFFER_SIZE";
  case CL_INVALID_MIP_LEVEL:
    return "CL_INVALID_MIP_LEVEL";
  case CL_INVALID_GLOBAL_WORK_SIZE:
    return "CL_INVALID_GLOBAL_WORK_SIZE";
  case CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR:
    return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
  case CL_PLATFORM_NOT_FOUND_KHR:
    return "CL_PLATFORM_NOT_FOUND_KHR";
    //case CL_INVALID_PROPERTY_EXT:
    //    return "CL_INVALID_PROPERTY_EXT";
  case CL_DEVICE_PARTITION_FAILED_EXT:
    return "CL_DEVICE_PARTITION_FAILED_EXT";
  case CL_INVALID_PARTITION_COUNT_EXT:
    return "CL_INVALID_PARTITION_COUNT_EXT";
  default:
    return "unknown error code";
  }
}


void check_err(int err, const char * fctname, cl_context* ctx)
{
  if (err != CL_SUCCESS)
  {
    const char* error = getOpenCLErrorCodeStr(err);

    printf("%s failed with error : %s\n", fctname, error);
    if (ctx)
      clReleaseContext(*ctx);
    exit(EXIT_FAILURE);
  }
}

cl_int FinCLPlatform(cl_platform_id& platform)
{
  cl_int status = CL_SUCCESS;
  cl_uint numPlatforms;
  //cl_platform_id platform = NULL;
  status = clGetPlatformIDs(0, NULL, &numPlatforms);
  if (status != CL_SUCCESS)
  {
    cout << "Error: clGetPlatformIDs failed. Error code : " << status;

    return status;
  }

  if (0 < numPlatforms)
  {
    // Get selected platform
    cl_platform_id* platforms = new cl_platform_id[numPlatforms];
    status = clGetPlatformIDs(numPlatforms, platforms, NULL);
    if (status != CL_SUCCESS)
    {
      cout << "Error: clGetPlatformIDs failed. Error code : " << status;

      return status;
    }

    // Print all platforms
    for (unsigned i = 0; i < numPlatforms; ++i)
    {
      char pbuf[100];
      status = clGetPlatformInfo(platforms[i],
        CL_PLATFORM_VENDOR,
        sizeof(pbuf),
        pbuf,
        NULL);

      if (status != CL_SUCCESS)
      {
        cout << "Error: clGetPlatformInfo failed. Error code : ";
        delete[] platforms;
        return status;
      }

      cout << "Platform " << i << " : " << pbuf << endl;
    }

    // Get AMD platform
    for (unsigned i = 0; i < numPlatforms; ++i)
    {
      char pbuf[100];
      status = clGetPlatformInfo(platforms[i],
        CL_PLATFORM_VENDOR,
        sizeof(pbuf),
        pbuf,
        NULL);

      if (status != CL_SUCCESS)
      {
        cout << "Error: clGetPlatformInfo failed. Error code : ";
        delete[] platforms;
        return status;
      }

      platform = platforms[i];
      if (!strcmp(pbuf, "Advanced Micro Devices, Inc."))
      {
        break;
      }
    }

    // Check for AMD platform
    char pbuf[100];
    status = clGetPlatformInfo(platform,
      CL_PLATFORM_VENDOR,
      sizeof(pbuf),
      pbuf,
      NULL);

    if (status != CL_SUCCESS)
    {
      cout << "Error: clGetPlatformInfo failed. Error code : ";
      return status;
    }
    if (strcmp(pbuf, "Advanced Micro Devices, Inc.") == 0)
    {
      cout << "AMD platform found, we will use this one by default" << endl;
      // return -1;
    }
    else
    {
      
      cout << "can't find AMD platform, we have to abort" << endl;
      return -1;
    }


    delete[] platforms;
  }

  return status;

}


bool CheckDGMAExtension(cl_device_id deviceID)
{
  size_t extensionSize;
  clGetDeviceInfo(deviceID, CL_DEVICE_EXTENSIONS, 0, NULL, &extensionSize);

  char* ExtensionName = new char[extensionSize];
  clGetDeviceInfo(deviceID, CL_DEVICE_EXTENSIONS, extensionSize, ExtensionName, NULL);

  string extensions_string = string(ExtensionName);

  std::size_t pos = extensions_string.find("cl_amd_bus_addressable_memory");
  if (pos == std::string::npos)
  {
    return false;
  }
  return true;
}

void CheckTopology(cl_device_id deviceID, int devicenumber)
{
  cl_device_topology_amd topo;
  clGetDeviceInfo(deviceID, CL_DEVICE_TOPOLOGY_AMD, sizeof(cl_device_topology_amd), &topo, NULL);
  cout << "device " << devicenumber << " has Bus ID : " << +topo.pcie.bus << endl;
}

cl_int InitCL(cl_context& context, cl_command_queue queue[2])
{
  cl_int status = CL_SUCCESS;
  cl_platform_id platform = NULL;
  cl_context_properties properties[3];


  status = FinCLPlatform(platform);

  if (status != CL_SUCCESS || platform == NULL)
  {
    cout << "can't find a OpenCL platform" << endl;
    return status;
  }

  //I only want to test on GPU for the moment,
  unsigned int NBDevices = 0;
  status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, &NBDevices);

  if (NBDevices<2)
  {
    cout << "We need 2 GPU to run this sample" << endl;
    return -1;
  }

  //we test on all devices

  clEnqueueWaitSignalAMD = (clEnqueueWaitSignalAMD_fn)clGetExtensionFunctionAddressForPlatform(platform, "clEnqueueWaitSignalAMD");
  clEnqueueWriteSignalAMD = (clEnqueueWriteSignalAMD_fn)clGetExtensionFunctionAddressForPlatform(platform, "clEnqueueWriteSignalAMD");
  clEnqueueMakeBuffersResidentAMD = (clEnqueueMakeBuffersResidentAMD_fn)clGetExtensionFunctionAddressForPlatform(platform, "clEnqueueMakeBuffersResidentAMD");


  int NBDeviceToUse = 2;


  cl_device_id* devices = new cl_device_id[NBDevices];

  status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, NBDevices, devices, NULL);
  if (status != CL_SUCCESS)
  {

    return status;
  }

  for (int i = 0; i < NBDeviceToUse; i++)
  {
    bool extensionSupported = CheckDGMAExtension(devices[i]);
    if (!extensionSupported)
    {
      cout << "cl_amd_bus_addressable_memory is not a supported extension, please turn it on manually on your system either using CCC or aticonfig" << endl;
      exit(EXIT_FAILURE);
    }
  }


  // context properties list - must be terminated with 0
  properties[0] = CL_CONTEXT_PLATFORM;
  properties[1] = (cl_context_properties)platform;
  properties[2] = 0;

  // create a context with the FIRST GPU device
  context = clCreateContext(properties, NBDeviceToUse, devices, NULL, NULL, &status);
  if (status != CL_SUCCESS)
  {

    return status;
  }


  //cl_queue_properties QueueProp[] = { CL_QUEUE_PROPERTIES, CL_QUEUE_PROFILING_ENABLE, 0 };
  for (int i = 0; i<NBDeviceToUse; i++)
  {
    CheckTopology(devices[i], i);
    queue [i]= clCreateCommandQueueWithProperties(context, devices[i], NULL, &status);
    check_err(status, "clCreateCommandQueueWithProperties", &context);

  }

  delete[]devices;


  return status;
}


int CreateLocalBuffer(cl_context ctx, cl_command_queue queue, cl_mem& origin, unsigned char* data)
{
  cl_int error = 0;
  origin = clCreateBuffer(ctx, CL_MEM_READ_WRITE, DATASIZE, NULL, &error);
  check_err(error, "clCreateBuffer local", &ctx);
  error = clEnqueueWriteBuffer(queue, origin, CL_TRUE, 0, DATASIZE, data, 0, NULL, NULL);
  check_err(error, "clEnqueueWriteBuffer output", &ctx);

  return error;
}

int CreateBufferAddressable(cl_context ctx, cl_mem& addressbus, cl_command_queue queue, cl_bus_address_amd&     m_pBusAddresses)
{
  cl_int error = 0;
  addressbus = clCreateBuffer(ctx, CL_MEM_BUS_ADDRESSABLE_AMD, DATASIZE, NULL, &error);
  check_err(error, "clCreateBuffer CL_MEM_BUS_ADDRESSABLE_AMD", &ctx);

  error = clEnqueueMakeBuffersResidentAMD(queue, 1, &addressbus, CL_TRUE, &m_pBusAddresses, 0, NULL, NULL);
  check_err(error, "clEnqueueMakeBuffersResidentAMD output", &ctx);

  return 0;
}

int CreateBufferRemote(cl_context ctx, cl_mem& remote, cl_command_queue queue, cl_bus_address_amd&  RemoteBusAddresses, cl_ulong& markerOffset)
{
  cl_int error = 0;
  cl_bus_address_amd temp;
  markerOffset = RemoteBusAddresses.marker_bus_address & 0xfff;

  temp.marker_bus_address = RemoteBusAddresses.marker_bus_address &~0xfff;

  temp.surface_bus_address = RemoteBusAddresses.surface_bus_address;
  remote = clCreateBuffer(ctx, CL_MEM_EXTERNAL_PHYSICAL_AMD, DATASIZE, &temp, &error);
  check_err(error, "clCreateBuffer CL_MEM_EXTERNAL_PHYSICAL_AMD", &ctx);


  error = clEnqueueMigrateMemObjects(queue, 1, &remote, 0, 0, NULL, NULL);
  check_err(error, "clEnqueueMigrateMemObjects", &ctx);


  return 0;
}



int main(int argc, char *argv[])
{
  cl_int error = 0;
  cl_context ctx = NULL;
  cl_command_queue queue[2] = { NULL, NULL };
  int ret = 0;

  cl_mem origin;
  cl_mem remote;
  cl_mem addressbus;
  cl_bus_address_amd     BusAddresses ;
  cl_ulong              MarkerOffsets;

  InitCL(ctx, queue);

  unsigned char* data = new unsigned char[DATASIZE];
  unsigned char* output = new unsigned char[DATASIZE];
  if (!data || !output)
  {
    cout << "can't allocate data on host" << endl;
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < DATASIZE; i++)
  {
    data[i] = i % 255;
    output[i] = (i + 1) % 255;
  }

  CreateLocalBuffer(ctx, queue[0], origin, data);

  CreateBufferAddressable(ctx, addressbus, queue[1], BusAddresses);
  clEnqueueWriteBuffer(queue[1], addressbus, CL_TRUE, 0, DATASIZE, output, 0, NULL, NULL);
  check_err(error, "clEnqueueWriteBuffer", &ctx);

  CreateBufferRemote(ctx, remote, queue[0], BusAddresses, MarkerOffsets);


  cl_event copy;
  error = clEnqueueCopyBuffer(queue[0], origin, remote, 0, 0, DATASIZE, 0, NULL, NULL);
  check_err(error, "clEnqueueCopyBuffer", &ctx);

  //for each transfer markerid needs to be different and can only be positive. It has to be incremented by 1 for each new transfer.
  //need to start at 0 
  cl_uint markerID = 0;
  error = clEnqueueWriteSignalAMD(queue[0], remote, markerID, MarkerOffsets, 0, NULL, &copy);
  check_err(error, "clEnqueueWriteSignalAMD", &ctx);

  clFlush(queue[0]);


  error = clEnqueueWaitSignalAMD(queue[1], addressbus, markerID, 1, &copy, NULL);
  check_err(error, "clEnqueueWaitSignalAMD", &ctx);
  
  clFinish(queue[1]);

  error = clEnqueueReadBuffer(queue[1], addressbus, CL_TRUE, 0, DATASIZE, output, 0, NULL, NULL);
  check_err(error, "clEnqueueReadBuffer", &ctx);

  int success = 1;
  std::ofstream outputfile;
  outputfile.open("log.txt");
  for (int i = 0; i < DATASIZE; i++)
  {
    if (data[i] != output[i])
    {
      outputfile << "DGMA Error at index   input data output data difference" << endl;
      outputfile << i << "  " << +data[i] << "  " << +output[i] << "  " << +(data[i]-output[i]) <<endl;
      
      success = 0;
    }
  }

  outputfile.close();
  if (success)
    cout << "DGMA transfer successful" << endl;
  else 
    cout << "DGMA transfer failed, see log.txt for more information" << endl;


  delete[] data;
  delete[] output;
  clReleaseEvent(copy);
  clReleaseMemObject(origin);
  clReleaseMemObject(remote);
  clReleaseMemObject(addressbus);
  clReleaseCommandQueue(queue[0]);
  clReleaseCommandQueue(queue[1]);
  clReleaseContext(ctx);


  return 0;
}
