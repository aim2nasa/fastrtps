#include <iostream>
#include <fastrtps/participant/Participant.h>
#include <fastrtps/Domain.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastrtps/subscriber/SubscriberListener.h>
#include <fastrtps/subscriber/SampleInfo.h>
#include <fastrtps/subscriber/Subscriber.h>
#include "gen/HelloWorldPubSubTypes.h"

#ifdef SECURITY
#include <fastrtps/xmlparser/XMLProfileManager.h>
#endif

using namespace std;

class listener:public eprosima::fastrtps::SubscriberListener{
public:
	listener():nCount_(0){}
	~listener(){}

	int nCount_;
	eprosima::fastrtps::SampleInfo_t info_;

	void onSubscriptionMatched(eprosima::fastrtps::Subscriber* sub, eprosima::fastrtps::rtps::MatchingInfo& info);
	void onNewDataMessage(eprosima::fastrtps::Subscriber* sub);
};
void listener::onSubscriptionMatched(eprosima::fastrtps::Subscriber* sub, eprosima::fastrtps::rtps::MatchingInfo& info)
{
	(void)sub;

	if(info.status==eprosima::fastrtps::rtps::MATCHED_MATCHING)
	{
		std::cout<<"Subscriber matched"<<std::endl;
	}
	else
	{
		std::cout<<"Subscriber unmatched"<<std::endl;
	}
}

void listener::onNewDataMessage(eprosima::fastrtps::Subscriber* sub)
{
	HelloWorld st;
	if(sub->takeNextData(&st,&info_))
	{
		if(info_.sampleKind == eprosima::fastrtps::rtps::ALIVE)
		{
			std::cout<<"Message="<<st.msg()<<std::endl;
		}
	}
}

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	eprosima::fastrtps::Participant* pParticipant = NULL;
#ifdef SECURITY
	std::cout<<"Security ON"<<std::endl;
	eprosima::fastrtps::xmlparser::XMLProfileManager::loadXMLFile("secureProfile_sub.xml");
	std::string participant_profile_name = "secure_participant_conf_for_subscriber";
	pParticipant = eprosima::fastrtps::Domain::createParticipant(participant_profile_name);
#endif
	assert(pParticipant!=NULL);

	HelloWorldPubSubType type;
	eprosima::fastrtps::Domain::registerType(pParticipant,&type);

	eprosima::fastrtps::SubscriberAttributes RParam;
	RParam.topic.topicDataType = "HelloWorld";
	RParam.topic.topicName = "HelloWorldTopic";

	listener ls;
	eprosima::fastrtps::Subscriber* pSubscriber
		= eprosima::fastrtps::Domain::createSubscriber(pParticipant,RParam,(eprosima::fastrtps::SubscriberListener*)&ls);
	assert(pSubscriber!=NULL);

	while(ls.nCount_==0) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout<<".";
		std::fflush(stdout);
	}

	bool b;
	b = eprosima::fastrtps::Domain::removeSubscriber(pSubscriber);
	assert(b==true);
	b = eprosima::fastrtps::Domain::removeParticipant(pParticipant);
	assert(b==true);

	cout<<"end of sub"<<endl;
	return 0;
}