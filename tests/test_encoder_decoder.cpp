#include <catch.hpp>
#include "encoder.h"
#include "decoder.h"

#include <sstream>

TEST_CASE("Encoder and Decoder") {
    std::vector<std::vector<std::pair<std::string, std::string>>> tests{
        {
            {"bibaboba", "balaboba"},
            {"3.1415926...", "pi"},
        },
        {
            {"some data", "surname"},
            {"To be, or not to be, that is the question:\n"
             "Whether 'tis nobler in the mind to suffer\n"
             "The slings and arrows of outrageous fortune,\n"
             "Or to take arms against a sea of troubles\n"
             "And by opposing end them. To die—to sleep,\n"
             "No more; and by a sleep to say we end\n"
             "The heart-ache and the thousand natural shocks\n"
             "That flesh is heir to: 'tis a consummation\n"
             "Devoutly to be wish'd. To die, to sleep;",
             "to be continued (or not)"},
            {"OiMP! OiMP! OiMP! How much there is in this word...", "Ode for OiMP"},
            {"(:", "smile"},
        },
    };

    Encoder encoder;
    Decoder decoder;

    for (const auto& test : tests) {
        std::ostringstream out;
        encoder.Start(out);
        for (const auto& [content, name] : test) {
            std::istringstream current(content);
            encoder.Add(current, name);
        }
        encoder.Stop();

        std::istringstream in(out.str());
        decoder.Start(in);
        std::vector<std::pair<std::string, std::string>> result;
        while (!decoder.IsDone()) {
            std::ostringstream current;
            result.emplace_back();
            decoder.Get(current, result.back().second);
            result.back().first = current.str();
        }

        REQUIRE(test == result);
    }
}
