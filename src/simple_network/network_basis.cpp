/**\file
 * \brief
 * NetworkBasis class definition
 * @version 23.07.2021
 * @author João Pedro Carvalho de Souza
 */

#include "network_basis.h"

namespace simple_network {

    /// Network base class
    NetworkBasis::NetworkBasis(){};
    NetworkBasis::~NetworkBasis(){}

    void NetworkBasis::setTarget(int _protocol, std::string ip_address, unsigned short _port){
        setProtocol(_protocol);
        setAddress(ip_address);
        setPort(_port);
    }

    std::string NetworkBasis::getOutputMSG(){
        return output_string_;
    }

    void NetworkBasis::setProtocol(int _in) {
        protocol_ = _in;
    }

    void NetworkBasis::setAddress(std::string _in) {
        ip_address_ = _in;
    }

    void NetworkBasis::setPort(unsigned short _in) {
        port_ = _in;
    }

}