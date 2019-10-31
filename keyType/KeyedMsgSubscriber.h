#ifndef __KEYEDMSGSUBSCRIBER_H__
#define __KEYEDMSGSUBSCRIBER_H__

#include "KeyedMsgPubSubTypes.h"

#include <fastrtps/fastrtps_fwd.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastrtps/subscriber/SubscriberListener.h>
#include <fastrtps/subscriber/SampleInfo.h>

#include "KeyedMsg.h"

class KeyedMsgSubscriber {
public:
	KeyedMsgSubscriber();
	virtual ~KeyedMsgSubscriber();
	bool init();
	void run();

private:
	KeyedMsgPubSubType m_type;
	eprosima::fastrtps::Participant* mp_participant;
	eprosima::fastrtps::Subscriber* mp_subscriber;

	class SubListener:public eprosima::fastrtps::SubscriberListener
	{
	public:
		SubListener():n_matched(0){};
		~SubListener(){};
		void onSubscriptionMatched(eprosima::fastrtps::Subscriber* sub, eprosima::fastrtps::rtps::MatchingInfo& info);
		void onNewDataMessage(eprosima::fastrtps::Subscriber* sub);

		int n_matched;
	}m_listener;
};

#endif
