#include "UnitTest.h"

#include <Logger/Logger.h>
#include "OperationTest.h"

namespace nkentsuu
{
    void UnitTest::Register(const std::string& name, UTFunction function, const std::string& description) {
        m_TestList[name] = std::make_shared<TestEntry>(name, function, description);
    }

    int32 UnitTest::Run() {
        uint32 totalNumber = 0;
        uint32 totalLost = 0;
        uint32 totalPassed = 0;

        std::vector<std::string> orderTestLost;
        std::vector<std::string> orderTestPassed;
        std::vector<std::string> orderNoTest;

        for (auto& test : m_TestList) {
            m_CurrentRegister = test.first;
            TestEntryPtr current = test.second;

            if (current->Run(m_CurrentRegister)) {
                uint32 actualNumber = 0;
                uint32 actualLost = 0;
                uint32 actualPassed = 0;

                for (int i = 0; i < current->GetInfos().size(); i++) {
                    UnitTestData utd = current->GetInfos()[i];

                    actualNumber++;

                    if (utd.condition) {
                        actualPassed++;
                        if (m_PrintDetails || m_PrintPassedDetails) {
                            //LOG_TEST.Info("| {0} | {1} | {2} | {3} |", utd.file, utd.function, utd.line, utd.message);
                            LOG_TEST.Info("| {0} | {1} | {2} |", utd.function, utd.line, utd.message);
                        }
                    } else {
                        actualLost++;
                        if (m_PrintDetails || m_PrintLossedDetails) {
                            //LOG_TEST.Error("| {0} | {1} | {2} | {3} |", utd.file, utd.function, utd.line, utd.message);
                            LOG_TEST.Error("| {0} | {1} | {2} |", utd.function, utd.line, utd.message);
                        }
                    }
                }

                if (actualNumber > 0) {
                    if (actualLost > 0) {
                        LOG_TEST.Error("[{0}] > {1} Lost; {2} Passed; {3} Total > ({4})", current->GetName(), actualLost, actualPassed, actualNumber, current->GetDescription());
                        orderTestLost.push_back(current->GetName());
                    }
                    else if (actualPassed > 0) {
                        LOG_TEST.Info("[{0}] > {1} Lost; {2} Passed; {3} Total > ({4})", current->GetName(), actualLost, actualPassed, actualNumber, current->GetDescription());
                        orderTestPassed.push_back(current->GetName());
                    }
                } else {
                    LOG_TEST.Warning("[{0}] > No test detected > ({1})", current->GetName(), current->GetDescription());
                    orderNoTest.push_back(current->GetName());
                }
                totalNumber += actualNumber;
                totalLost += actualLost;
                totalPassed += actualPassed;
            } else {
                LOG_TEST.Warning("The current test {0} Is not {1} test research", current->GetName(), test.first);
            }
        }
        std::string names = " ";
        for (auto& lost : orderTestLost){
            names += lost + "; ";
        }
        if (names != " ")
            LOG_TEST.Error("{0} Lost / {1} Total > [{2}]", totalLost, totalNumber, names);

        names = " ";
        for (auto& passed : orderTestPassed){
            names += passed + "; ";
        }
        if (names != " ")
            LOG_TEST.Info("{0} Passed / {1} Total > [{2}]", totalPassed, totalNumber, names);

        names = " ";
        for (auto& noTest : orderNoTest){
            names += noTest + "; ";
        }
        if (names != " ")
            LOG_TEST.Warning("No test detected > [{0}]", names);

        return (0);
    }
} // namespace ntsut
