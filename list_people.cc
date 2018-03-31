// See README.txt for information and build instructions.

#include <fstream>
#include <google/protobuf/arena.h>
#include <google/protobuf/util/time_util.h>
#include <iostream>
#include <string>

#include "addressbook.pb.h"

using namespace std;
using namespace tutorial;
using google::protobuf::Arena;
using google::protobuf::util::TimeUtil;

Arena arena;

// Iterates though all people in the AddressBook and prints info about them.
void ListPeople(const AddressBook& address_book) {
  for (int i = 0; i < address_book.people_size(); i++) {
    const Person& person = address_book.people(i);

    cout << "Person ID: " << person.id() << endl;
    cout << "  Name: " << person.name() << endl;
    if (person.email() != "") {
      cout << "  E-mail address: " << person.email() << endl;
    }
    if (person.phone() != "") {
      cout << "  Phone: " << person.phone() << endl;
    }
    if (person.has_last_updated()) {
      cout << "  Updated: " << TimeUtil::ToString(person.last_updated()) << endl;
    }
  }
}

// Main function:  Reads the entire address book from a file and prints all
//   the information inside.
int main(int argc, char* argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  if (argc != 2) {
    cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
    return -1;
  }

  AddressBook* book =
    google::protobuf::Arena::CreateMessage<AddressBook>(&arena);

  {
    // Read the existing address book.
    fstream input(argv[1], ios::in | ios::binary);
    if (!book->ParseFromIstream(&input)) {
      cerr << "Failed to parse address book." << endl;
      return -1;
    }
  }

  ListPeople(*book);

  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
