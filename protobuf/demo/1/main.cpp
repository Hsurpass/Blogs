#include <iostream>
#include <string>
#include <fstream>

#include "person.pb.h"

using namespace std;

void listPerson(const AddressBook& addressBook)
{
    for (int i = 0; i < addressBook.person_size();i++)
    {
        const Person& person = addressBook.person(i);

        cout << "name: " << person.name() << endl;
        cout << "id: " << person.id() << endl;
        cout << "email: " << person.email() << endl;

        for (int j = 0; j < person.phonenumber_size();j++)
        {
            const Person::PhoneNumber& phoneNumber = person.phonenumber(j);

            cout << "phoneNumber: " << phoneNumber.number() << endl;
            cout << "phoneType: " << phoneNumber.type() << endl;
        }
    }
}

int main()
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

    return 0;
}