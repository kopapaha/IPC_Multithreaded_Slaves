#define BOOST_DATE_TIME_NO_LIB
//#define BOOST_INTERPROCESS_WINDOWS

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include<iostream>

int main() 
{
	using namespace boost::interprocess;

	//shared_memory_object shm_obj
	//(create_only,                  //only create
	//	, "shared_memory"              //name
	//	, read_write                   //read-write mode
	//);

	// Open
	shared_memory_object shm_obj(create_only, "shared_memory", read_write);

	// Allocate mem
	shm_obj.truncate(10000);

	// Once created or opened, a process just has to map the shared memory object in the process' address space. The user can map the whole shared memory or just part of its
	std::size_t mm_size = 1000; // mmaped memory size
	mapped_region region(shm_obj, read_write, 0, mm_size);

	// Get the address of the mapped object
	void * regionUserAddress = region.get_address();

	//Get the size of the region
	std::size_t regionSize = region.get_size();

	std::cout << "Size of memory mapped: " << regionSize << "Bytes?\n";
	// Set region to 1
	std::memset(regionUserAddress, 1, regionSize);

	std::cout << "enter to remove shared memory \n";
	system("PAUSE");

	// Close
	shared_memory_object::remove("shared_memory");


	return 0;
}