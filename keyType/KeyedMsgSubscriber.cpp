#include "KeyedMsgSubscriber.h"
#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastrtps/subscriber/Subscriber.h>
#include <fastrtps/Domain.h>

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;

KeyedMsgSubscriber::KeyedMsgSubscriber()
    : mp_participant(nullptr)
    , mp_subscriber(nullptr)
{
}

bool KeyedMsgSubscriber::init()
{
    ParticipantAttributes PParam;
    mp_participant = Domain::createParticipant(PParam);
    if(mp_participant==nullptr) return false;

    Domain::registerType(mp_participant,&m_type);

    SubscriberAttributes Rparam;
    Rparam.topic.topicKind = WITH_KEY;
    Rparam.topic.topicDataType = "KeyedMsg";
    Rparam.topic.topicName = "KeyedMsgTopic";
    Rparam.qos.m_reliability.kind = RELIABLE_RELIABILITY_QOS;
    mp_subscriber = Domain::createSubscriber(mp_participant,Rparam,(SubscriberListener*)&m_listener);
    if(mp_subscriber == nullptr) return false;

    return true;
}

KeyedMsgSubscriber::~KeyedMsgSubscriber()
{
    Domain::removeParticipant(mp_participant);
}

void KeyedMsgSubscriber::SubListener::onSubscriptionMatched(Subscriber* /*sub*/,MatchingInfo& info)
{
    if(info.status == MATCHED_MATCHING)
    {
        n_matched++;
        std::cout << "Subscriber matched"<<std::endl;
    }
    else
    {
        n_matched--;
        std::cout << "Subscriber unmatched"<<std::endl;
    }
}

void KeyedMsgSubscriber::SubListener::onNewDataMessage(Subscriber* sub)
{
	KeyedMsg kmsg;
	eprosima::fastrtps::SampleInfo_t info;

	if(sub->takeNextData(&kmsg,&info)) {
		if(info.sampleKind==ALIVE) {
			std::cout << "id:"<<kmsg.id()<< ",msg:"<< kmsg.msg()<<std::endl;
		}
	}
}

void KeyedMsgSubscriber::run()
{
    std::cout << "Subscriber running. Please press enter to stop the Subscriber" << std::endl;
    std::cin.ignore();
}
