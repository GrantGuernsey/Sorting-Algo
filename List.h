#ifndef LIST
#define LIST

#include <iostream>
#include <string>
#include <stack>
#include "Student.h"
using namespace std;


class List{
private:
    /* NODE CLASS */
    class Node{
    public:
        Student data;
        Node* prev;
        Node* next;

        Node(Student data, Node* prev, Node* next = nullptr){
            this->data = data;
            this->prev = prev;
            this->next = next;
        }
    };

    /* ERROR CLASSES */
    class Empty{};
    class DNE{};

    /* LIST ATTRIBUTES */
    Node* head;
    int len, itr;

    /* LIST HELPERS */
    void clear(Node* cur){
        //Base Case
        if (cur == nullptr) return;

        //Recursion
        clear(cur->next);

        //Deletion
        if (cur != head) cur->prev->next = nullptr;
        else head = nullptr;
        delete cur;
    }

public:
    /* LIST CONSTRUCTOR */
    List(){
        head = nullptr;
        len = 0;
        itr = 0;
    }

    /* LIST UTILITY METHODS */
    bool isEmpty(){
        return (head == nullptr) && (len == 0);
    }
    int getLen(){
        return len;
    }
    int getCompCount(){
        return itr;
    }

    /* LIST METHODS */
    void addItem(Student data){
        //Empty list insertion
        if (head == nullptr){
            head = new Node(data, nullptr);
        }

        //Non-empty list insertion
        else{
            Node* cur = head;
            while (cur->next != nullptr && cur->data < data){
                cur = cur->next;
            }

            //Insert at head
            if (cur == head){
                head->prev = new Node(data, nullptr, head);
                head = head->prev;
            }

            //Insert at tail
            else if (cur->next == nullptr && cur->data < data){
                cur->next = new Node(data, cur);
            }

            //Insert elsewhere
            else{
                cur->prev->next = new Node(data, cur->prev, cur);
                cur->prev = cur->prev->next;
            }
        }

        len += 1;
    }
    bool contains(Student trgt){
        //Search loop
        Node* cur = head;
        while (cur != nullptr && cur->data != trgt){
            cur = cur->next;
        }

        //Return
        if (cur == nullptr) return false;
        return true;
    }
    Student getItem(Student trgt){
        //Empty list handling
        if (isEmpty()) throw Empty();

        //Search loop
        Node* cur = head;
        while (cur != nullptr && cur->data != trgt){
            cur = cur->next;
            itr += 1;
        }

        //Return
        if (cur == nullptr) throw DNE();
        return cur->data;
    }
    Student removeItem(Student trgt){
        //Search loop
        Node* cur = head;
        while (cur != nullptr && cur->data != trgt){
            cur = cur->next;
        }

        //Not found
        if (cur == nullptr) throw DNE();

        //Deletion
        if (cur != head){
            cur->prev->next = cur->next;
            if (cur->next != nullptr) cur->next->prev = cur->prev;
        }
        else head = head->next;

        //Return
        Student val = cur->data;
        len -= 1;
        delete cur;
        return val;
    }

	/* DISPLAY METHODS ASCENDING */
	void printOut(){
		Node* f = head;
		while(f->next != nullptr){
			cout << f->data << endl;
			f = f->next;
		}
	}
	void printFirst(){
		Node* f = head;
		while(f->next != nullptr){
			cout << f->data.firstName << " " << f->data.lastName << endl;
			f = f->next;
		}
	}
	void printLast(){
		Node* f = head;
		while(f->next != nullptr){
			cout << f->data.lastName << ", " << f->data.firstName << endl;
			f = f->next;
		}
	}

	/* DISPLAY METHODS DESCENDING */
	void printROut(){
		Node* cur = head;

		//Reach end
		while(cur->next != nullptr){
			cur = cur->next;
		}

		//Reach beginning
		while(cur != nullptr){
			cout << cur->data << endl;
			cur = cur->prev;
		}
	}
	void printRLast(){
		stack<Student> x;
		Node* cur = head;
		while(cur != nullptr){
			x.push(cur->data);
			cur = cur->next;
		}
		while(!x.empty()){
			cout << x.top().lastName << ", " << x.top().firstName << endl;
			x.pop();
		}
	}
	void printRFirst(){
		Node* cur = head;

		//Reach end
		while(cur->next != nullptr){
			cur = cur->next;
		}

		//Reach beginning
		while(cur != nullptr){
			cout << cur->data.firstName << " " << cur->data.lastName << endl;
			cur = cur->prev;
		}
	}

	/* SORTING METHODS */
	Node* swap(Node* one, Node* two){
		Node* three = two->next;
		two->next = one;
		one->next = three;
		return two;
	}

	//for first name
	void bubbleSort(){
		Student buffer;
		Node* cur = nullptr;
		int count = 0, end = len - 1;
	
		while(count < end){
			//Reset
			cur = head;
			count = 0;
	
			for (int n = 0; n < end; n++){
				//Convert first name to an int
				int right = stoi(cur->data.firstName);
				int left = stoi(cur->next->data.firstName);
	
				//Perform swap or update failed swap count
				if (right > left){
					buffer = cur->next->data;
					cur->next->data = cur->data;
					cur->data = buffer;
				}
				else count++;
	
				//Move cur
				cur = cur->next;
			}
		}
	}

	//for last name
	void insertionSort(){
		int idx = 1;
		Student buffer;
		Node *h;
		h = head;
		while (idx < len){
			for (int cur = idx; cur > 0; cur--){
			  
				if (h->data > h->next->data){
					buffer = h->next->data;
					h->next->data = h->data;
					h->data = buffer;
				}
				else break;
			}
			idx++;
		}
    }

	//for mnumber
	void merge(){
		MergeSort(&(head));
	}
	void MergeSort(Node** front){
	    Node* topNode = *front;
	    Node* one;
	    Node* two;
	 
	    
	    if ((topNode == nullptr) || (topNode->next == nullptr)) {
	        return;
	    }
	 
	
	    split(topNode, &one, &two);
	 
	
	    MergeSort(&one);
	    MergeSort(&two);
	
	    *front = mergeSorting(one, two);
	}
	Node* mergeSorting(Node* x, Node* y){
	    Node* result = nullptr;
	 
	    if (x == nullptr){
	        return y;
			}
	    else if (y == nullptr){
	        return x;
			}
	 		int left = stoi(x->data.lastName);
			int right = stoi(y->data.lastName);
	    if (left < right){ //x->data < y->data
	        result = x;
	        result->next = mergeSorting(x->next, y);
	    }
	    else{
	        result = y;
	        result->next = mergeSorting(x, y->next);
	    }
	    return result;
	}
	void split(Node* base,Node** front, Node** back){
	    Node* first;
			first = base;
			
	    Node* second;
	    second = base->next;
	
	    while (second != nullptr) {
	        second = second->next;
	        if (second != nullptr) {
	            first = first->next;
	            second = second->next;
	        }
	    }
	 
	    *back = first->next;
		  *front = base;
	    first->next = nullptr;
	}
};

#endif