#include "OperationTest.h"

#include "UnitTest.h"

namespace nkentsuu {
    TestEntry::TestEntry(const std::string& name, UTFunction function, const std::string& description) {
        this->name = name;
        this->function = function;
        this->description = description;
    }

    void TestEntry::AddTest(const UnitTestData& unitest) {
        assetInfos.push_back(unitest);
        Increment(unitest.condition);
    }

    uint32_t TestEntry::GetTotal() {
        return passed + loss;
    }

    void TestEntry::Reset() {
        passed = 0;
        loss = 0;
    }

    std::string TestEntry::GetName() {
        return name;
    }

    UTFunction TestEntry::GetFunction() {
        return function;
    }

    bool TestEntry::Run(const std::string& name) {
        if (function != nullptr && name == this->name) {
            function(name);
            return true;
        }
        return false;
    }

    std::string TestEntry::GetDescription() {
        return description;
    }

    AssertInfos TestEntry::GetInfos() {
        return assetInfos;
    }

    void TestEntry::Increment(bool a) {
        if (a) passed++;
        else loss++;
    }
}