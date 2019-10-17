#include <iostream>
#include <fastrtps/participant/Participant.h>
#include <fastrtps/Domain.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/publisher/Publisher.h>
#include "gen/HelloWorldPubSubTypes.h"
#include <fastrtps/publisher/PublisherListener.h>

using namespace std;

class pubListener:public eprosima::fastrtps::PublisherListener{
public:
	pubListener():match_(false){}
	~pubListener(){}
	void onPublicationMatched(eprosima::fastrtps::Publisher* pub,
							  eprosima::fastrtps::rtps::MatchingInfo& info)
	{
		(void)pub;
		if(info.status==eprosima::fastrtps::rtps::MATCHED_MATCHING){
			match_=true;
			std::cout<<"Publisher matched"<<std::endl;
		}else{
			match_ = false;
			std::cout<<"Publisher unmatched"<<std::endl;
		}
	}
	bool match_;
};

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	eprosima::fastrtps::ParticipantAttributes PParam;
	eprosima::fastrtps::Participant* pParticipant = eprosima::fastrtps::Domain::createParticipant(PParam);
	assert(pParticipant!=NULL);

	HelloWorldPubSubType type;
	eprosima::fastrtps::Domain::registerType(pParticipant,&type);

	eprosima::fastrtps::PublisherAttributes WParam;
	WParam.topic.topicDataType = "HelloWorld";

	pubListener pl;
	eprosima::fastrtps::Publisher* pPublisher 
		= eprosima::fastrtps::Domain::createPublisher(pParticipant,WParam,&pl);
	assert(pPublisher!=NULL);

	HelloWorld hello;
	hello.msg("HelloWorld");

	while(pl.match_==false) std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
	std::cout<<"Matching Waiting done"<<std::endl;
	if(pPublisher->write(&hello)) {
		std::cout<<".";
		std::fflush(stdout);
	}
	std::cin.ignore();

	bool b;
	b = eprosima::fastrtps::Domain::removePublisher(pPublisher);
	assert(b==true);
	b = eprosima::fastrtps::Domain::removeParticipant(pParticipant);
	assert(b==true);

	cout<<"end of pub"<<endl;
	return 0;
}
