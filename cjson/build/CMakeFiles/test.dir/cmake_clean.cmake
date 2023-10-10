FILE(REMOVE_RECURSE
  "CMakeFiles/test.dir/example.c.o"
  "CMakeFiles/test.dir/cJson.c.o"
  "test.pdb"
  "test"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang C)
  INCLUDE(CMakeFiles/test.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
