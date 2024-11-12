#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <windows.h>
#include <string>

using ::testing::Return;
using ::testing::_;

class SerialPort {
public:
    virtual ~SerialPort() = default;

    virtual HANDLE openSerialPort(const std::wstring& portName, DWORD baudRate) = 0;
    virtual void sendMessage(HANDLE hSerial, const std::string& message) = 0;
    virtual std::string readMessage(HANDLE hSerial) = 0;
};

class MockSerialPort : public SerialPort {
public:
    MOCK_METHOD(HANDLE, openSerialPort, (const std::wstring& portName, DWORD baudRate), (override));
    MOCK_METHOD(void, sendMessage, (HANDLE hSerial, const std::string& message), (override));
    MOCK_METHOD(std::string, readMessage, (HANDLE hSerial), (override));
};

TEST(SerialPortTest, ReadMessageReturnsEmptyString) {
    MockSerialPort mockSerial;
    HANDLE mockHandle = (HANDLE)1;
    EXPECT_CALL(mockSerial, readMessage(mockHandle))
        .WillOnce(Return(""));
    std::string actualMessage = mockSerial.readMessage(mockHandle);
    EXPECT_EQ(actualMessage, "");
}

TEST(SerialPortTest, ReadMessageReturnsCorrectData) {
    MockSerialPort mockSerial;
    HANDLE mockHandle = (HANDLE)1;
    std::string expectedMessage = "Hello, World!";
    EXPECT_CALL(mockSerial, readMessage(mockHandle))
        .WillOnce(Return(expectedMessage));
    std::string actualMessage = mockSerial.readMessage(mockHandle);
    EXPECT_EQ(actualMessage, expectedMessage);
}

TEST(SerialPortTest, OpenSerialPortFails) {
    MockSerialPort mockSerial;
    EXPECT_CALL(mockSerial, openSerialPort(_, _))
        .WillOnce(Return(INVALID_HANDLE_VALUE));
    HANDLE handle = mockSerial.openSerialPort(L"COM3", 9600);
    EXPECT_EQ(handle, INVALID_HANDLE_VALUE);
}

TEST(SerialPortTest, ReadMessageHandlesNewline) {
    MockSerialPort mockSerial;
    HANDLE mockHandle = (HANDLE)1;
    std::string message = "Hello, World!\n";
    EXPECT_CALL(mockSerial, readMessage(mockHandle))
        .WillOnce(Return(message));
    std::string actualMessage = mockSerial.readMessage(mockHandle);
    EXPECT_EQ(actualMessage, message);
}

TEST(SerialPortTest, SendMessageFails) {
    MockSerialPort mockSerial;
    HANDLE mockHandle = (HANDLE)1;
    std::string message = "Hello, World!";

    EXPECT_CALL(mockSerial, sendMessage(mockHandle, message))
        .WillOnce([](HANDLE, const std::string&) {
        SetLastError(ERROR_IO_DEVICE);
            });
    mockSerial.sendMessage(mockHandle, message);
    EXPECT_EQ(GetLastError(), ERROR_IO_DEVICE);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    ::testing::GTEST_FLAG(output) = "xml:TestResultFile.xml";

    int result = RUN_ALL_TESTS();
    system("pause");
    return result;
}
