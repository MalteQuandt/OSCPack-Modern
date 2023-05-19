#include <chrono>
#include <thread>

#include <osc/OscOutboundPacketStream.h>
#include <ip/UdpSocket.h>
#include <osc/OscTypes.h>

#define ADDRESS "127.0.0.1"
#define PORT 9001
#define OUTPUT_BUFFER_SIZE 1024

using namespace std::chrono_literals;

/**
 * @brief Example Program to send some messages over osc
*/
int main(void) {
    // open socket
    UdpTransmitSocket transmitSocket {IpEndpointName(ADDRESS, PORT)};

    // prepare the osc packet
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p (buffer, OUTPUT_BUFFER_SIZE);

    // send the message: /dome/azimuth 1 i (with i in [0, 360])
    for(auto i{0}; i <= 360; i++) {

        p << osc::BeginMessage("/dome/azimuth") << 1 << i << osc::EndMessage;
        // send the packet over the network
        transmitSocket.Send(p.Data(), p.Size());
        // clear the message queue, so that the buffer can be reused
        p.Clear();

        std::this_thread::sleep_for(2ms);
    }
    return 0;
}