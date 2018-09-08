#define BOOST_DATE_TIME_NO_LIB
//#define BOOST_INTERPROCESS_WINDOWS

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>

int main()
{
	using namespace boost::interprocess;

	//Open already created shared memory object.
	shared_memory_object shm(open_only, "shared_memory", read_only);

	//Map the whole shared memory in this process
	mapped_region region(shm, read_only);

	//Check that memory was initialized to 1
	unsigned char *ch = (unsigned char *)region.get_address();
	//region.get_page_size
	for (std::size_t i = 0; i < region.get_size(); i++) 
	{
		// Check Data
		if (ch[i] != 1) 
		{
			std::cout << "shared mem data not match in byte num:"<< i <<"\n";
			system("PAUSE");
			break;
		}
	}

	std::cout << "client process end \n";
	system("PAUSE");

	return 0;
}