
client: client.cpp requests.cpp helpers.cpp buffer.cpp
	g++ -std=c++17 -Wall -Wextra client.cpp requests.cpp helpers.cpp buffer.cpp -o client

run: client
	./client

clean:
	rm -f *.o client
