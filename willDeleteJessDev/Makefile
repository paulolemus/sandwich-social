# temp folder Makefile

CXX := c++

CXX_FLAGS := -Wall -Wextra -pedantic --std=c++11 -g

LIBS := -lncurses

all: paulo

paulo: paulo-test.cpp
	$(CXX) $^ -o $@ $(CXX_FLAGS) $(LIBS)



# clean targets

.PHONY: clean clean-paulo

clean: clean-paulo

clean-paulo:
	-rm paulo
