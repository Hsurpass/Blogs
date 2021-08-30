#pragma once

#include <iostream>
#include <string>
#include <fstream>
//#include "SDPath.pb.h"
#include "testoneof.pb.h"
//#include "routing/routingResponse.pb.h"
#include "testChinese.pb.h"
#include "addressbook.pb.h"

#include <google/protobuf/util/json_util.h>

using namespace std;

void PromptForAddress(tutorial::Person* person)
{
	cout << "Enter Person ID number: ";
	int id;
	cin >> id;
	person->set_id(id);
	cin.ignore(256, '\n');

	cout << "Enter name: ";
	getline(cin, *person->mutable_name());

	cout << "Enter email address (blank for none): ";
	string email;
	getline(cin, email);
	if (!email.empty())
	{
		person->set_email(email);
	}

	while (true)
	{
		cout << "Enter a phone number (or leave blank to finish): ";
		string number;
		getline(cin, number);
		if (number.empty())
		{
			break;
		}

		tutorial::Person::PhoneNumber* phone_number = person->add_phones();
		phone_number->set_number(number);

		cout << "Is this a mobile, home, or work phone?";
		string type;
		getline(cin, type);
		if (type == "mobile")
		{
			phone_number->set_type(tutorial::Person::MOBILE);
		}
		else if (type == "home")
		{
			phone_number->set_type(tutorial::Person::HOME);
		}
		else if (type == "work")
		{
			phone_number->set_type(tutorial::Person::WORK);
		}
		else{
			cout << "Unkown phone type.Using default." << endl;
		}
	}
}

void listAddressBook(const tutorial::AddressBook& addressBook)
{
	for (int i = 0; i < addressBook.people_size(); i++)
	{
		const tutorial::Person& people = addressBook.people(i);

		cout << "name:" << people.name() << endl;
		cout << "id:" << people.id() << endl;
		cout << "email: " << people.email() << endl;

		for (int j = 0; j < people.phones_size(); j++)
		{
			const tutorial::Person::PhoneNumber& phone_number = people.phones(j);

			cout << "phone number: " << phone_number.number() << endl;
			cout << "phone type: " << phone_number.type() << endl;
		}
	}
}

bool testAddressbook()
{
	tutorial::AddressBook address_book;

	// Add an address.
	PromptForAddress(address_book.add_people());

	// SerializeToString
	string outputString;
	address_book.SerializeToString(&outputString);
	cout << outputString << endl;

	// SerializeToArray
	char array[1024];
	address_book.SerializeToArray(array, address_book.ByteSize());
	cout << array << endl;

	// SerializeToStream
	{
		// Write the new address book back to dish.
		fstream output("address.binary", ios::out | ios::trunc | ios::binary);
		if (!address_book.SerializeToOstream(&output))
		{
			cerr << "Failed to write address book." << endl;
			return false;
		}
		output.close();
	}

	cout << "---------------------------" << endl;
	{
		// Parse from string
		tutorial::AddressBook addressBookFromString;
		addressBookFromString.ParseFromString(outputString);

		listAddressBook(addressBookFromString);
	}

	cout << "########################" << endl;
	{
		// parse from stream
		tutorial::AddressBook addressBookFromStream;
		fstream input("address.binary", ios::in | ios::binary);
		if (!addressBookFromStream.ParseFromIstream(&input))
		{
			cerr << "parse from stream error." << endl;
			return false;
		}
		listAddressBook(addressBookFromStream);
		input.close();
	}

	cout << "***********************" << endl;

	{
		// parse from Array
		tutorial::AddressBook addressBookFromArray;
		addressBookFromArray.ParseFromArray(array, address_book.ByteSize());
		listAddressBook(addressBookFromArray);
		cout << addressBookFromArray.DebugString() << endl;
	}

	// Optional: Delete all global objects allocates by libprotobuf.
	google::protobuf::ShutdownProtobufLibrary();

	return true;
}

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
	//fstream file(;

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
	//testOneOf();
	//testChinese();
	testAddressbook();
    return 0;
}

