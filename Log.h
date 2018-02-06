//#include "Graph.h"
#define MAX_MEMORY 4096

class Log {
public:
  Log();
  void logNode(Node n);
  void clearLog();
protected:
  String startSequence = "START HERE";
private:
  dataAddr = 0;
  static void writeString(String str);

};
