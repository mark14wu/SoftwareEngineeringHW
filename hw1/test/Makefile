core = test_core
argparser = test_argparser

core:
	g++ $(core).cpp -isystem ./include libgmock.a -pthread -o $(core) -std=c++11
	./$(core)
	rm -rf $(core)

argparser:
	g++ $(argparser).cpp -isystem ./include libgmock.a -pthread -o $(argparser) -std=c++11
	./$(argparser)
	rm -rf $(argparser)