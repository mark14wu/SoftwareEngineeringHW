core = test_core
argparser = test_argparser
preprocessing = test_preprocessing

main = test_driver
object = test
graph = result

all:
	g++ --coverage $(main).cpp $(core).cpp $(argparser).cpp $(preprocessing).cpp -isystem ./include libgmock.a -pthread -o $(object) -std=c++11 
	./$(object)
	lcov -d . -t $(object) -o $(object).info -b . -c
	genhtml -o $(graph) $(object).info

core:
	g++ $(main).cpp $(core).cpp -isystem ./include libgmock.a -pthread -o $(core) -std=c++11
	./$(core)
	rm -rf $(core)

argparser:
	g++ $(main).cpp $(argparser).cpp -isystem ./include libgmock.a -pthread -o $(argparser) -std=c++11
	./$(argparser)
	rm -rf $(argparser)

preprocessing:
	g++ $(main).cpp $(preprocessing).cpp -isystem ./include libgmock.a -pthread -o $(preprocessing) -std=c++11
	./$(preprocessing)
	rm -rf $(preprocessing)

clean:
	rm -rf $(object)
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf $(graph)
	rm -rf $(object).info