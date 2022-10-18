#include "List.h"
#include "Student.h"

#include <cmath>
#include <cstdlib>
#include <chrono>
#include <string>
#include <iostream>
using namespace std;

typedef std::chrono::high_resolution_clock Clock;

/* HELPER FOR RADIX */
int mod(int n, int d){
    return (n / (int)pow(10, d)) % 10;
}


void bubble(int* arr, int len){
    int swapCount = 0, buffer, next;

    while(swapCount < len - 1){
        swapCount = 0; //Reset

        for (int cur = 0; cur < len - 1; cur++){
            next = cur + 1;

            if (arr[cur] > arr[next]){
                buffer = arr[next];
                arr[next] = arr[cur];
                arr[cur] = buffer;
            }
            else swapCount++;
        }
    }
}
void insertion(int* arr, int len){
    int idx = 1, buffer, prev;

    while (idx < len){
        for (int cur = idx; cur > 0; cur--){
            prev = cur - 1;

            if (arr[prev] > arr[cur]){
                buffer = arr[cur];
                arr[cur] = arr[prev];
                arr[prev] = buffer;
            }
            else break;
        }
        idx++;
    }
}
void merge(int* arr, int start, int len){
    //Split, then merge
    if (len > 2){
        int left, right; //New lengths
        int idxL, idxR;  //Indices for start

        int table[len];   //Array for the merge
        int stopL, stopR; //Boundaries for the merge

        //Update lengths with even len
        if (len % 2 == 0){
            left = len / 2;
            right = left;
        }

        //Update lengths with odd len
        else{
            left = len / 2;
            right = left + 1;
        }

        //Update left starting idx and stop condition
        idxL = start;
        stopL = start + left;

        //Update right starting idx and stop condition
        idxR = start + left;
        stopR = idxR + right;

        //Left and right calls
        merge(arr, idxL, left);
        merge(arr, idxR, right);

        //Merge left and right into table
        int idxT = 0;
        while(idxL < stopL || idxR < stopR){

            //Both aren't done yet
            if (idxL < stopL && idxR < stopR){
                if (arr[idxL] < arr[idxR]){
                    table[idxT] = arr[idxL];
                    idxL++;
                }
                else{
                    table[idxT] = arr[idxR];
                    idxR++;
                } 
                idxT++;
            }

            //Left is done
            else if (idxR < stopR){
                table[idxT] = arr[idxR];
                idxR++;
                idxT++;
            }

            //Right is done
            else if (idxL < stopL){
                table[idxT] = arr[idxL];
                idxL++;
                idxT++;
            }
        }

        //Update arr using table
        for (int n : table){
            arr[start] = n;
            start++;
        }
    }

    //Sort pair from split, len < 2 is the base case
    else if (len == 2){
        if (arr[start] > arr[start + 1]){
            int buffer = arr[start + 1];
            arr[start + 1] = arr[start];
            arr[start] = buffer;
        }
    }
}

int quickSwaps(int arr[], int start, int end){
    int pivot = arr[end];

    int count = start - 1;

    for (int curr = start; curr <= end - 1; curr++){
        if (arr[curr] <= pivot){
            count++;
            swap(arr[count], arr[curr]);
        }
    }
    //Putting pivot in correct spot
    swap(arr[count+1], arr[end]);
    return(count + 1);
}
int quickRand(int arr[], int start, int end){
    //Generating random val
    int random = rand() % (end - start) + start;

    swap(arr[random], arr[end]);
    return quickSwaps(arr, start, end);
}
void quick(int arr[], int start, int end){
    if (start < end){
        int randPosition = quickRand(arr, start, end);

        //Sorting other sides of the value recursively
        quick(arr, start, randPosition - 1);
        quick(arr, randPosition + 1, end);
    }
}

int* count(int* arr, int len){
    int cur, idx;            //Used for indexing
    int* ans = new int[len]; //Output array

    //Find max value
    int max = arr[0];
    for (cur = 1; cur < len; cur++){
        if (arr[cur] > max) max = arr[cur];
    }

    //Create tally table
    max++;
    int* table = new int[max];

    //Update tally table
    for (cur = 0; cur < len; cur++){
        table[arr[cur]]++;
    }

    //Running sum of table
    for (cur = 1; cur < max; cur++){
        table[cur] += table[cur - 1];
    }

    //Populate output array
    for (cur = len - 1; cur >= 0; cur--){
        idx = table[arr[cur]] - 1; //Get new index
        ans[idx] = arr[cur];       //Insert item at new index
        table[arr[cur]]--;         //Decrement tally
    }

    return ans;
}
void radix(int* arr, int len){
    int cur;                  //For loop iterator
    int idx;                  //Keeps track of new indices for output
    int place = 0;            //Digits place
    int table[10];            //Table of keys
    int* ans = new int[len];  //Output array

    //Find max value
    int max = 0;
    for (cur = 0; cur < len; cur++){
        if (arr[cur] > max) max = arr[cur];
    }

    //Get iteration count
    int halt = 0;
    while(max > 0){
        max /= 10;
        halt++;
    }

    //Conduct radix sort
    while (halt > 0){
        //Reset table
        for (cur = 0; cur < 10; cur++){
            table[cur] = 0;
        }

        //Update tally table
        for (cur = 0; cur < len; cur++){
            max = mod(arr[cur], place);
            table[max]++;
        }

        //Running sum of table
        for (cur = 1; cur < 10; cur++){
            table[cur] += table[cur - 1];
        }

        //Populate output array
        for (cur = len - 1; cur >= 0; cur--){
            //Get new index
            max = mod(arr[cur], place);
            idx = table[max] - 1;

            //Insert item at new index
            ans[idx] = arr[cur];     

            //Decrement tally
            table[max]--;
        }

        //Move results to original array
        for (cur = 0; cur < len; cur++){
            arr[cur] = ans[cur];
        }

        //Update digits place and iteration count
        place++;
        halt--;
    }
    
    delete[] ans;
}

void test(){
    //Controls
    int size;
    cout << "What would you like your size to be? ";
    cin >> size;
    bool runtime = false;
    bool disp = false;

    srand(time(NULL));
    
    if (runtime){
        //Fill test array
        int* test = new int[size];
        for(int n = 0; n < size; n++){
            test[n] = rand() % (2 * size);
        }

        //Time and run algorithm
        auto t1 = Clock::now();
        for (int n = 0; n < 50; n++){
            quick(test, 0, size-1);
        }
        auto t2 = Clock::now();
        cout << "Delta T: " <<chrono::duration_cast<chrono::nanoseconds>((t2 - t1) / 5).count()<< " ns" << endl;
        
        //Print resulting array
        if (disp){
            for (int n = 0; n < size; n++){
                cout << test[n] << ' ';
            }
            cout << endl;
        }
    }
}

int StudentList(){
	/* LINKED LIST SORTING */
	int option;
	int option2;
	cout << "Select 1 for first name sort, 2 for last, 3 for mnumber" << endl;
	cin >> option;
	cout << "Select 1 for accending, 2 for decending" << endl;
	cin >> option2;
	List coc;
	for(int n = 0; n < 50; n++){
		int mnum = 10000000 + (rand() % (99999999 - 10000000 + 1 ));
		int fname = 100 + (rand() % (999 - 100 + 1 ));
		int lname = 100 + (rand() % (999 - 100 + 1 ));
		Student* newStudent = new Student(to_string(mnum), to_string(fname), to_string(lname)); 
		coc.addItem(*newStudent); 
	}
	if(option == 1){
		coc.bubbleSort();
		if(option2 == 1){
			coc.printFirst();
		}
		else{
			coc.printRFirst();
		}
	}
	else if(option == 2){
		coc.merge();
		if(option2 == 1){
			coc.printLast();
		}
		else{
			coc.printRLast();
		}
	}
	else if(option == 3){
		coc.insertionSort();
		if(option2 == 1){
			coc.printOut();
		}
		else{
			coc.printROut();
		}
	}
	else{
		cout << "Enter something in the range next time!";
	}
	return 0;
}

int main(){
  int option, cringeVariable;
  cout << "Type 1 to run the test program." << endl;
  cout << "Type 2 to run the Student Sort." << endl;
  cin >> option;

  if (option == 1){
    test();
  }
  else if (option == 2){
    cringeVariable = StudentList();
  }
  else{
    cout << "Incorrect value, goodbye." << endl;
  }
}