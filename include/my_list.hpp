#include <iostream>
#include <fstream>

using namespace std;

typedef struct node{
    int val;
    node *next;
    node *prev;
}* list;

list head_insert (list l, int el);

list insert_ordered(list head, int el);

void print_reverse(list head, const char *filename);

void print_reverse_helper(list head, ofstream& outputFile);

void delete_list(list head);









// #include <iostream>
// #include <cstdlib>
// #include <ctime>

// using namespace std;

// struct lista {
//     int val;
//     lista *next;
// };

// typedef lista* p_lista;

// void print_list(p_lista head){
// 	while (head!=NULL){
// 		cout << head->val << '\t';
// 		head = head->next ;
// 	}
//     cout << endl;
// }



// p_lista head_insert (p_lista head, int el){
//     p_lista tmp_head = new lista;
//     tmp_head->val = el;
//     tmp_head->next = head;
//     return(tmp_head);
// }

// p_lista tail_insert (p_lista l, int el){
//     if( l == NULL) {
// 		p_lista new_l = new lista;
// 		new_l->next = NULL;
//         new_l->val = el;
// 		l = new_l;
// 		return l;
// 	}else{
// 		l -> next = tail_insert(l->next, el);
// 		return l;
// 	}
// }

// p_lista new_level(p_lista l, int n){
// 	if(l == NULL) {
// 		l = new lista;
//         l->val = n;
// 		l->next = NULL;
// 		return l;
// 	} else {
// 		p_lista new_l = new lista;
// 		new_l->next = NULL;
// 		l->val = n;
// 		l->next = new_l;
// 		return l -> next;
// 	}
// }

// p_lista create_Random_List_by_head(const int length) {
// 	p_lista ptrList = NULL;
// 	srand((unsigned)time(0));

// 	for (int i = 0; i < length; i++) {
// 		ptrList = head_insert(ptrList, rand() % 20);
//         p_lista tmp_ptr = ptrList;
//         print_list(tmp_ptr);
//         cout << endl;    }

// 	return ptrList;
// }

// p_lista create_Random_List_by_tail(const int length) {
//     p_lista ptrList, tmp;
//     tmp = new lista;

//     ptrList = tmp;
//     srand((unsigned)time(0));

//     for (int i = 0; i < length; i++){
//         tmp->val = rand() % 20;
//         if(i < length - 1){
//             tmp->next = new lista;
//             tmp = tmp->next;
//         }else{
//             tmp->next = NULL;
//         }
//     }

//     return ptrList;
// }



// double get_avarage(p_lista list){
//     double media = 0.0;
//     int counter = 0;

//     while (list!=NULL){
//         media += list->val, counter++;
//         list = list->next;
//     }
//     media /= counter;
//     return media;
// }

// int get_value_closeest_to_avarage(p_lista list){
//     double media = get_avarage(list);
//     double distance, tmp_distance;
//     int winner;
//     bool found = false;

//     winner = list->val;
//     list = list->next;
//     //calcolo la prima distanza
//     if(media > winner) distance = media - (double) winner;
//     else if(media == (double) winner ) found =true;
//     else if(media < winner) distance = (double) winner - media;

//     while (list!= NULL && !found){
//         if(media > list->val) tmp_distance = media - (double) list->val;
//         else if(media == (double) list->val ) found =true, winner = list->val;
//         else if(media < list->val) tmp_distance = (double) list->val - media;
//         if (!found && distance > tmp_distance){
//             distance = tmp_distance;
//             winner = list->val;
//         }
//     }
//         list = list->next;
//     return winner;
// }

// int get_last_val(p_lista list){
//     // Precondition: list != NULL
//     while(list->next != NULL)
//         list = list->next;

//     return list->val;
// }


// p_lista delete_node(p_lista list, int el){
//     bool found = false;
//     p_lista head, list_before;
//     head = list;
//     while(list->next !=NULL && !found){

//         if(list->val == el)     //esce se trova il nodo da eliminare
//             found = true;
//         else
//             list_before = list,
//             list = list->next;
//     }
//     if(found){
//         list_before->next = list->next;
//         delete list;   //garbage collector
//     }
//     return(head);
// }


// p_lista delete_multiples(p_lista list, int n){
//     p_lista head, list_before = list, temp = list;
//     head = list, list_before;
//     bool is_first =true;

//     while(list != NULL){
//         if (list->val % n == 0){    //se è multiplo

//             if(is_first){           //se è il primo ed è multiplo
//                 list = list->next;
//                 head = list;
//             } else{                 //se non è l'ultimo ed è multiplo
//                 list_before->next = list->next;
//             }
//         }else{                      //se non è multiplo
//             list_before = list;
//             list = list->next;
//             is_first = false;
//         }
//     }


//     return head;
// }


// p_lista delete_multip_2(p_lista list, int n){
//     p_lista before, tmp = list, head;

//     while (tmp->val % n == 0){   //condizione
//         before = tmp;
//         head = tmp = tmp->next;
//         delete before;
//     }
//     head = tmp;
//     before = tmp;
//     tmp = tmp->next;

//     while(tmp != NULL){
//         if(tmp->val % n == 0){  //cancello
//             before->next= tmp->next;
//             delete tmp;
//         }else{                  //skippo
//             before = tmp;
//             tmp = tmp->next;
//         }
//     }

//     return head;
// }
