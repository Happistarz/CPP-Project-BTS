#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			std::string expected = "Hello World";

			std::string actual = "Hello World";

			Assert::AreEqual(expected, actual);
		}
	};
}
