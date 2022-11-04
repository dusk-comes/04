all: print

print_ip: print_ip.cpp
	g++ --std=c++17 -Wall -Wextra -pedantic -Werror $< -o $@

clean:
	rm print_ip

print: print_ip
	./$<

.PHONY: clean print
