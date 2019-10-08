#include <iostream>
#include <fastrtps/participant/Participant.h>
#include <fastrtps/Domain.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/publisher/Publisher.h>
#include "gen/HelloWorldPubSubTypes.h"

using namespace std;

int main(int argc, char** argv)
{
	eprosima::fastrtps::ParticipantAttributes PParam;
	eprosima::fastrtps::Participant* pParticipant = eprosima::fastrtps::Domain::createParticipant(PParam);
	assert(pParticipant!=NULL);

	HelloWorldPubSubType type;
	eprosima::fastrtps::Domain::registerType(pParticipant,&type);

	eprosima::fastrtps::PublisherAttributes WParam;
	WParam.topic.topicDataType = "HelloWorld";

	eprosima::fastrtps::Publisher* pPublisher 
		= eprosima::fastrtps::Domain::createPublisher(pParticipant,WParam);
	assert(pPublisher!=NULL);

	bool b;

	HelloWorld hello;
	hello.msg("HelloWorld");
	for(int i=0;i<10;i++)
	{
		b = pPublisher->write((void*)&hello);
		if(b) std::cout<<".";
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	b = eprosima::fastrtps::Domain::removePublisher(pPublisher);
	assert(b==true);
	b = eprosima::fastrtps::Domain::removeParticipant(pParticipant);
	assert(b==true);

	cout<<"end of pub"<<endl;
	return 0;
}
