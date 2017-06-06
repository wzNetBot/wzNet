#include "../common/capnp/wzNet.capnp.h"
#include <iostream>
#include <math.h>
#include <capnp/ez-rpc.h>
#include <kj/debug.h>

using namespace std;

/*
class WzNetClient final : public WZNet::Function::Server {
public:
    kj::Promise<kj::String> wzVersion();
    kj::Promise<void> call(CallContext context){
        auto params = context.getParams().getParams();
        KJ_REQUIRE(params.size() == 2, "wrong number of parameters.");
        context.getResults().setValue(pow(params[0], params[1]));
        return kj::READY_NOW;
    }
};
*/

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " HOST:PORT\n"
                                             "Connects to the wzNet server at the given address and "
                                             "does some RPCs." << std::endl;
        return 1;
    }

    capnp::EzRpcClient client(argv[1]);
    WzNet::Client cl = client.getMain<WzNet>();

    auto& waitScope = client.getWaitScope();
    {
	std::cout << "requesting wzVersion..." << endl;
	std::cout.flush();

	auto request = cl.wzVersionRequest();

	auto evalPromise = request.send();
	auto response = evalPromise.wait(waitScope);
	auto ver = response.getValue();

	std::cout << "wzVer: " << ver.cStr() << endl;
	
/*
        std::cout << "Using a callback... ";
        std::cout.flush();

        WZNet::Function::Client add = nullptr;

        {
            auto request = cl.getOperatorRequest();
            request.setOp(WZNet::Operator::ADD);
            add = request.send().getFunc();
        }

        auto request = cl.evaluateRequest();

        auto powCall = request.getExpression().initCall();
        powCall.setFunction(kj::heap<WZNetClient>());
        auto powParams = powCall.initParams(2);
        powParams[0].setLiteral(2);

        auto addCall = powParams[1].initCall();
        addCall.setFunction(add);
        auto addParams = addCall.initParams(2);
        addParams[0].setLiteral(4);
        addParams[1].setLiteral(5);

        // send request and wait
        auto response = request.send().getValue().readRequest()
                .send().wait(waitScope);
*/
//        std::cout << "Result:" << response.getValue() << endl;
    }
    return 0;
}
