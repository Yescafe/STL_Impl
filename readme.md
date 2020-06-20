# STL Implementation
代码参考《STL 源码剖析》（侯捷 著）。  
Reference to *The Annotated STL Sources(using SGI STL)*.   

最低兼容版本为 C++11，默认为 C++17 (放弃了原来的 C++20).  
Default is `-std=c++17` (C++20 is deprecated), minimum is `-std=c++11`.  


## 组件和附属组件完成状态 Components' Status
- [x] memory.hpp
  - [x] memory/alloc.hpp
  - [x] memory/construct.hpp
  - [x] memory/utils.hpp
- [x] iterator.hpp
- [x] vector.hpp
  - [x] tests/vector.cpp
- [x] list.hpp
  - [x] tests/list.cpp
- [x] deque.hpp
  - [x] tests/deque.cpp
- [x] stack.hpp
  - [x] tests/stack.cpp
- [x] queue.hpp
  - [x] tests/queue.cpp
- [x] pqueue.hpp (priority_queue)
  - [x] tests/priority_queue.cpp
- Algorithm.hpp
  - [x] heap: `push_heap()`, `pop_heap()`, `sort_heap()`, `make_heap()`
- [ ] Experiment libs (maybe need C++20, so need to modify the `Makefile`)
  - [ ] experiment/concept/concept.hpp (C++20)
