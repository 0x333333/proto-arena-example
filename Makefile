# See README.txt.

.PHONY: all cpp clean

all: cpp

cpp:    add_person_cpp    list_people_cpp

clean:
	rm -f add_person_cpp list_people_cpp add_person_java list_people_java add_person_python list_people_python
	rm -f javac_middleman AddPerson*.class ListPeople*.class com/example/tutorial/*.class
	rm -f protoc_middleman addressbook.pb.cc addressbook.pb.h addressbook_pb2.py com/example/tutorial/AddressBookProtos.java
	rm -f *.pyc
	rm -f protoc_middleman_go tutorial/*.pb.go add_person_go list_people_go
	rmdir tutorial 2>/dev/null || true
	rmdir com/example/tutorial 2>/dev/null || true
	rmdir com/example 2>/dev/null || true
	rmdir com 2>/dev/null || true

protoc_middleman: addressbook.proto
	protoc $$PROTO_PATH --cpp_out=. --java_out=. --python_out=. addressbook.proto
	@touch protoc_middleman

protoc_middleman_go: addressbook.proto
	mkdir -p tutorial # make directory for go package
	protoc $$PROTO_PATH --go_out=tutorial addressbook.proto
	@touch protoc_middleman_go

add_person_cpp: add_person.cc protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	c++ add_person.cc addressbook.pb.cc -o add_person_cpp `pkg-config --cflags --libs protobuf`

list_people_cpp: list_people.cc protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	c++ list_people.cc addressbook.pb.cc -o list_people_cpp `pkg-config --cflags --libs protobuf`