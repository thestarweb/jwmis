#include "jwweb_net.h"

jwweb_net* jwweb_net::selfobj=NULL;
jwweb_net* jwweb_net::get(){
    if(selfobj==NULL)selfobj=new jwweb_net();
    return selfobj;
}

jwweb_net::jwweb_net()
{
    yzm_ui=new yzm();
    yzm_ui->hide();
}
void jwweb_net::get_info(jw_info_callback jw){
    yzm_ui->show();
}

