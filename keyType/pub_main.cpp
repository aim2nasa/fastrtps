#include <iostream>
#include "KeyedMsgPublisher.h"

using namespace std;

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	KeyedMsgPublisher pub;
	if(!pub.init()) {
		std::cout<<"init failed"<<std::endl;
		return -1;
	}
	pub.run(1000);
	std::cout<<"publisher end"<<std::endl;
	return 0;
}
