#ifndef officialTestVectors_hpp
#define officialTestVectors_hpp

#include <array>

#include "testData.hpp"

const std::vector<testData> officialTestVectors = {
    {
        {0x00, 0x00, 0x00, 0x00},
        {"abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "about"},
        "c55257c360c07c72029aebc1b53c05ed0362ada38ead3e3e9efa3708e53495531f09a6987599d18264c1e1c92f2cf141630c7a3c4ab7c81b2f001698e7463b04"
    },
    {
        {0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f},
        {"legal", "winner", "thank", "year", "wave", "sausage", "worth", "useful", "legal", "winner", "thank", "yellow"},
        "2e8905819b8723fe2c1d161860e5ee1830318dbf49a83bd451cfb8440c28bd6fa457fe1296106559a3c80937a1c1069be3a3a5bd381ee6260e8d9739fce1f607"
    },
    {
        {0x80808080, 0x80808080, 0x80808080, 0x80808080},
        {"letter", "advice", "cage", "absurd", "amount", "doctor", "acoustic", "avoid", "letter", "advice", "cage", "above"},
        "d71de856f81a8acc65e6fc851a38d4d7ec216fd0796d0a6827a3ad6ed5511a30fa280f12eb2e47ed2ac03b5c462a0358d18d69fe4f985ec81778c1b370b652a8"
    },
    {
        {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff},
        {"zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "wrong"},
        "ac27495480225222079d7be181583751e86f571027b0497b5b5d11218e0a8a13332572917f0f8e5a589620c6f15b11c61dee327651a14c34e18231052e48c069"
    },
    {
        {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
        {"abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "agent"},
        "035895f2f481b1b0f01fcf8c289c794660b289981a78f8106447707fdd9666ca06da5a9a565181599b79f53b844d8a71dd9f439c52a3d7b3e8a79c906ac845fa"
    },
    {
        {0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f},
        {"legal", "winner", "thank", "year", "wave", "sausage", "worth", "useful", "legal", "winner", "thank", "year", "wave", "sausage", "worth", "useful", "legal", "will"},
        "f2b94508732bcbacbcc020faefecfc89feafa6649a5491b8c952cede496c214a0c7b3c392d168748f2d4a612bada0753b52a1c7ac53c1e93abd5c6320b9e95dd"
    },
    {
        {0x80808080, 0x80808080, 0x80808080, 0x80808080, 0x80808080, 0x80808080, 0x80808080, 0x80808080},
        {"letter", "advice", "cage", "absurd", "amount", "doctor", "acoustic", "avoid", "letter", "advice", "cage", "absurd", "amount", "doctor", "acoustic", "avoid", "letter", "advice", "cage", "absurd", "amount", "doctor", "acoustic", "bless"},
        "c0c519bd0e91a2ed54357d9d1ebef6f5af218a153624cf4f2da911a0ed8f7a09e2ef61af0aca007096df430022f7a2b6fb91661a9589097069720d015e4e982f"
    },
    {
        {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff},
        {"zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "zoo", "vote"},
        "dd48c104698c30cfe2b6142103248622fb7bb0ff692eebb00089b32d22484e1613912f0a5b694407be899ffd31ed3992c456cdf60f5d4564b8ba3f05a69890ad"
    },
    {
        {0x9e885d95, 0x2ad362ca, 0xeb4efe34, 0xa8e91bd2},
        {"ozone", "drill", "grab", "fiber", "curtain", "grace", "pudding", "thank", "cruise", "elder", "eight", "picnic"},
        "274ddc525802f7c828d8ef7ddbcdc5304e87ac3535913611fbbfa986d0c9e5476c91689f9c8a54fd55bd38606aa6a8595ad213d4c9c9f9aca3fb217069a41028"
    },
    {
        {0x68a79eac, 0xa2324873, 0xeacc50cb, 0x9c6eca8c, 0xc68ea5d9, 0x36f98787, 0xc60c7ebc, 0x74e6ce7c},
        {"hamster", "diagram", "private", "dutch", "cause", "delay", "private", "meat", "slide", "toddler", "razor", "book", "happy", "fancy", "gospel", "tennis", "maple", "dilemma", "loan", "word", "shrug", "inflict", "delay", "length"},
        "64c87cde7e12ecf6704ab95bb1408bef047c22db4cc7491c4271d170a1b213d20b385bc1588d9c7b38f1b39d415665b8a9030c9ec653d75e65f847d8fc1fc440"
    },
};

#endif
