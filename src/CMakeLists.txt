
add_library(solve STATIC bit_vector.c bit_vector.h map.c map.h queue.c queue.h vector.c vector.h)

add_library(sat_cryptominisat STATIC satsolver_cryptominisat.cc)
target_link_libraries(sat_cryptominisat cryptominisat5)
find_package (Threads)
target_link_libraries(sat_cryptominisat ${CMAKE_THREAD_LIBS_INIT})

add_library(sat_picosat STATIC satsolver_picosat.c)
target_link_libraries(sat_picosat picosat)

add_library(sat_minisat STATIC satsolver_minisat.cc)
target_link_libraries(sat_minisat minisat)

add_library(sat_lingeling STATIC satsolver_lingeling.c)
target_link_libraries(sat_lingeling lingeling)
target_link_libraries(sat_lingeling m)

add_library(sat_glucose STATIC satsolver_glucose.cc)
target_link_libraries(sat_glucose glucose)

# External Projects

include(ExternalProject)


# cryptominisat
ExternalProject_Add(cmsat
    GIT_REPOSITORY https://github.com/msoos/cryptominisat.git
	CMAKE_GENERATOR "Unix Makefiles"
    CMAKE_ARGS "-DSTATICCOMPILE=ON"
    BUILD_COMMAND make libcryptominisat5 CopyPublicHeaders
    INSTALL_COMMAND ""
    UPDATE_DISCONNECTED 1
)

ExternalProject_Get_Property(cmsat binary_dir)

add_library(cryptominisat5 STATIC IMPORTED)
set_property(TARGET cryptominisat5 PROPERTY IMPORTED_LOCATION ${binary_dir}/lib/libcryptominisat5.a)
add_dependencies(cryptominisat5 cmsat)
include_directories(${binary_dir}/include)


# picosat
ExternalProject_Add(picosat-src
    URL http://fmv.jku.at/picosat/picosat-965.tar.gz
	CONFIGURE_COMMAND ./configure.sh
    BUILD_COMMAND make libpicosat.a
	BUILD_IN_SOURCE 1
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(picosat-src binary_dir)

add_library(picosat STATIC IMPORTED)
set_property(TARGET picosat PROPERTY IMPORTED_LOCATION ${binary_dir}/libpicosat.a)
add_dependencies(picosat picosat-src)
include_directories(${binary_dir})


# minisat
ExternalProject_Add(minisat-src
    GIT_REPOSITORY https://github.com/stp/minisat.git
	CMAKE_GENERATOR "Unix Makefiles"
    BUILD_COMMAND make minisat-lib-static
    INSTALL_COMMAND ""
	UPDATE_DISCONNECTED 1
)

ExternalProject_Get_Property(minisat-src binary_dir)
ExternalProject_Get_Property(minisat-src source_dir)

add_library(minisat STATIC IMPORTED)
set_property(TARGET minisat PROPERTY IMPORTED_LOCATION ${binary_dir}/libminisat.a)
add_dependencies(minisat minisat-src)
include_directories(${source_dir})


# lingeling
ExternalProject_Add(lingeling-src
    URL http://fmv.jku.at/lingeling/lingeling-bbc-9230380-160707.tar.gz
	CONFIGURE_COMMAND ./configure.sh
    BUILD_COMMAND make liblgl.a
	BUILD_IN_SOURCE 1
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(lingeling-src binary_dir)

add_library(lingeling STATIC IMPORTED)
set_property(TARGET lingeling PROPERTY IMPORTED_LOCATION ${binary_dir}/liblgl.a)
add_dependencies(lingeling lingeling-src)
include_directories(${binary_dir})

# glucose
ExternalProject_Add(glucose-src
    URL http://www.labri.fr/perso/lsimon/downloads/softwares/glucose-syrup-4.1.tgz
	CONFIGURE_COMMAND echo
	BINARY_DIR glucose-src-prefix/src/glucose-src/simp/
    BUILD_COMMAND make libr
	#BUILD_IN_SOURCE 1
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(glucose-src binary_dir)

add_library(glucose STATIC IMPORTED)
set_property(TARGET glucose PROPERTY IMPORTED_LOCATION ${binary_dir}/lib.a)
add_dependencies(glucose glucose-src)
include_directories(${binary_dir}/..)
