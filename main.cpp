#include <iostream>
#include <cstdlib>
#include "classes.h"

int main() {
	Status st1;
	Dataframe df1;
	double time_set;
	double prob_loss;
	double prob_corrupt;
	int N_r = 0;
	double time_temp55;
	double prev_stat_time;
	
	std::cout << "Simulation time :";
	std::cin >> time_set;
	std::cout << "Loss probability :";
	std::cin >> prob_loss;
	std::cout << "Corruption probability :";
	std::cin >> prob_corrupt;
	st1.SetProb(prob_loss, prob_corrupt);
	st1.SetQ(time_set);
 
	while (st1.GetTimer() <= time_set){
		if ((N_r)>=3) {
			st1.IncremFail();
			df1.NewData();
			N_r = 0;
			std::cout << std::endl;
		}
		//s1.send(r1);
		if (N_r == 0)
			st1.QPop();

		N_r += 1;
		if (st1.GetTimer() >= time_set)
			break;

		if (N_r == 1) {
			std::cout << "[" << st1.GetTimer() << "] ";
			std::cout << "1st trial of sending frame " << df1 << " with SEQ :" << df1.GetBITS3() << std::endl;
		}
		else if (N_r == 2) {
			std::cout << "[" << st1.GetTimer() << "] ";
			std::cout << "2nd trial of sending frame " << df1 << std::endl;
		}
		else if (N_r == 3) {
			std::cout << "[" << st1.GetTimer() << "] ";
			std::cout << "3rd trial of sending frame " << df1 << std::endl;
		}

		prev_stat_time = st1.GetTimer();
		time_temp55 = MyRand2(5.5, 10);
		st1.IncremTime(time_temp55);

		st1.SetState();

		if (st1.GetState()==LOST){	//by 0.1,
			std::cout << ">>Receiver timeout." << std::endl;
			st1.IncremTime(15 - time_temp55);
		}
		else if(st1.GetState()==SUCCESS){
			std::cout << ">>SUCCESS! Receiver sends ACK : " << !df1.GetBITS3() << std::endl << std::endl;
			df1.Init();		//Init inverses seq
			st1.IncremSucc();
			N_r = 0;

			if (st1.GetTimer() < st1.QFront()) { //if queue from layer 3 is empty,
				st1.IncremTime(st1.QFront() - st1.GetTimer());
			}
		}
		else {	//by 0.1, if CORRUPT,
			std::cout<<">>Corrupted frame. Receiver sends NAK."<<std::endl;
			st1.IncremTime(time_temp55);
		}
	}
	std::cout << "=========================================" << std::endl;
	std::cout << "Time passed : " << prev_stat_time << std::endl;
	std::cout << "Successfully sent frames : " << st1.GetSucc() << std::endl;
	std::cout << "Failed frames: " << st1.GetFail() << std::endl;
	

	return 0;
}