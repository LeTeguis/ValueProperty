#ifndef __UNITTEST_H_HEADER__
#define __UNITTEST_H_HEADER__

#include <Platform/Platform.h>
#include <Platform/Types.h>
#include <Logger/Logger.h>

#include <chrono>
#include <functional>
#include <string>
#include <unordered_map>
#include <memory>

#include "OperationTest.h"
#include <Logger/Assert.h>

namespace nkentsuu
{   
    class NKENTSUU_API UnitTest{
        public:
            static UnitTest& Instance(){
                static UnitTest unitTest;
                return unitTest;
            }

            // Register
            void Register(const std::string& name, UTFunction function, const std::string& description);

            // Run
            int32 Run();

            /*void BeginTest(const std::string& name) {
                Assert__->True(m_CurrentRegister != "");
                m_CurrentRegister = name;
            }

            void EndTest(const std::string& name) {
                Assert__->True(m_CurrentRegister != name);
                m_CurrentRegister = "";
            }*/

            // Test
            TestState AssertTest(bool condition, const std::string& file, uint32 line, const std::string& function, const std::string& message)
            {
                if (m_TestList.find(m_CurrentRegister) == m_TestList.end() || m_CurrentRegister == "") {
                    Logger__->Warning("Le block de test {0} nexiste pas", function);
                    return TestState::Indetermine;
                }
                m_TestList[m_CurrentRegister]->AddTest(UnitTestData(condition, file, line, function, message));

                return condition ? TestState::Passed : TestState::Lossed;
            }

            bool IsDetailPrint() {
                return m_PrintDetails;
            }

            void PrintDetails(bool print) {
                m_PrintDetails = print;
            }

            bool IsPassedDetailPrint() {
                return m_PrintPassedDetails;
            }

            void PrintPassedDetails(bool print) {
                m_PrintPassedDetails = print;
            }

            bool IsLossedDetailPrint() {
                return m_PrintLossedDetails;
            }

            void PrintLossedDetails(bool print) {
                m_PrintLossedDetails = print;
            }

            std::shared_ptr<Logger> Logger__;
            std::shared_ptr<Assert> Assert__;
        
        private:
            UnitTest() : Logger__(std::make_shared<Logger>("UnitTest")) {
                Assert__ = std::make_shared<Assert>(Logger__);
            }
            AssertFunction m_CurrentRegister;
            std::unordered_map<AssertFunction, TestEntryPtr> m_TestList;
            bool m_PrintDetails = false;
            bool m_PrintLossedDetails = true;
            bool m_PrintPassedDetails = false;
    };
} // namespace nkentsuu

namespace nkentsuu {
#define EXPRESSION(value) #value
#define UNIT_TEST           UnitTest::Instance()
#define LOG_TEST            UnitTest::Instance().Logger__->ILog(__FILE__, __LINE__, __FUNCTION__)
#define ASSERT_TEST			UnitTest::Instance().Assert__->IAssert(__FILE__, __LINE__, __FUNCTION__)

#define UTAT UNIT_TEST.AssertTest
#define SFF STRING_FORMATTER.Format
#define FLF __FILE__, __LINE__, __FUNCTION__

#define STRAUT(a) #a

#define AUT(value, ... ) UTAT((value), FLF, SFF("[{0}]; {1}", ##value, __VA_ARGS__))

#define AUT_TRUE(value, ... ) UTAT((value == true), FLF, SFF("[{0} Is True]; {1}", #value, __VA_ARGS__))

#define AUT_FALSE(value, ... ) UTAT((value == false), FLF, SFF("[{0} Is False]; {1}", #value, __VA_ARGS__))

#define AUT_EQUAL(value1, value2, ... ) UTAT((value1 == value2), FLF, SFF("[{0}]; {1}", STRAUT(value1##==##value2), __VA_ARGS__))

#define AUT_DIFFERENT(value1, value2, ... ) UTAT((value1 != value2), FLF, SFF("[{0}]; {1}", STRAUT(value1##!=##value2), __VA_ARGS__))

#define AUT_NULL(value, ... ) UTAT((value == nullptr), FLF, SFF("[{0} Is Null]; {1}", #value, __VA_ARGS__))
}

#endif /* __UNITTEST_H_HEADER__ */
