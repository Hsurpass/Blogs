#pragma once

#include <iostream>
#include <fstream>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/util/json_util.h>

//#include "SDPath.pb.h"
//#include "routing/routingResponse.pb.h"

#include "testoneof.pb.h"
#include "testChinese.pb.h"

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

//void testRoutingResponse()
//{
//	ncProtocol::RoutingResponse routingResponse;
//	//routingResponse.
//}

void testChinese()
{
	chinese chi;
	chi.set_old(12);
	//chi.set_name("Ð¡Ã÷");
	chi.set_name("abcdefg");
	chi.set_company("¹È¸è");
	chi.set_number(0);
	cout << chi.old() << endl;
	cout << chi.name() << endl;
	cout << chi.company() << endl;
	cout << chi.number() << endl;
	printf("%s\n", chi.company().c_str());

	string str;
	chi.SerializeToString(&str);

	/*char* p = (char*)malloc(chi.ByteSize());
	memset(p, 0, chi.ByteSize());
	chi.SerializeToArray(p, chi.ByteSize());
	string str(p);*/

	chinese result;
	result.ParseFromString(str);
	cout << chi.old() << endl;
	cout << chi.name() << endl;
	cout << chi.company() << endl;
	cout << chi.number() << endl;
	printf("%s\n", chi.company().c_str());

	cout << "------------------------------------" << endl;
	result.PrintDebugString();
	/*cout << result.DebugString() << endl;
	cout << result.ShortDebugString() << endl;
	cout << result.Utf8DebugString() << endl;*/

	cout << "---------pb to json---------" << endl;
	string json_string;
	google::protobuf::util::JsonPrintOptions options;
	options.add_whitespace = true;
	options.always_print_primitive_fields = true;
	google::protobuf::util::MessageToJsonString(chi, &json_string, options);
	cout << json_string << endl;
	ofstream file("test.json", std::ofstream::out | std::ofstream::trunc);
	file << json_string;
	file.close();

	cout << "---------json to pb---------" << endl;
	chinese chi2;
	google::protobuf::util::JsonPrintOptions options2;
	google::protobuf::util::JsonStringToMessage(json_string, &chi2);
	cout << chi.old() << endl;
	cout << chi.name() << endl;
	cout << chi.company() << endl;
	printf("%s\n", chi.company().c_str());


}

int main()
{
	cout << GOOGLE_PROTOBUF_VERSION << endl;
	cout << GOOGLE_PROTOBUF_MIN_LIBRARY_VERSION << endl;
	cout << GOOGLE_PROTOBUF_MIN_PROTOC_VERSION << endl;
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	//testOneOf();
	testChinese();
    return 0;
}

