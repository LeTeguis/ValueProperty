#ifndef __OPERATIONTEST_H_HEADER__
#define __OPERATIONTEST_H_HEADER__

#pragma once

#include <Platform/Types.h>
#include <functional>
#include <string>
#include <vector>
#include <memory>

namespace nkentsuu
{
    enum class TestState {
        Indetermine, Passed, Lossed
    };

    struct UnitTestData {
        bool condition;
        std::string file;
        uint32 line;
        std::string function;
        std::string message;

        UnitTestData() : condition(true), file(""), line(0), function(""), message("") {}
        UnitTestData(bool condition, const std::string& file, uint32 line, const std::string& function, const std::string& message) : condition(condition), file(file), line(line), function(function), message(message) {}
    };

    using UTFunction = std::function<void(const std::string&)>;
    #define UTRegisterClass(name, description) #name, std::bind(&name, this, std::placeholders::_1), description
    #define UTRegisterFunction(name, description) #name, name, description
    #define UTRegisterLambda(name, lambda, description) #name, lambda, description

    using AssertInfos = std::vector<UnitTestData>;
    using AssertFunction = std::string;

    struct TestEntry {
        TestEntry(const std::string& name, UTFunction function, const std::string& description);

        void AddTest(const UnitTestData& unitest);

        uint32_t GetTotal();

        void Reset();

        std::string GetName();

        UTFunction GetFunction();

        bool Run(const std::string& name);

        std::string GetDescription();

        AssertInfos GetInfos();

        private:
        std::string name;
        UTFunction function;
        std::string description;
        AssertInfos assetInfos;
        uint32 passed = 0;
        uint32 loss = 0;

        void Increment(bool a);
    };

    using TestEntryPtr = std::shared_ptr<TestEntry>;
} // namespace nkentsuu


#endif /* __OPERATIONTEST_H_HEADER__ */
