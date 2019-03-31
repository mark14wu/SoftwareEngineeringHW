core = test_core

core:
	g++ $(core).cpp -isystem ./include libgmock.a -pthread -o $(objects) -std=c++11
	./$(core)
	rm -rf $(core)