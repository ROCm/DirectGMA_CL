# DirectGMA_CL
Simple example showing how to use DGMA in OpenCL

----------------
System Setup
----------------

Your system needs 2 AMD GPUs with the DirectGMA feature, and the latest GPU driver.
Plug at least 1 monitor on each GPU.

-----------------
Enable DirectGMA
-----------------

Before running your DirectGMA samples, you have to make sure that the DirectGMA feature is enabled:

on Windows: 
AMD Firepro Control Center -> AMD Firepro -> SDI/DirectGMA -> Check the checkbox of the 2 GPU -> Apply -> Restart your computer.

on Linux:
in your terminal, enter the commands :
>  aticonfig --initial=dual-head --adapter=all -f
>  aticonfig --set-pcs-val=MCIL,DMAOGLExtensionApertureMB,96
>  aticonfig --set-pcs-u32=KERNEL,InitialPhysicalUswcUsageSize,96
and reboot.

-----------------
Prerequisites:
-----------------

cmake 2.8.12 or higher
AMD APP SDK 2.9.1 or higher

-----------------
Building procedure:
-----------------

create a build directory
cd build
cmake Path_to_the_src_directory
make (Linux) compile the Project.sln project with Visual Studio (Windows)
