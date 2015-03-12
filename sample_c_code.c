#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Author: Tatsumi Suenaga */

typedef struct Book{
	char title[35];
	char author[35];
	int stockNumber;
	float wPrice; //wholesale price
	float rPrice; //retail price
	int wSales; //wholesale quantity purchased by bookstore
	int rSales; //retail quantity purchased by customers
}Book;

typedef struct Node{
	Book data;
	struct Node *next;
}Node;

Node *head = NULL;

//Function add 'returns' a list with nodes with information provided by user. Also ends when user inputs '#'.
void add(Node **head) //line 23
{
	printf("Please enter data about the book(# to stop): \n");
	int go = 1;
	while(go == 1){
		Node *newNode;
		newNode = malloc(sizeof(Node));
		if(newNode != NULL){
			scanf(" %35[^\n]s", (*newNode).data.title);
		
			if((*newNode).data.title[0] != '#'){
				scanf(" %35[^\n]s", (*newNode).data.author);

				scanf(" %d", &(*newNode).data.stockNumber);

				scanf(" %f", &(*newNode).data.wPrice);

				scanf(" %f", &(*newNode).data.rPrice);

				scanf(" %d", &(*newNode).data.wSales);

				scanf(" %d", &(*newNode).data.rSales);
				
				Node *temp = *head;
				if(*head == NULL){
					*head = newNode; //48
					newNode->next = NULL;
					//printf("Success");
				}else if((*head)->data.stockNumber > (*newNode).data.stockNumber){ 
					newNode->next = *head;
					*head = newNode;	//53
					//printf("Success1");
				}else {
					int go = 1;
					while(temp != NULL && go == 1){
						if((*temp).data.stockNumber <= (*newNode).data.stockNumber && ((*temp).next == NULL || temp->next->data.stockNumber > (*newNode).data.stockNumber)){
							newNode->next = temp->next;
							temp->next = newNode;
							go = 0;
							//printf("Success2");
						}		
						temp = temp->next; //go to next node
					}
				}
			} else {
				go = 0;
			}
		} else{
			go = 0;
			printf("newNode in add() did not dynamically allocate properly! Ending program.");
		}
	}
}

//Function addFunc 'returns' an updated list with an added node. Node contains information provided by user.
void addFunc(Node **head){
	Node *newNode;
	newNode = malloc(sizeof(Node));
	if(newNode != NULL){
		printf("Please enter data about the book: \n");
		scanf(" %35[^\n]s", (*newNode).data.title);
		
		scanf(" %35[^\n]s", (*newNode).data.author);

		scanf(" %d", &(*newNode).data.stockNumber);

		scanf(" %f", &(*newNode).data.wPrice);

		scanf(" %f", &(*newNode).data.rPrice);

		scanf(" %d", &(*newNode).data.wSales);

		scanf(" %d", &(*newNode).data.rSales);
		Node *temp = *head;
		if(*head == NULL){
			*head = newNode;
			newNode->next = NULL;
			//printf("Success");
		}else if((*head)->data.stockNumber > (*newNode).data.stockNumber){ 
			newNode->next = *head;
			*head = newNode;
			//printf("Success1");
		}else {
			int go = 1;
			while(temp != NULL && go == 1){
				if((*temp).data.stockNumber <= (*newNode).data.stockNumber && ((*temp).next == NULL || temp->next->data.stockNumber > (*newNode).data.stockNumber)){
					newNode->next = temp->next;
					temp->next = newNode;
					go = 0;
					//printf("Success2");
				}		
				temp = temp->next; //go to next node
			}
		}
	}else {
		printf("newNode in addFunc() did not dynamically allocate properly! Ending program.");
	}
}

//Function prints total revenue(which equals the sum of (retail price * retail quantity)) for all books
void totalRevenue(Node **head){
	float ans = 0.0;
	Node *temp = *head;
	while (temp != NULL){
		ans += (temp->data.rPrice * temp->data.rSales);
		temp = temp->next; //go to next node
	}
	printf("Total Revenue for all books: $%3.2f\n", ans);
}

//Function prints total wholesale cost(which equals the sum of (wholesale price * wholesale  quantity)) for all books
void totalWholesale(Node **head){
	float ans = 0.0;
	Node *temp = *head;
	while (temp != NULL){
		ans += (temp->data.wPrice * temp->data.wSales);
		temp = temp->next; //go to next node
	}
	printf("Total Wholesale Cost for all books: $%3.2f\n", ans);
}

//Function prints total profit (which equals total revenue - total wholesale)
void totalProfit(Node **head){
	float ans = 0.0;
	float ans2 = 0.0;
	Node *temp = *head;
	while (temp != NULL){
		ans += (temp->data.rPrice * temp->data.rSales);
		ans2 += (temp->data.wPrice * temp->data.wSales);
		temp = temp->next; //go to next node
	}
	printf("Total Profit for all books: $%3.2f\n", ans - ans2);

	/* Comment: I chose to redo functions totalRevenue and totalWholesale in this function
         * when I could have just called those functions instead if they returned floats, because
         * I wanted to utilize the function pointer. Also the runningtime for this function should be
	 * the same, if not less than doing the two functions seperately. 
	 *
	 * This reasoning was used for function avgPPS as well.
         */
}


//Function prints the number of sales(which equals the sum of retail quantity)for all books
void totalSales(Node **head){
	int ans = 0;
	Node *temp = *head;
	while (temp != NULL){
		ans += (temp->data.rSales);
		temp = temp->next; //go to next node
	}
	printf("Total Sales for all books: %3.2f\n", ans);
}

//Function prints average profit per sale (which equals total profit / total Sales)
void avgPPS(Node **head){
	float ans = 0.0;
	float ans2 = 0.0;
	float ans3 = 0.0;
	Node *temp = *head;
	while (temp != NULL){
		ans += (temp->data.rPrice * temp->data.rSales);
		ans2 += (temp->data.wPrice * temp->data.wSales);
		ans3 += (temp->data.rSales);
		temp = temp->next; //go to next node
	}
	printf("Average Profit Per Sales for all books: $%3.2f\n", (ans - ans2)/ans3 );
}

//Function prints the titles of the books in the list
void bookList(Node **head){
	Node *temp = *head;
	while (temp != NULL){
		printf("%s \n", (*temp).data.title);
		temp = temp->next; //go to next node
	}
}

//Function deletes a book from the list if user inputted title is found. If title not found, error message is sent.
void delete(Node **head){
	char title[35];
	Node *temp = *head;
	Node *prior = NULL;
	int notFound = 1;
	printf("Enter title to be eliminated: ");
	scanf(" %35[^\n]s", title);
	while (temp != NULL && notFound != 0){
		notFound = strcmp(title, temp->data.title);
		if (notFound == 0) {
			if (prior == NULL){
				*head = temp->next;
			} else {
				prior->next = temp->next;
			}
			printf("String %s found and terminated\n", title);
		} 
		prior = temp;
		temp = temp->next; //go to next node
	}
	if (notFound != 0 && *head != NULL) {
		printf("Title %s not found\n", title);
	}else if(notFound != 0 && *head == NULL){
		printf("Title %s not found as the list is empty!\n", title);
	}
	
}

//Function prompts options for user (from 1 - 9), then redirects chosen option to function via function pointer.
void options(Node **head)
{
	int choice;
	Node *temp = *head;
	void (*fp[8])(Node**);
	fp[0] = totalRevenue;
	fp[1] = totalWholesale;
	fp[2] = totalProfit;
	fp[3] = totalSales;
	fp[4] = avgPPS;
	fp[5] = bookList;
	fp[6] = addFunc;
	fp[7] = delete;
	
	while (choice != 9){
		printf("\nHere are your options: \n");
		printf("1. Get Total Revenue\n2. Get Total Wholesale Cost\n3. Get Total Profit\n4. Total Number of Sales\n5. Get Average Profit Per Sale\n");
		printf("6. Print Book List\n7. Add Book\n8. Delete Book\n9. Exit\n");
		printf("Enter choice number: ");
		scanf(" %d", &choice);
		
		if (choice != 9 ){
			(fp)[choice - 1](&temp);
		}
	}
	if(choice == 9) {
		printf("Goodbye!");
	}
}

int main(void){
	add(&head);
	if(head != NULL){
		options(&head);
	}
	return(0);
	free(head);
}
