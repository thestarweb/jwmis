#include "http_response.h"

http_response::http_response(QString info)
{
    content="";
    http_state=0;
    read_state=0;
    content_lenth=0;
    this->_info=info;
}
QString http_response::info(){
    return _info;
}

