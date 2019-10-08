#include <iostream>
#include <fastrtps/participant/Participant.h>
#include <fastrtps/Domain.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/PublisherAttributes.h>
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

	cout<<"end of pub"<<endl;
	return 0;
}
