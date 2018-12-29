#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include <amy/connector.hpp>

BOOST_AUTO_TEST_CASE(should_construct_a_connector_instance) {
    AMY_ASIO_NS::io_context io_context;
    amy::connector connector(io_context);
}

BOOST_AUTO_TEST_CASE(should_be_opened_successfully) {
    AMY_ASIO_NS::io_context io_context;
    amy::connector connector(io_context);

    connector.open();
    BOOST_CHECK(connector.is_open());
}

BOOST_AUTO_TEST_CASE(should_be_closed_successfully) {
    AMY_ASIO_NS::io_context io_context;
    amy::connector connector(io_context);

    connector.open();
    BOOST_CHECK(connector.is_open());

    connector.close();
    BOOST_CHECK(!connector.is_open());
}

// vim:ft=cpp sw=4 ts=4 tw=80 et
