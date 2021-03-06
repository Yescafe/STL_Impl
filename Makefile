cpp          := c++
cppflags     := -std=c++17 -Wall -Wextra -g

out_dir      := ./bin
target_name  := $(shell ls ./tests | grep -v rb_tree\.cpp)
target_name  := $(patsubst %.cpp,%,$(target_name))
target       := $(addprefix $(out_dir)/,$(target_name))

all: $(out_dir) $(target)

$(out_dir)/%: ./tests/%.cpp
	$(cpp) $^ -o $@ $(cppflags)

$(out_dir):
	mkdir -p $(out_dir)

.PHONY:
clean:
	rm -rf $(out_dir)
