#include <iostream>
#include <fastrtps/participant/Participant.h>
#include <fastrtps/Domain.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include "gen/HelloWorldPubSubTypes.h"

using namespace std;

int main(int argc, char** argv)
{
	eprosima::fastrtps::ParticipantAttributes PParam;
	eprosima::fastrtps::Participant* pParticipant = eprosima::fastrtps::Domain::createParticipant(PParam);
	assert(pParticipant!=NULL);

	HelloWorldPubSubType type;
	eprosima::fastrtps::Domain::registerType(pParticipant,&type);

	eprosima::fastrtps::SubscriberAttributes RParam;
	RParam.topic.topicDataType = "HelloWorld";

	eprosima::fastrtps::Subscriber* pSubscriber
		= eprosima::fastrtps::Domain::createSubscriber(pParticipant,RParam);
	assert(pSubscriber!=NULL);

	bool b;
	b = eprosima::fastrtps::Domain::removeSubscriber(pSubscriber);
	assert(b==true);
	b = eprosima::fastrtps::Domain::removeParticipant(pParticipant);
	assert(b==true);

	cout<<"end of sub"<<endl;
	return 0;
}
