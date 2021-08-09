#include <iostream>

//#include "SDPath.pb.h"
#include "testoneof.pb.h"
#include "routing/routingResponse.pb.h"

using namespace std;

void testOneOf()
{
	SampleMessage sampleMessage;
	sampleMessage.set_name("abc");
	sampleMessage.set_number(100);
	Result* mutableResult = sampleMessage.mutable_result();
	mutableResult->set_url("url");
	mutableResult->set_title(200);
	mutableResult->add_snippets("123");
	mutableResult->add_snippets("456");


	cout << sampleMessage.name() << endl;
	cout << sampleMessage.number() << endl;

	Result result = sampleMessage.result();
	cout << result.url() << endl;
	cout << result.title() << endl;
	cout << result.snippets_size() << endl;
	cout << result.snippets(0) << endl;
	cout << result.snippets(1) << endl;

}

void testRoutingResponse()
{
	ncProtocol::RoutingResponse routingResponse;
	//routingResponse.
}

int main()
{
	testOneOf();
    return 0;
}

