#include <iostream>
#include <vector>
#include <time.h>

using namespace std;
#define INF 0x7FFFFFFF 
#define L 1000
int randomOptions[8];
void generateRandom(){
	for (int i = 0; i < 8; i++)
		randomOptions[i] = i;

	for (int n=8,i = 0; i < 8; i++,n--){
		srand(time(0));
		int rnd = rand() % n;
		swap(randomOptions[rnd], randomOptions[n - 1]);
	}
}
struct problem{
	vector<int> column;// position of each queen in every column
	vector<int> initcolumn;// position of each queen in every column at initial state
	int successor[8][8]; // h_n of next move
	int h_n = INF; // h_n of current state
	int inith_n = INF; // h_n of initial state
	problem(){
		for (int i = 0; i < 8; ++i){
			initcolumn.push_back(0);
			column.push_back(0);
		}
			
	}
};

int h(problem q){ // determine h(n) for given columns
	int result = 0;
	for (int i = 0; i < 8; ++i){
		for (int j = i+1; j < 8; ++j){
			if (q.column[i] == q.column[j])
				result++;
			else if (i-q.column[i]  == j-q.column[j])
				result++;
			else if (q.column[i] + i == q.column[j] + j)
				result++;
		}

	}
	return result;
}
bool hill_Climbing(problem &q){ // returns 1 in case of finding an answer
	int min = INF;
	int mini, minj;
	q.inith_n = h(q); // h(n) of initial state

	do{	

		q.h_n = h(q); // finding h(n) of current column

		// counting successors
		for (int i = 0; i < 8; ++i){
			int t = q.column[i];
			for (int j = 0; j < 8; ++j){ // change the position of queen on ith column and determine h(n)
				q.column[i] = j;
				q.successor[j][i] = h(q);
				if (q.successor[j][i] < min){ // find minimum h(n)
					min = q.successor[j][i];
					mini = i; // store coordinate of minimum column
					minj = j;
				}
					
			}

			q.column[i] = t;
		}

		
		q.column[mini] = minj;
	} while (q.h_n && q.h_n!=min);
	
	
	if (q.h_n == 0)
		return 1;

	return 0;	
}
int main(){
	problem x;
	problem min;
	min.h_n = INF;

	int tries = 0;
	bool f = 1;
	do{
		tries++;
		
		for (int i = 0; i < 8; i++){
			generateRandom();
			x.column[i] = randomOptions[i];
			x.initcolumn[i] = x.column[i];
		}

		f = hill_Climbing(x);

		if (min.h_n>x.h_n){
			min.h_n = x.h_n;
			min.inith_n = x.inith_n;
			min.column.swap(x.column);
			min.initcolumn.swap(x.initcolumn);
		}
			
		
	} while (tries <= L && !f);

	if (min.h_n > x.h_n)
		swap(min, x);



	if (min.h_n > 0){
		cout << "BEST ACHIEVEMENT WHITIN " << tries << " TRIES\n";
	}
	else
		cout << "SOLUTION FOUND WITHIN " << tries << " TRIES\n";

	cout << "initial state:\n";
	cout << "h(n) = " << min.inith_n << endl << endl;
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j)
		if (min.initcolumn[j] != i)
			cout << "\t-";
		else
			cout << "\tQ";

		cout << endl << endl;
	}

	cout << "\nFinal state:\n"; 
	cout << "h(n) = " << min.h_n << endl << endl;
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j)
		if (min.column[j] != i)
			cout << "\t-";
		else
			cout << "\tQ";

		cout << endl << endl;
	}

	return 0;
}
