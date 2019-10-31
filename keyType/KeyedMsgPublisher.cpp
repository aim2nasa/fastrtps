#include "KeyedMsgPublisher.h"
#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/publisher/Publisher.h>
#include <fastrtps/Domain.h>
#include <thread>

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;

KeyedMsgPublisher::KeyedMsgPublisher()
    : mp_participant(nullptr)
    , mp_publisher(nullptr)
{
}

bool KeyedMsgPublisher::init()
{
    m_keyedMsg.id(0);
    m_keyedMsg.msg("This is keyed msg");

    ParticipantAttributes PParam;
    mp_participant = Domain::createParticipant(PParam);
    if(mp_participant==nullptr) return false;

    Domain::registerType(mp_participant,&m_type);

    PublisherAttributes Wparam;
    Wparam.topic.topicKind = WITH_KEY;
    Wparam.topic.topicDataType = "KeyedMsg";
    Wparam.topic.topicName = "KeyedMsgTopic";
    Wparam.qos.m_reliability.kind = RELIABLE_RELIABILITY_QOS;
    mp_publisher = Domain::createPublisher(mp_participant,Wparam,(PublisherListener*)&m_listener);
    if(mp_publisher == nullptr) return false;

    return true;
}

KeyedMsgPublisher::~KeyedMsgPublisher()
{
    Domain::removeParticipant(mp_participant);
}

void KeyedMsgPublisher::PubListener::onPublicationMatched(Publisher* /*pub*/,MatchingInfo& info)
{
    if(info.status == MATCHED_MATCHING)
    {
        n_matched++;
        std::cout << "Publisher matched"<<std::endl;
    }
    else
    {
        n_matched--;
        std::cout << "Publisher unmatched"<<std::endl;
    }
}

void KeyedMsgPublisher::runThread(uint32_t sleep)
{
	while(1){
		std::condition_variable cv_;
    	m_keyedMsg.id(m_keyedMsg.id()+1);
        if(mp_publisher->write((void*)&m_keyedMsg)){
			std::cout << "id:"<<m_keyedMsg.id()<< ",msg:"<< m_keyedMsg.msg()<<std::endl;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
	}
}

void KeyedMsgPublisher::run(uint32_t sleep)
{
    std::thread thread(&KeyedMsgPublisher::runThread, this, sleep);
    thread.join();
}
