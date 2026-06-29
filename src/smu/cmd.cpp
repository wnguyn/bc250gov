#include "cmd.hpp"

Smu::Smu(bool queue, std::string bdf, uint16_t timeout) : trans(bdf){
   this->trans = CyanTransport(buf);


};
