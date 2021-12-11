#include <thread>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

int nextIn = 0;
int nextOut = 0;
const int n = 99999999;
const int sec = 1;
int buf[n] = {};

void producer() {
		cout << "producer running\n";
		while (true) {
			int k1 = rand() % sec + 1;

			for (int i = 0; i < k1; i++) {
				buf[nextIn + k1 % n] = 1;
				//cout << "producer";
			}
			nextIn = nextIn + k1 & n;
		}

		int t1 = rand() % sec + 1;
		std::this_thread::sleep_for(chrono::seconds(t1));
	}
	
void consumer() {
	cout << "consumer running\n";
	while (true) {
		int t2 = rand() % sec + 1;
		//std::this_thread::sleep_for(chrono::seconds(1));
		int k2 = rand() % sec + 1;

		for (int i = 0; i < k2; i++) {
			int data = buf[nextOut + k2 % n];
			//cout << "consumer";

				if (data > 1) {
					cout << "\nRace condition detected. Exiting program.\n";
					exit(EXIT_FAILURE);
				}

				nextOut = nextOut + k2 % n;
			}
		}
	}
	
int main() {
	
	cout << "starting threads...\n";
    
    srand(time(NULL));
	std::thread producerThread(producer);
	std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();
}






