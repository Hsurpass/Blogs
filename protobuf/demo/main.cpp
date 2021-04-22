#include <iostream>
#include <string>
#include <fstream>
#include "addressbook.pb.h"

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

int main(int argc, char *argv[])
{
    cout << GOOGLE_PROTOBUF_VERSION << endl;
    cout << GOOGLE_PROTOBUF_MIN_LIBRARY_VERSION << endl;
    cout << GOOGLE_PROTOBUF_MIN_PROTOC_VERSION << endl;

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 2)
    {
        cerr << "Ueage: " << argv[0] << "FILE" << endl;
    }


    tutorial::AddressBook address_book;

    // Add an address.
    PromptForAddress(address_book.add_people());

    string outputString;
    address_book.SerializeToString(&outputString);
    cout << outputString << endl;

    {
        // Write the new address book back to dish.
        fstream output(argv[1], ios::out | ios::trunc | ios::binary);
        if (!address_book.SerializeToOstream(&output))
        {
            cerr << "Failed to write address book." << endl;
            return -1;
        }
        output.close();
    }
    

    cout << "---------------------------" << endl;

    // Parse from string
    tutorial::AddressBook parseAddress;
    parseAddress.ParseFromString(outputString);
    
    listAddressBook(parseAddress);

    {
        // parse from stream
        tutorial::AddressBook parseAddressfromStream;
        fstream input(argv[1], ios::in | ios::binary);
        if (!parseAddressfromStream.ParseFromIstream(&input))
        {
            cerr << "parse from stream error." << endl;
            return -1;
        }
        listAddressBook(parseAddressfromStream);
        input.close();
    }



    // Optional: Delete all global objects allocates by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}