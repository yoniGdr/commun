cmake_minimum_required (VERSION 3.10.2)
set(CMAKE_CXX_STANDARD 14)
project (SM_STRUCTURE)

# Recurse into the "Hello" and "Demo" subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
add_subdirectory (srcs)
add_subdirectory (examples)
