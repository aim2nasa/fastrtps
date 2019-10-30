#ifndef __KEYEDMSGPUBLISHER_H__
#define __KEYEDMSGPUBLISHER_H__

#include "KeyedMsgPubSubTypes.h"

#include <fastrtps/fastrtps_fwd.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/publisher/PublisherListener.h>


#include "KeyedMsg.h"

class KeyedMsgPublisher {
public:
	KeyedMsgPublisher();
	virtual ~KeyedMsgPublisher();
	bool init();
	void run(uint32_t sleep);

private:
	KeyedMsg m_keyedMsg;
	KeyedMsgPubSubType m_type;
	eprosima::fastrtps::Participant* mp_participant;
	eprosima::fastrtps::Publisher* mp_publisher;
	void runThread(uint32_t sleep);

	class PubListener:public eprosima::fastrtps::PublisherListener
	{
	public:
		PubListener():n_matched(0){};
		~PubListener(){};
		void onPublicationMatched(eprosima::fastrtps::Publisher* pub, eprosima::fastrtps::rtps::MatchingInfo& info);
		int n_matched;
	}m_listener;
};

#endif
