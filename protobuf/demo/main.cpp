#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

//#include "SDPath.pb.h"
//#include "routing/routingResponse.pb.h"

#include "testoneof.pb.h"
#include "testChinese.pb.h"
#include "addressbook.pb.h"
#include "person.pb.h"
#include "routingResponseSource/routingResponse.pb.h"

#include <google/protobuf/util/json_util.h>

using namespace std;

void listPerson(const AddressBook& addressBook)
{
	for (int i = 0; i < addressBook.person_size(); i++)
	{
		const Person& person = addressBook.person(i);

		cout << "name: " << person.name() << endl;
		cout << "id: " << person.id() << endl;
		cout << "email: " << person.email() << endl;

		for (int j = 0; j < person.phonenumber_size(); j++)
		{
			const Person::PhoneNumber& phoneNumber = person.phonenumber(j);

			cout << "phoneNumber: " << phoneNumber.number() << endl;
			cout << "phoneType: " << phoneNumber.type() << endl;
		}
	}
}

void testPerson()
{
	AddressBook addressBook;
	Person* person = addressBook.add_person();

	person->set_name("liudehua");
	person->set_id(11);
	person->set_email("liudehua@qq.com");
	Person::PhoneNumber* phoneNumber = person->add_phonenumber();
	phoneNumber->set_number("111111222222");
	phoneNumber->set_type(Person::MOBILE);
	phoneNumber = person->add_phonenumber();
	phoneNumber->set_number("222222333333");
	phoneNumber->set_type(Person::HOME);

	Person* person1 = addressBook.add_person();
	person1->set_name("zhangxueyou");
	person1->set_id(22);
	person1->set_email("zhangxueyou@qq.com");
	Person::PhoneNumber* phoneNumber1 = person1->add_phonenumber();
	phoneNumber1->set_number("666666777777");
	phoneNumber1->set_type(Person::WORK);

	// serialize to stream
	fstream fileOut("personDb.txt", ios::out | ios::trunc | ios::binary);
	addressBook.SerializePartialToOstream(&fileOut);
	fileOut.close();

	// serialize to string
	string originStr;
	addressBook.SerializeToString(&originStr);
	cout << originStr << endl;

	// serialize to array
	char array[1024];
	addressBook.SerializeToArray(array, addressBook.ByteSize());
	cout << array << endl;

	// write To test.json
	fstream testOut("test.json", ios::out | ios::trunc | ios::binary);
	testOut << originStr;
	testOut.close();

	// convert string to vector<uchar>
	std::vector<unsigned char> inputUcharStream;
	inputUcharStream.assign(originStr.begin(), originStr.end());
	for (auto &i : inputUcharStream)
	{
		cout << i;
	}
	cout << endl;
	cout << "#############################" << endl;

	// parse stream
	fstream fileIn("personDb.txt", ios::in | ios::binary);
	AddressBook addressBookFromStream;
	addressBookFromStream.ParseFromIstream(&fileIn);
	listPerson(addressBookFromStream);
	cout << "-----------------------------" << endl;

	// parse string
	AddressBook addressBookFromString;
	addressBookFromString.ParseFromString(originStr);
	listPerson(addressBookFromString);
	cout << "*****************************" << endl;

	// parse array
	AddressBook addressBookFromArray;
	addressBookFromArray.ParseFromArray(array, addressBook.ByteSize());
	listPerson(addressBookFromArray);
	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;

	// read from test.json
	AddressBook addressBookFromTestJson;
	fstream testIn("test.json", ios::in | ios::binary);
	ostringstream a;
	a << testIn.rdbuf();
	string b = a.str();
	cout << b << endl;
	addressBookFromTestJson.ParseFromString(b);
	//addressBookFromTestJson.ParseFromIstream(&testIn);
	listPerson(addressBookFromTestJson);
	cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;

	// parse vector<uchar>
	AddressBook addressBookFromucharStream;
	string outUcharStream;
	outUcharStream.assign(inputUcharStream.begin(), inputUcharStream.end());
	cout << outUcharStream << endl;
	//addressBookFromucharStream.ParseFromArray(&inputUcharStream, inputUcharStream.size());
	addressBookFromucharStream.ParseFromString(outUcharStream);
	listPerson(addressBookFromucharStream);
}

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

	// SerializeToString
	string outputPartialString;
	address_book.SerializePartialToString(&outputPartialString);
	cout << outputPartialString << endl;

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

	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	{
		// Parse from string
		tutorial::AddressBook addressBookFromString;
		addressBookFromString.ParsePartialFromString(outputPartialString);

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
	cout << "---------------------------" << endl;

	{
		// parseFromArray use string
		tutorial::AddressBook addressBookFromArray;
		cout << addressBookFromArray.ParseFromArray(outputString.c_str(), outputString.size()) << endl;
		listAddressBook(addressBookFromArray);
		cout << addressBookFromArray.DebugString() << endl;
	}
	cout << "---------------------------" << endl;
	{
		// parseFromArray use string
		tutorial::AddressBook addressBookFromArray;
		cout << addressBookFromArray.ParseFromArray(outputPartialString.c_str(), outputPartialString.size()) << endl;
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

void testRoutingResponse()
{
	ncProtocol::RoutingResponse routingResponse;

	// read from test.dat
	fstream testIn("test.dat", ios::in | ios::binary);
	ostringstream a;
	a << testIn.rdbuf();
	string b = a.str();
	cout << b << endl;
}

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
	//testPerson();
	//testRoutingResponse();

    return 0;
}

