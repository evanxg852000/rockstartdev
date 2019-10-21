#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

#include "core.hpp"



TEST_CASE("Test byte_to_hexstr", "[ex23]") {
    std::vector<unsigned char> v{ 0xBA, 0xAD, 0xF0, 0x0D };
    std::array<unsigned char, 6> a{ {1,2,3,4,5,6} };
    unsigned char buf[5] = {0x11, 0x22, 0x33, 0x44, 0x55};

    CHECK(bytes_to_hexstr(v, true) == "BAADF00D");
    CHECK(bytes_to_hexstr(a, true) == "010203040506");
    CHECK(bytes_to_hexstr(buf, true) == "1122334455");

    CHECK(bytes_to_hexstr(v) == "baadf00d");
    CHECK(bytes_to_hexstr(a) == "010203040506");
    CHECK(bytes_to_hexstr(buf) == "1122334455");

}

TEST_CASE("Test hexstr_to_byte", "[ex24]"){
    std::vector<unsigned char> expected{ 0xBA, 0xAD, 0xF0, 0x0D, 0x42 };
    CHECK(hexstr_to_bytes("BAADF00D42") == expected);
    CHECK(hexstr_to_bytes("BaaDf00d42") == expected);
}

TEST_CASE("Test capitalize", "[ex25]"){
    using namespace std::string_literals;
    CHECK("The C++ Challenger"s == capitalize("the c++ challenger"s));
    CHECK("This Is An Example, Should Work!"s == capitalize("THIS IS an ExamplE, should wORk!"s));
}

TEST_CASE("Test join_strings", "[ex26]"){
    using namespace std::string_literals;
    std::vector<std::string> v1{ "this","is","an","example" };
    std::vector<std::string> v2{ "example" };
    std::vector<std::string> v3{ };
    CHECK(join_strings(v1, " ") == "this is an example"s);
    CHECK(join_strings(v2, " ") == "example"s);
    CHECK(join_strings(v3, " ") == ""s);
}

TEST_CASE("Test tokenise", "[ex27]"){
    using namespace std::string_literals;
    std::vector<std::string> expected{"this", "is", "a", "sample"};
    CHECK(expected == split("this is a sample"s, ' '));
    CHECK(expected == split("this,is a.sample!!"s, ",.! "s));
}

TEST_CASE("Test validate_license_plate", "[ex29a]"){
    CHECK(validate_license_plate_format("ABC-DE 123"));
    CHECK(validate_license_plate_format("ABC-DE 1234"));
    CHECK(!validate_license_plate_format("ABC-DE 12345"));
    CHECK(!validate_license_plate_format("abc-de 1234"));
}

TEST_CASE("Test extract_license_plate_numbers", "[ex29b]"){
    std::vector<std::string> expected {"AAA-AA 123", "ABC-DE 1234", "XYZ-WW 0001"};
    std::string text("AAA-AA 123qwe-ty 1234 ABC-DE 123456..XYZ-WW 0001");
    CHECK(expected == extract_license_plate_numbers(text));
}

TEST_CASE("Test parse_uri", "[ex30]"){
    auto p1 = parse_uri("https://packt.com");
    CHECK(p1.has_value());
    CHECK(p1->protocol == "https");
    CHECK(p1->domain == "packt.com");
    CHECK(!p1->port.has_value());
    CHECK(!p1->path.has_value());
    CHECK(!p1->query.has_value());
    CHECK(!p1->fragment.has_value());

    auto p2 = parse_uri("https://bbc.com:80/en/index.html?lite=true#ui");
    CHECK(p2.has_value());
    CHECK(p2->protocol == "https");
    CHECK(p2->domain == "bbc.com");
    CHECK(p2->port == 80);
    CHECK(p2->path == "/en/index.html");
    CHECK(p2->query == "lite=true");
    CHECK(p2->fragment == "ui");
}

TEST_CASE("Test transform_date", "[ex31]"){
    using namespace std::string_literals;
    CHECK(transform_date("today is 01.12.2017!"s) == "today is 2017-12-01!"s);
}