cmake_minimum_required(VERSION 3.0)

project(amy CXX)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

add_library(amy INTERFACE)
target_include_directories(amy INTERFACE include)

option(AMY_USE_BOOST_ASIO "AMY_USE_BOOST_ASIO" ON)
if(AMY_USE_BOOST_ASIO)
    set(AMY_USE_BOOST_ASIO "1")
endif()

option(AMY_USE_MARIADB "AMY_USE_MARIADB" ON)
if(AMY_USE_MARIADB)
    set(AMY_MYSQL_LIB mariadbclient)
else()
    set(AMY_MYSQL_LIB mysqlclient)
endif()

target_compile_definitions(amy INTERFACE AMY_USE_BOOST_ASIO=${AMY_USE_BOOST_ASIO})
target_link_libraries(amy INTERFACE ${AMY_MYSQL_LIB} pthread)
if(AMY_USE_BOOST_ASIO)
    target_link_libraries(amy INTERFACE boost_system)
endif()

option(build_tests "build tests" ON)
if(build_tests)
    enable_testing()
    set(test_src
        test/async_connect_test.cpp
        test/auth_info_test.cpp
        test/blocking_connect_test.cpp
        test/connector_test.cpp
        test/init.sql
        test/main.cpp)
    if(AMY_USE_MARIADB)
        set(test_src ${test_src} test/mariadb_async_connect_test.cpp)
    endif()
    add_executable(tests ${test_src})
    target_link_libraries(tests boost_unit_test_framework amy)
    add_test(tests tests)
endif()

option(build_examples "build examples" ON)
if(build_examples)
    set(examples
        blocking_execute
        async_execute
        blocking_multi_query
        async_multi_query
        blocking_single_query
        async_single_query
        blocking_connect
        async_connect
    )
    if(AMY_USE_MARIADB)
        set(examples
            ${examples}
            mariadb_async_multi_query
            mariadb_async_single_query)
    endif()
    add_library(example_utils STATIC example/utils.cpp)
    target_link_libraries(example_utils PUBLIC amy)
    foreach(example ${examples})
        add_executable(${example} example/${example}.cpp)
        target_link_libraries(${example} example_utils)
    endforeach()
endif()

install(DIRECTORY include DESTINATION ${CMAKE_INSTALL_PREFIX})
