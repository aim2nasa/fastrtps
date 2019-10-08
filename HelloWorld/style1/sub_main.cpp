#include <iostream>
#include <fastrtps/participant/Participant.h>
#include <fastrtps/Domain.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastrtps/subscriber/SubscriberListener.h>
#include "gen/HelloWorldPubSubTypes.h"

using namespace std;

class listener:public eprosima::fastrtps::SubscriberListener{
public:
	listener():nCount_(0){}
	~listener(){}

	int nCount_;

	void onSubscriptionMatched(eprosima::fastrtps::Subscriber* sub, eprosima::fastrtps::rtps::MatchingInfo& info);
	void onNewDataMessage(eprosima::fastrtps::Subscriber* sub);
};
void listener::onSubscriptionMatched(eprosima::fastrtps::Subscriber* sub, eprosima::fastrtps::rtps::MatchingInfo& info)
{
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
	std::cout<<"onNewDataMessage"<<std::endl;
}

int main(int argc, char** argv)
{
	eprosima::fastrtps::ParticipantAttributes PParam;
	eprosima::fastrtps::Participant* pParticipant = eprosima::fastrtps::Domain::createParticipant(PParam);
	assert(pParticipant!=NULL);

	HelloWorldPubSubType type;
	eprosima::fastrtps::Domain::registerType(pParticipant,&type);

	eprosima::fastrtps::SubscriberAttributes RParam;
	RParam.topic.topicDataType = "HelloWorld";

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
