#include <iostream>
#include "KeyedMsgSubscriber.h"

using namespace std;

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	KeyedMsgSubscriber sub;
	if(!sub.init()) {
		std::cout<<"init failed"<<std::endl;
		return -1;
	}
	sub.run();
	std::cout<<"subscriber end"<<std::endl;
	return 0;
}
