#ifndef testarrayLine_h
#define testarrayLine_h

#ifdef __cplusplus
  extern "C" {
#endif
class testarrayLine{


private:
	bool lineSensor[8];
	SensorBar arrayLine;
public:
	testarrayLine();
	static void loopArrayLineTest();

};


#ifdef __cplusplus
  }
#endif
#endif