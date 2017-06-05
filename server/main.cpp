#include "../common/capnp/wzNet.capnp.h"
#include <iostream>
#include <capnp/ez-rpc.h>
#include <kj/debug.h>


class WZNetImpl final: public WZNet::Server {
public:
  kj::Promise<void>
};

int main(int argc, const char* argv[]) {
  if (argc != 2) {
    std::cerr << "usage: " << argv[0] << " ADDRESS[:PORT]\n"
        "Runs the server bound to the given address/port.\n"
        "ADDRESS may be '*' to bind to all local addresses.\n"
        ":PORT may be omitted to choose a port automatically." << std::endl;
    return 1;
  }

  // Set up a server.
  capnp::EzRpcServer server(kj::heap<CalculatorImpl>(), argv[1]);

  // Write the port number to stdout, in case it was chosen automatically.
  auto& waitScope = server.getWaitScope();
  uint port = server.getPort().wait(waitScope);
  if (port == 0) {
    // The address format "unix:/path/to/socket" opens a unix domain socket,
    // in which case the port will be zero.
    std::cout << "Listening on Unix socket..." << std::endl;
  } else {
    std::cout << "Listening on port " << port << "..." << std::endl;
  }

  // Run forever, accepting connections and handling requests.
  kj::NEVER_DONE.wait(waitScope);
}
