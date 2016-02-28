#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <memory>
#include <SDL.h>

namespace scenevr {

class Connector {

  public:
    typedef std::shared_ptr<Connector> Ptr;

    static Ptr create(std::string url) { 
      return std::make_shared<Connector>(url); 
    }

    Connector(const std::string url);
    // ~Connector();

    void connect();

  private:
    std::string url;
};

}

#endif
