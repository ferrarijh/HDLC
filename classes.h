#pragma once
#include <queue>

enum State { LOST, CORRUPT, SUCCESS };

class Dataframe {
	std::string data;
	int bits3;
public:
	Dataframe();
	void Init();
	void NewData();
	int GetBITS3() const;
	friend std::ostream& operator<<(std::ostream& os, const Dataframe& df);
};

class Status {
	double prob_loss;
	double prob_corrupt;
	double timer;
	int cnt_success;
	int cnt_fail;
	State state;
	std::queue<double> queue_timeline;
public:
	Status();
	void SetQ(double _time);
	void QPop();
	double QFront() const;
	void SetProb(double loss, double corrupt);
	double GetTimer() const;
	void IncremTime(double);
	int GetSucc() const;
	int GetFail() const;
	void IncremSucc();
	void IncremFail();
	void SetState();
	State GetState() const;
	void QShow();
};

double MyRand(double n1, double n2);
double MyRand2(double avg, double disp);