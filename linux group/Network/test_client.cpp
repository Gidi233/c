#include "Msg.h"
#include "NetworkTest.grpc.pb.h"
#include "NetworkTest.pb.h"
#include <algorithm>
#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <bits/types/FILE.h>
#include <chrono>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <deque>
#include <exception>
#include <fcntl.h>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/support/status.h>
#include <memory>
#include <mutex>
#include <ostream>
#include <random>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/stat.h>
#include <thread>
#include <unistd.h>
#include <vector>

class ClientTester {
    friend void RunClientTest(std::shared_ptr<ClientTester> tester);
    using NT = NetworkTest::NT;
    using Stub = NetworkTest::NT::Stub;
    using Result = NetworkTest::Result;
    using runtime_error = std::runtime_error;
    using Context = ::grpc::ClientContext;

    std::unique_ptr<Stub> stub;
    std::default_random_engine re;
    std::uniform_int_distribution<char> AsciiStringGenerator;
    std::uniform_int_distribution<char> BinStringGenerator;
    std::uniform_int_distribution<uint32_t> LenGenerator;
    int fd;
    void QueryStatus(uint64_t idx, Result &response) {
        if (idx < 0)
            runtime_error("No Exist msg Idx<0\n");
        if (idx <= SuccessMaxIdx) {
            response.set_id(SuccessMaxIdx);
            response.set_reason(Success);
            return;
        }
        Context context;
        NetworkTest::Query query;
        query.set_id(idx);
        auto res = stub->ResultQuery(&context, query, &response);
        if (!res.ok())
            runtime_error("Test Error,Please Retry!\n");
        if (response.reason() >= ErrorLevel)
            throw std::runtime_error(
                    ErrorCode2Msg(static_cast<TestStatus>(response.reason())));
        if (response.reason() == Success)
            SuccessMaxIdx = std::max(SuccessMaxIdx, response.id());
    }
    void SendAnswer(const std::string &s) {
        SendSeq++;
        Context context;
        Result response;
        ::NetworkTest::Register answer;
        answer.set_content(s);
        auto res = stub->AnswerRegister(&context, answer, &response);
        if (!res.ok())
            runtime_error("Test Error,Please Retry!\n");
        if (response.reason() >= ErrorLevel)
            throw std::runtime_error(
                    ErrorCode2Msg(static_cast<TestStatus>(response.reason())));
        if (response.reason() == Success)
            SuccessMaxIdx = std::max(SuccessMaxIdx, response.id());
    }
    uint32_t SendSeq = -1;
    uint32_t SuccessMaxIdx = -1;
    static const char *ErrorCode2Msg(TestStatus s) noexcept {
        switch (s) {
            case Success:
                return "Success";
            case Wait:
                return "Wait For Msg";
            case WaitRPC:
                return "Wait For Test";
            case Diff:
                return "Msg is Error";
            case Unknow:
                return "Unknow Error";
            case ErrorLevel:
            case TestError:;
        }
        return "Tester is Error";
    }

    TestStatus Check() {
        using namespace std::chrono_literals;
        Result response;
        QueryStatus(SendSeq, response);
        if (response.id() == SendSeq && response.reason() == Success)
            return Success;
        std::this_thread::sleep_for(3s);
        return (response.id() == SendSeq && response.reason() == Success)
                       ? Success
                       : static_cast<TestStatus>(response.reason());
    }

    void genAsciiMsg(uint64_t size) {
        for (uint64_t i = 0; i < size; i++) {
            auto len = LenGenerator(re);
            auto ch = AsciiStringGenerator(re);
            std::string s(len, ch);
            SendAnswer(s);
            msgs->push(std::move(s));
        }
    }

    void genBinMsg(uint64_t size) {
        for (uint64_t i = 0; i < size; i++) {
            auto len = LenGenerator(re);
            std::string s;
            for (auto t = 0; t < len; t++)
                s.push_back(BinStringGenerator(re));
            SendAnswer(s);
            msgs->push(std::move(s));
        }
    }
    uint64_t getSeed() {
        fd = open("/dev/urandom", O_RDONLY);
        uint64_t seed;
        auto rc = read(fd, &seed, sizeof(seed));
        if (rc != sizeof(seed))
            throw runtime_error("read /dev/random failed");
        return seed;
    }

public:
    ClientTester(std::string addr)
        : stub(NT::NewStub(
                  grpc::CreateChannel(addr, grpc::InsecureChannelCredentials()))),
          re(getSeed()), msgs(std::make_shared<MsgBuf>()),
          AsciiStringGenerator(' ', '~'), BinStringGenerator(CHAR_MIN, CHAR_MAX),
          LenGenerator(0, 4096) {}
    std::shared_ptr<MsgBuf> msgs;
    void FinishCheck() {
        auto res = Check();
        if (res == Success) {
            puts("Congratulations! You Pass The Test!");
            _exit(0);
        }
        printf("Sorry! You did not pass all Test. Reason:%s  :(\n",
               ErrorCode2Msg(res));
    }
};
void RunClientTest(std::shared_ptr<ClientTester> tester) {
    try {
        using namespace std::chrono_literals;
        tester->genAsciiMsg(1);
        std::this_thread::sleep_for(2s);
        auto reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 1\n");
        }
        tester->genAsciiMsg(1);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 2\n");
        }
        tester->genAsciiMsg(1);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 3\n");
        }
        tester->genBinMsg(1);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 4\n");
        }
        tester->genBinMsg(1);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 5\n");
        }
        tester->genBinMsg(1);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 6\n");
        }
        tester->genAsciiMsg(1024);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 7\n");
        }
        tester->genBinMsg(1024);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 8\n");
        }
        tester->genAsciiMsg(1024);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 9\n");
        }
        tester->genBinMsg(1024);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 10\n");
        }
        printf("Success Pass All Test\n");
        _exit(0);
    } catch (...) {
        printf("Exception:\n");
    }
}
std::shared_ptr<MsgBuf> InitTestClient(std::string addr) {
    try {
        auto tester = std::make_shared<ClientTester>(addr);
        auto test_thread = std::thread(RunClientTest, tester);
        test_thread.detach();
        return tester->msgs;
    } catch (std::exception &e) {

        printf("Exception: %s\n", e.what());
    }
    return nullptr;
}

struct Message {
    int msgID;
    int partID;
    std::string data;
};
class mess {
    int partid;
    int len;
};

int main() {
    // Server 端的监听地址
    auto msg = InitTestClient("127.0.0.0:1");
    //u_int32_t
    int cfd;
    int numRead;
    struct addrinfo hints;
    struct addrinfo *result, *rp;//struct

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_family = AF_UNSPEC;                /* Allows IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV;//不必当做名字解析

    if (getaddrinfo("127.0.0.0:1", 50000, &hints, &result) != 0) cout<<"error:267";

    for (rp = result; rp != NULL; rp = rp->ai_next) {

        cfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (cfd == -1)
            continue;                   /* On error, try next address */

        if (connect(cfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break;                              /* Success */

        /* Connect failed: close this socket and try next address */

        close(cfd);
    }

    if (rp == NULL) cout<<"找不到可用addrinfo"
    
    freeaddrinfo(result);

    while(1){
        std::string masg=msg->pop();
        numRead=masg.length();
        send(cfd,(const void*) &numRead,sizeof(int));
        send(cfd,masg.c_str(),sizeof(masg));
    }
    
    exit(EXIT_SUCCESS);                         /* Closes 'cfd' */
}

// int main() {
//     // 创建套接字
//     int sockfd = socket(AF_INET, SOCK_STREAM, 0);
//     if (sockfd == -1) {
//         std::cerr << "Error: Failed to create socket." << std::endl;
//         return -1;
//     }

//     // 连接服务器
//     struct sockaddr_in server_addr;
//     server_addr.sin_family = AF_INET;
    //  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 设置服务器 IP 地址
    // server_addr.sin_port = htons(8080); // 设置服务器端口号

//     if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
//         std::cerr << "Error: Failed to connect to server." << std::endl;
//         close(sockfd);
//         return -1;
//     }

//     // 发送数据包
//     std::string data = "Hello, world!";
//     int seq_num = 0;
//     int sent_bytes = 0;
//     int ret = 0;
//     time_t start_time = time(nullptr);
//     while (sent_bytes < data.length()) {
//         // 发送数据包
//         ret = send(sockfd, data.c_str() + sent_bytes, data.length() - sent_bytes, 0);
//         if (ret < 0) {
//             std::cerr << "Error: Failed to send data." << std::endl;
//             close(sockfd);
//             return -1;
//         }

//         // 记录发送时间和数据包序号
//         time_t send_time = time(nullptr);
//         seq_num++;
//         sent_bytes += ret;

//         // 等待确认消息
//         while (true) {
//             // 计算已经等待的时间
//             time_t elapsed_time = time(nullptr) - start_time;
//             if (elapsed_time >= TIMEOUT) {
//                 // 超时，重传数据包
//                 std::cerr << "Timeout: Resending data packet " << seq_num << std::endl;
//                 break;
//             }

//             // 检查是否收到确认消息
//             char buf[1024];
//             memset(buf, 0, sizeof(buf));
//             int recv_bytes = recv(sockfd, buf, sizeof(buf), MSG_DONTWAIT);
//             if (recv_bytes < 0) {
//                 // 没有收到确认消息，继续等待
//                 continue;
//             } else {
//                 // 收到确认消息，更新发送窗口的状态
//                 int ack_num = std::stoi(buf);
//                 if (ack_num == seq_num) {
//                     std::cout << "Received ACK " << ack_num << std::endl;
//                     break;
//                 }
//             }
//         }
//     }

//     // 关闭套接字
//     close(sockfd);

//     return 0;
// }