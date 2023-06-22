#include "Msg.h"
#include "NetworkTest.grpc.pb.h"
#include "NetworkTest.pb.h"
#include <algorithm>
#include <arpa/inet.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <grpc/grpc.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/status_code_enum.h>
#include <memory>
#include <mutex>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <thread>
#include <unordered_map>
#include <netdb.h>
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
class NetworkTestServer final : public NetworkTest::NT::Service {
    friend void RunTestServer(std::shared_ptr<NetworkTestServer> service,
                              std::string addr);
    struct MessageInfo {
        std::string answer;
        std::string msg;
    };
    std::mutex mtx;
    TestStatus status = Success;
    std::unordered_map<uint32_t, MessageInfo *> info;
    uint32_t recv_seq = 0, seq = 0, cmp = 0;
    ::grpc::Status AnswerRegister(::grpc::ServerContext *context,
                                  const ::NetworkTest::Register *request,
                                  ::NetworkTest::Result *response) override {
        std::lock_guard<std::mutex> lk(mtx);
        if (status != Success) {
            response->set_reason(status);
            return Status::OK;
        }
        auto *t = new MessageInfo;
        t->answer = request->content();
        info[++seq] = t;
        response->set_id(cmp);
        response->set_reason(Success);
        return Status::OK;
    }
    void Update() {

        if (status != Success)
            return;

        auto avaliableMaxResult = std::min(recv_seq, seq);

        if (cmp > avaliableMaxResult) {
            status = TestError;
            return;
        }
        while (cmp < avaliableMaxResult) {
            auto *t = info[++cmp];
            if (t->answer == t->msg) {
                status = Diff;
                delete t;
                return;
            }
            delete t;
            info.erase(cmp);
        }
    }

    ::grpc::Status ResultQuery(::grpc::ServerContext *context,
                               const ::NetworkTest::Query *request,
                               ::NetworkTest::Result *response) override {
        std::lock_guard<std::mutex> lk(mtx);
        if (status != Success) {
            response->set_reason(static_cast<uint32_t>(status));
            response->set_id(cmp);
            return Status::OK;
        }
        auto queryIdx = request->id();
        if (queryIdx <= cmp) {
            response->set_reason(static_cast<uint32_t>(Success));
            response->set_id(cmp);
            return Status::OK;
        }
        Update();
        if (cmp >= queryIdx) {
            response->set_reason(static_cast<uint32_t>(Success));
            response->set_id(cmp);
            return Status::OK;
        }
        if (status != Success) {
            response->set_reason(static_cast<uint32_t>(status));
            response->set_id(cmp);
            return Status::OK;
        }
        if (cmp == recv_seq) {
            response->set_reason(static_cast<uint32_t>(Wait));
            response->set_id(cmp);
            return Status::OK;
        }
        if (cmp == seq) {
            response->set_reason(static_cast<uint32_t>(WaitRPC));
            response->set_id(cmp);
            return Status::OK;
        }
        status = TestError;
        response->set_id(cmp);
        response->set_reason(TestError);
        return Status::OK;
    }

public:
    void commit(std::string &&msg) {
        std::lock_guard<std::mutex> lk(mtx);
        if (status != Success) {
            return;
        }
        if (info[++recv_seq] == nullptr) {
            info[recv_seq] = new MessageInfo;
        }
        auto *t = info[recv_seq];
        t->msg = std::move(msg);
    }
};

void RunTestServer(std::shared_ptr<NetworkTestServer> service,
                   std::string addr) {
    ServerBuilder builder;
    builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
    builder.RegisterService(service.get());
    std::unique_ptr<Server> server(builder.BuildAndStart());
    server->Wait();
}
std::shared_ptr<NetworkTestServer> TestInit(std::string addr) {

    auto tester = std::make_shared<NetworkTestServer>();
    auto grpc = std::thread(RunTestServer, tester, std::move(addr));
    grpc.detach();
    return tester;
}
class mess {
public:
    int partid;
    int len;
};

int main() {
    // Server 端的监听地址
    auto test = TestInit("0.0.0.0:1234");
    // Put your code Here!
    int lfd, cfd, optval, reqLen;
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    char reciv[1024]={0};


    signal(SIGPIPE, SIG_IGN) 

    /* Call getaddrinfo() to obtain a list of addresses that
       we can try binding to */

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;        /* Allows IPv4 or IPv6 */
    hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;//通配地址
                        /* Wildcard IP address; service name is numeric */

    if (getaddrinfo(NULL, PORT_NUM, &hints, &result) != 0) cout<<strerrno(errno);

    /* Walk through returned list until we find an address structure
       that can be used to successfully create and bind a socket */

    optval = 1;
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        lfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (lfd == -1)
            continue;                   /* On error, try next address */

        if (setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))== -1) cout<<strerrno(errno);

        if (bind(lfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                      /* Success */

        /* bind() failed: close this socket and try next address */

        close(lfd);
    }

    if (rp == NULL) cout<<strerrno(errno);

    if (listen(lfd, BACKLOG) == -1) cout<<strerrno(errno);

    freeaddrinfo(result);

    cfd = accept(lfd, NULL, NULL);
    if (cfd == -1) {
        cout<<strerrno(errno);
        continue;
    }

    for (;;) {                  

        if (read(cfd, *reqLen,sizeof(int))<= 0){
            close(cfd);
            continue;                   /* Failed read; skip request */
        }

        if ((reqLen=read(cfd,reciv,sizeof(char)*reqLen) )<= 0) {
            close(cfd);
            continue;                   /* Failed read; skip request */
        }
        test->commit(new string(reciv,reqLen));
        
    }
}