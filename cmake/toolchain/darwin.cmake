set(CMAKE_SYSTEM_NAME Darwin)
set(CMAKE_SYSTEM_VERSION 10.15)

# target environment on the build host system
set(CMAKE_FIND_ROOT_PATH ${CMAKE_PREFIX_PATH})

# modify default behavior of FIND_XXX() commands
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
