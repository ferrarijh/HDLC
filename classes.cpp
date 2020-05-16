#include <iostream>
#include <cstdlib>
#include <ctime>
#include "classes.h"

double MyRand(double n1, double n2) {
	return n1 + (n2-n1) * rand() / RAND_MAX;
}

double MyRand2(double avg, double disp) {
	return avg * (1 - (disp / 100)) + 2 * avg * (disp / 100) * rand() / RAND_MAX;
}

Dataframe::Dataframe() {
	srand(time(NULL));
	double temp;
	for (int i = 0; i < 20; i++) {
		temp = ('z' - 'a') * rand() / RAND_MAX;
		data.append(1, 'a' + (int)temp);
	}
	bits3 = 0;
}

void Dataframe::Init() {
	data.clear();
	double temp;
	for (int i = 0; i < 20; i++) {
		temp = ('z' - 'a') * rand() / RAND_MAX;
		data.append(1, 'a' + (int)temp);
	}
	bits3 = !bits3;
}

void Dataframe::NewData() {
	data.clear();
	double temp;
	for (int i = 0; i < 20; i++) {
		temp = ('z' - 'a') * rand() / RAND_MAX;
		data.append(1, 'a' + (int)temp);
	}
}

int Dataframe::GetBITS3() const {
	return this->bits3;
}

std::ostream& operator<<(std::ostream & os, const Dataframe & df) {
	os << "[" << df.data << "]";
	return os;
}

Status::Status():timer(0), cnt_success(0), cnt_fail(0), state(LOST){}

void Status::SetQ(double _time) {
	int num = _time / 20 * 3;
	double temp = 0;
	for (int i = 0; i < num; i++) {
		temp += MyRand2(20, 10);
		queue_timeline.push(temp);
	}
}

void Status::QPop() {
	this->queue_timeline.pop();
}
double Status::QFront() const {
	return this->queue_timeline.front();
}

void Status::SetProb(double loss, double corrupt) {
	this->prob_loss = loss;
	this->prob_corrupt = corrupt;
}

double Status::GetTimer() const {
	return this->timer;
}

void Status::IncremTime(double _time) {
	this->timer += _time;
}

int Status::GetSucc() const {
	return this->cnt_success;
}

void Status::IncremSucc() {
	this->cnt_success += 1;
}

int Status::GetFail() const {
	return this->cnt_fail;
}

void Status::IncremFail() {
	this->cnt_fail += 1;
}

void Status::SetState() {
	double _random = MyRand(0, 1);
	//std::cout << "(_random : "<<_random << ")"<<std::endl;
	if (_random < (1 - prob_loss) * (1-prob_corrupt))
		state = SUCCESS;
	else if (_random < 1 - prob_loss)
		state = CORRUPT;
	else
		state = LOST;
}

State Status::GetState() const {
	return this->state;
}

void Status::QShow() {
	int num = this->queue_timeline.size();
	for (int i = 0; i < num; i++) {
		std::cout << queue_timeline.front() << std::endl;
		queue_timeline.pop();
	}
	this->SetQ((int)num * 20);
}