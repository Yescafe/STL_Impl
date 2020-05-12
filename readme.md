# STL Implements
代码参考《STL 源码剖析》（侯捷 著）。  
Reference to *The Annotated STL Sources(using SGI STL)*.   

最低兼容版本为 C++17，默认为 C++20.  
Default is `-std=c++20`, minimum is `-std=c++17`.  

## 组件和附属组件完成状态 Compenents' Status
- [ ] memory.hpp
  - [x] memory/alloc.hpp
  - [x] memory/construct.hppb
  - [ ] memory/utils.hpp
- [x] iterator.hpp
- [ ] vector.hpp
  - [x] tests/vector.cpp
- [ ] list.hpp
  - [x] tests/list.cpp
- [ ] experiment libs (optional)
  - [ ] experiment/concept/concept.hpp (C++20)