#include "route.hpp"

#include "server.hpp"

Route::Route(Request::Method method, const std::string& path)
    : method_(method),
      path_(path),
      handler_(nullptr) {}

Route::~Route() {
    delete handler_;
}

void Route::setHandler(RequestHandler* handler) {
    handler_ = handler;
}

Response* Route::handle(Request* req) {
    return handler_->callback(req);
}

bool Route::isMatch(Request::Method method, const std::string& url) {
    if(path_.back() == '*'){
        std::string stripPath = path_.substr(0, path_.size()-1);
        std::string stripUrl = url.substr(0, path_.size()-1);
        return (method_ == method) && (stripUrl == stripPath);
    }
    return (method_ == method) && (url == path_);
}
