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
all: graph_test mt_node_test
graph_test: graph_test.o
	$(CXX) -o graph_test graph_test.o -lpthread -lgtest -lgtest_main
graph_test.o: graph_test.cpp
	$(CXX) $(CXXFLAGS) -c graph_test.cpp
mt_node_test: mt_node_test.o
	$(CXX) -o mt_node_test mt_node_test.o -lpthread -lgtest -lgtest_main
mt_node_test.o: mt_node_test.cc
	$(CXX) $(CXXFLAGS) -c mt_node_test.cc
search_test: search_test.o
	$(CXX) -o search_test search_test.o -lpthread -lgtest -lgtest_main
search_test.o: search_test.cc
	$(CXX) $(CXXFLAGS) -c search_test.cc
utils_test: utils_test.o
	$(CXX) -o utils_test utils_test.o -lpthread -lgtest -lgtest_main
utils_test.o: utils_test.cc
	$(CXX) $(CXXFLAGS) -c utils_test.cc
clean:
	rm *.o graph_test
