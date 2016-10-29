#ifndef JWWEB_NET_H
#define JWWEB_NET_H

#include <network/http.h>
#include <ui/yzm.h>
class netcb{

};
typedef void(netcb::*jw_info_callback)(QString);

class jwweb_net
{
public:
    static jwweb_net* get();
    void get_info();
private:
    static jwweb_net* selfobj;
    jwweb_net();
    yzm *yzm_ui;

};

#endif // JWWEB_NET_H
