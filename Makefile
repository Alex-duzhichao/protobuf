.PHONY: all clean protoc_middleman add_diceroll

all: add_diceroll read_diceroll

clean:
	rm -rf diceroll.pb.cc diceroll.pb.h add_diceroll protoc_middleman read_diceroll

protoc_middleman: diceroll.proto
	protoc --cpp_out=. diceroll.proto
	@touch protoc_middleman

add_diceroll: protoc_middleman add_diceroll.cc
	g++ add_diceroll.cc diceroll.pb.cc -o add_diceroll -std=gnu++11 `pkg-config --cflags --libs protobuf`

read_diceroll: protoc_middleman read_diceroll.cc
	g++ read_diceroll.cc diceroll.pb.cc -o read_diceroll -std=gnu++11 `pkg-config --cflags --libs protobuf`
