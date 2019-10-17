#include <iostream>
#include <fastrtps/participant/Participant.h>
#include <fastrtps/Domain.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/publisher/Publisher.h>
#include "gen/HelloWorldPubSubTypes.h"
#include <fastrtps/publisher/PublisherListener.h>
#include <fastrtps/qos/QosPolicies.h>

#ifdef SECURITY
#include <fastrtps/rtps/attributes/PropertyPolicy.h>
#endif

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
#ifdef SECURITY
	std::cout<<"Security ON"<<std::endl;
	eprosima::fastrtps::rtps::PropertyPolicy participant_property_policy;
	participant_property_policy.properties().emplace_back("dds.sec.auth.plugin","builtin.PKI-DH");
	participant_property_policy.properties().emplace_back("dds.sec.auth.builtin.PKI-DH.identity_ca","file://../certs/mainCaCert.pem");
	participant_property_policy.properties().emplace_back("dds.sec.auth.builtin.PKI-DH.identity_certificate","file://../certs/pubCert.pem");
	participant_property_policy.properties().emplace_back("dds.sec.auth.builtin.PKI-DH.private_key","file://../certs/pubKey.pem");
	participant_property_policy.properties().emplace_back(eprosima::fastrtps::rtps::Property("dds.sec.access.plugin","builtin.Access-Permissions"));
	participant_property_policy.properties().emplace_back(eprosima::fastrtps::rtps::Property("dds.sec.access.builtin.Access-Permissions.permissions_ca","file://../certs/mainCaCert.pem"));
	participant_property_policy.properties().emplace_back(eprosima::fastrtps::rtps::Property("dds.sec.access.builtin.Access-Permissions.governance","file://../certs/governance.smime"));
	participant_property_policy.properties().emplace_back(eprosima::fastrtps::rtps::Property("dds.sec.access.builtin.Access-Permissions.permissions","file://../certs/permissions.smime"));
	participant_property_policy.properties().emplace_back("dds.sec.crypto.plugin","builtin.AES-GCM-GMAC");
	participant_property_policy.properties().emplace_back("rtps.participant.rtps_protection_kind","ENCRYPT");

	PParam.rtps.properties = participant_property_policy;
#endif
	eprosima::fastrtps::Participant* pParticipant = eprosima::fastrtps::Domain::createParticipant(PParam);
	assert(pParticipant!=NULL);

	HelloWorldPubSubType type;
	eprosima::fastrtps::Domain::registerType(pParticipant,&type);

	eprosima::fastrtps::PublisherAttributes WParam;
	WParam.topic.topicDataType = "HelloWorld";
	WParam.topic.topicName = "HelloWorldTopic";
	WParam.qos.m_reliability.kind = eprosima::fastrtps::RELIABLE_RELIABILITY_QOS;

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
