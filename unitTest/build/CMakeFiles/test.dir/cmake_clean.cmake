FILE(REMOVE_RECURSE
  "CMakeFiles/test.dir/hello.cpp.o"
  "CMakeFiles/test.dir/swap.cpp.o"
  "test.pdb"
  "test"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang CXX)
  INCLUDE(CMakeFiles/test.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
