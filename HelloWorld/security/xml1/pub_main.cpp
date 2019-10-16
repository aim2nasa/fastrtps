#include <iostream>
#include <fastrtps/participant/Participant.h>
#include <fastrtps/Domain.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/publisher/Publisher.h>
#include "gen/HelloWorldPubSubTypes.h"

#ifdef SECURITY
#include <fastrtps/xmlparser/XMLProfileManager.h>
#endif

using namespace std;

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	eprosima::fastrtps::Participant* pParticipant = NULL;
#ifdef SECURITY
	std::cout<<"Security ON"<<std::endl;
	eprosima::fastrtps::xmlparser::XMLProfileManager::loadXMLFile("secureProfile_pub.xml");
	std::string participant_profile_name = "secure_participant_conf_for_publisher";
	pParticipant = eprosima::fastrtps::Domain::createParticipant(participant_profile_name);
#endif
	assert(pParticipant!=NULL);

	HelloWorldPubSubType type;
	eprosima::fastrtps::Domain::registerType(pParticipant,&type);

	eprosima::fastrtps::PublisherAttributes WParam;
	WParam.topic.topicDataType = "HelloWorld";
	WParam.topic.topicName = "HelloWorldTopic";

	eprosima::fastrtps::Publisher* pPublisher 
		= eprosima::fastrtps::Domain::createPublisher(pParticipant,WParam);
	assert(pPublisher!=NULL);

	bool b;

	HelloWorld hello;
	hello.msg("HelloWorld");
	for(int i=0;i<10;i++)
	{
		b = pPublisher->write((void*)&hello);
		if(b) {
			std::cout<<".";
			std::fflush(stdout);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	b = eprosima::fastrtps::Domain::removePublisher(pPublisher);
	assert(b==true);
	b = eprosima::fastrtps::Domain::removeParticipant(pParticipant);
	assert(b==true);

	cout<<"end of pub"<<endl;
	return 0;
}
