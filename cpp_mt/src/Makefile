CXX = clang++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++17
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++ grpc`\
					 -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed\
					 -ldl
PROTOC = protoc
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`
PROTOS_PATH = ../protoc
all: graph_test
graph_test: graph_test.o
	$(CXX) -o graph_test graph_test.o -lpthread -lgtest -lgtest_main
graph_test.o: graph_test.cpp
	$(CXX) $(CXXFLAGS) -c graph_test.cpp
clean:
	rm *.o graph_test
