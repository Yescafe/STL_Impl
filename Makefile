cpp          := c++
cppflags     := -std=c++17 -W{all,extra} -g

out_dir      := ./bin
target_name  := $(shell ls ./tests)
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
