#include "server/server.h"

int main() {
  // TEST BENCH
//  AsyncLog4Q::set_level(AsyncLog4Q::Level::Warn);
//  signal(SIGPIPE, [](int signum) { /*AsyncLog4Q_Warn("Receive a SIGPIPE.");*/ });

  signal(SIGPIPE, [](int signum) { AsyncLog4Q_Warn("Receive a SIGPIPE."); });
  QWebServer q_web_server;
  q_web_server.Start();
  return 0;
}
