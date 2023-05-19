#include <iostream>
#include <cstring>
#include <exception>

#include "extern/oscpack/oscpack/osc/OscReceivedElements.h"
#include "extern/oscpack/oscpack/osc/OscPacketListener.h"
#include "extern/oscpack/oscpack/ip/UdpSocket.h"

#define PORT 9001
#define ENDL "\n" // endline without flushing

class ExampleServer : public osc::OscPacketListener {
    protected: 
        /**
         * @brief Handler for arbitrary OSC packages that arrive on this server
         * @param m The osc message. 
         *        Bundles are handled implicitely by the superclass
         * @param remoteEntpoint Information about the endpoint
        */
        void ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint) override {
            try {
                // process the message: 
                if("/dome/azimuth" == std::string{m.AddressPattern()}) {
                    // create argument iterator. Another option would be the ArgumentStream 
                    osc::ReceivedMessageArgumentIterator itr {m.ArgumentsBegin()};        
                    // get the 1. argument
                    const auto channel {(itr++)->AsInt32()};
                    // get the 2. argument
                    const auto azimuth {(itr++)->AsInt32()};
                    // reflection is also supported: (args*)->asBool() checks if the current argument is a bool!
                    if(itr != m.ArgumentsEnd()) {
                        throw osc::ExcessArgumentException("Too many arguments have been provided from the sender!");
                    }
                    // do something with the arguments
                    std::cout << "received /dome/azimuth " << channel << " " << azimuth << ENDL;
                }
            } catch(osc::Exception& e) {
                std::cerr << "error while parsing message:" << m.AddressPattern() << ": " << e.what() << ENDL;
            }
        }
};

/**
 * @brief Example program to receive some messages over osc
*/
int main(void) {
    ExampleServer server {};
    // set up the server to listen on the given port
    UdpListeningReceiveSocket s {IpEndpointName{IpEndpointName::ANY_ADDRESS, PORT}, &server};
    std::cout << "press ctrl-c to end" ENDL;
    // start the server
    s.RunUntilSigInt();
    return 0;
}