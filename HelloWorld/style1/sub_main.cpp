#include <iostream>
#include <fastrtps/participant/Participant.h>
#include <fastrtps/Domain.h>
#include <fastrtps/attributes/ParticipantAttributes.h>

using namespace std;

int main(int argc, char** argv)
{
	eprosima::fastrtps::ParticipantAttributes PParam;
	eprosima::fastrtps::Participant* pParticipant = eprosima::fastrtps::Domain::createParticipant(PParam);
	assert(pParticipant!=NULL);

	cout<<"end of sub"<<endl;
	return 0;
}
