#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/// <summary>
/// Constant value for dynamic formatting of input prompt length.
/// </summary>
static int INPUT_PROMPT_LENGTH = 20;

/// <summary>
/// Constant value for dynamic calculation of output format.
/// </summary>
static int OUTPUT_LENGTH = 14;

/// <summary>
/// Constant value for dynamic intendation of output.
/// </summary>
static int LEFT_PADDING = 8;

/// <summary>
/// Struct to model a date and time reprenstation.
/// It is used to specify a specific moment for measurements.
/// </summary>
struct moment {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
};

/// <summary>
/// Struct to model an mesurement of an imaginary temperature sensor.
/// Every measurement item relates to a specific point in time an temperature in °C.
/// </summary>
struct measurement {
	float temperatureInCelcius;
	struct moment moment;
	struct measurement* next;
};

/// <summary>
/// Helper function to determine whether to moments are equal.
/// Moments are equal if all their date and time parts are equal.
/// </summary>
/// <param name="momentA">Pointer to the first moment struct to compare.</param>
/// <param name="momentB">Pointer to the second moment struct to compare.</param>
/// <returns>TRUE if the two moments are equal, FALSE otherwise.</returns>
bool areEqual(struct moment* momentA, struct moment* momentB) {
	if (momentA->year != momentB->year) return false;
	if (momentA->month != momentB->month) return false;
	if (momentA->day != momentB->day) return false;
	if (momentA->hour != momentB->hour) return false;
	if (momentA->minute != momentB->minute) return false;
	if (momentA->second != momentB->second) return false;
	return true;
}

bool isInChronologicalOrder(struct moment* momentA, struct moment* momentB) {
	struct tm a = { momentA->second, momentA->minute, momentA->hour, momentA->day, momentA->month, momentA->year - 1900 };
	struct tm b = { momentB->second, momentB->minute, momentB->hour, momentB->day, momentB->month, momentB->year - 1900 };
	time_t ta = mktime(&a);
	time_t tb = mktime(&b);
	return difftime(ta, tb) < 0;
}

/// <summary>
/// This pointer references the first node in the singly linked list.
/// It may be used for any list related operations since it serves as the only
/// "entrance point" into the singly linked list.
/// </summary>
struct measurement* head = NULL;


/// <summary>
/// Append a new measurement to the existing singly linked list.
/// If the singly linked list is currently emtpy, the provided values will form the lists first entry.
/// </summary>
/// <param name="year">Year of measurement.</param>
/// <param name="month">Month of measurement.</param>
/// <param name="day">Day of measurement.</param>
/// <param name="hour">Hour of measurement.</param>
/// <param name="minute">Minute of measurement.</param>
/// <param name="second">Second of measurement.</param>
/// <param name="temperature">Temperature of measurement.</param>
void insertAtEnd(int year, int month, int day, int hour, int minute, int second, float temperature) {
	// Pointer to access the lists entries.
	struct measurement* lastNode;

	// Check if list already has an entry.
	// If head references NULL, there's no entry yet.
	if (head == NULL) {
		// Allocate memory for new measurement entry and check if allocation worked.
		if ((head = (struct measurement*)malloc(sizeof(struct measurement))) == NULL) {
			// Allocation failed. Print error message and return.
			printf("Cannot allocate memory.\n");
			return;
		}

		// Assign the given values to the newly created measurement.
		*head = (struct measurement){ temperature,{year, month, day, hour, minute, second} };

		// There's no successor for the new entry yet. Set next-pointer of entry to NULL.
		head->next = NULL;
	}
	else
	{
		// Since head is not NULL, there must be at least one element in the list, yet.
		lastNode = head;

		// Loop through the singly linked list until the last element is reached.
		while (lastNode->next != NULL) {
			lastNode = lastNode->next;
		}

		// Allocate memory for the new entry and check if allocation worked.
		if ((lastNode->next = (struct measurement*)malloc(sizeof(struct measurement))) == NULL) {
			printf("Cannot allocate memory.\n");
			return;
		}

		// Point to freshly allocated memory for new measurement item.
		lastNode = lastNode->next;

		// Assign the given values to the newly created measurement.
		*lastNode = (struct measurement){ temperature, {year, month, day, hour, minute, second} };

		// There's no successor for the new entry yet. Set next-pointer of entry to NULL.
		lastNode->next = NULL;
	}
}

/// <summary>
/// Insert a new measurement at the beginning of the singly linked list.
/// </summary>
/// <param name="year">Year of measurement.</param>
/// <param name="month">Month of measurement.</param>
/// <param name="day">Day of measurement.</param>
/// <param name="hour">Hour of measurement.</param>
/// <param name="minute">Minute of measurement.</param>
/// <param name="second">Second of measurement.</param>
/// <param name="temperature">Temperature of measurement.</param>
void insertAtBeginning(int year, int month, int day, int hour, int minute, int second, float temperature) {

	// TODO: Implement this 

	struct measurement* newNode;

	if ((newNode = (struct measurement*)malloc(sizeof(struct measurement))) == NULL) {
		printf("Cannot allocate memory.\n");
		return;
	}

	*newNode = (struct measurement){ temperature, { year, month, day, hour, minute, second} };

	newNode->next = head;
	head = newNode;
}

/// <summary>
/// Insert a new measurement in relation to its date and time.
/// The new node should be inserted chronologically: Before the first node whose date and time
/// of measurement is later or at exactly the same time than the new nodes date and time.
/// If the singly linked list is empty or the given daten and time information of the new measurement
/// to insert into the singly linked list, the new node should be inserted at the end of the list.
/// </summary>
/// <param name="year">Year of measurement.</param>
/// <param name="month">Month of measurement.</param>
/// <param name="day">Day of measurement.</param>
/// <param name="hour">Hour of measurement.</param>
/// <param name="minute">Minute of measurement.</param>
/// <param name="second">Second of measurement.</param>
/// <param name="temperature">Temperature of measurement.</param>
void insertChronologically(int year, int month, int day, int hour, int minute, int second, float temperature) {

	// TODO: Implement this function

	// Will hold a reference to the node after which the new element needs to be inserted.
	struct measurement* nodeToInsertAfter;

	// Will hold a reference to the node to insert into the singly linked list.
	struct measurement* newNode;

	if (head == NULL) {
		// If there's no head, the list is currently empty. Let's just insert the new node at the beginning.
		insertAtBeginning(year, month, day, hour, minute, second, temperature);
	}
	else
	{
		// Starting from the head, we'll iterate through the singly linked list to look for chronological order.
		nodeToInsertAfter = head;

		// Allocate memory for the new node to insert into the singly linked list.
		if ((newNode = (struct measurement*)malloc(sizeof(struct measurement))) == NULL) {
			printf("Cannot allocate memory.\n");
			return;
		}

		// Assign the provided parameter values to the new node referenced by the newNode pointer.
		*newNode = (struct measurement){ temperature, { year, month, day, hour, minute, second} };

		// If the new nodes date/time is before the first nodes date/time,
		// the new node needs to go at the beginning (head) of the singly linked list.
		if (!isInChronologicalOrder(&head->moment, &newNode->moment)) {
			insertAtBeginning(year, month, day, hour, minute, second, temperature);
			return;
		}

		// Iterate through the singly linked list as long as the next element is "younger"
		// than the new node to insert into the list.
		while (nodeToInsertAfter->next != NULL && isInChronologicalOrder(&nodeToInsertAfter->next->moment, &newNode->moment)) {
			nodeToInsertAfter = nodeToInsertAfter->next;
		}

		// Insert before end of list
		newNode->next = nodeToInsertAfter->next;
		nodeToInsertAfter->next = newNode;
	}
}

/// <summary>
/// This function deletes the first element of the singly linked list.
/// If the list is empty, the (empty) singly linkes list remains unchanged.
/// </summary>
void deleteFirstElement() {

	// TODO: Implement this function!

	// This pointer will eventually hold a reference to the successor of the current head.
	// Eventually means: In case there's no head at all, we actually won't need this pointer.
	struct measurement* newHead;

	if (head != NULL) {
		// Temporary reference to successor of current head.
		newHead = head->next;

		// Free memory of current head
		free(head);

		// Set head of list to successof of previous head.
		head = newHead;
	}
}

/// <summary>
/// This function deletes the first node in the singly linked list which matches the given date and time.
/// If there are multiple nodes which match the given moment in the list, only the first occurenct will be deleted.
/// </summary>
/// <param name="moment"></param>
void deleteFirstOccurence(struct moment* moment) {

	// TODO: Implement this function!

	// Pointer which references the node right before the node to remove from the singly linked list.
	struct measurement* nodeBefore;

	// If there's no head, there's no list at all.
	if (head != NULL) {
		// Relay on the deleteFirstElement() function in case the head matches the given moment.
		if (areEqual(&head->moment, moment)) {
			deleteFirstElement();
		}
		else
		{
			// Once more, we need to iterate through the singly linked list.
			// We're looking for a node whose successors date/time (=moment) matches the moment parameters value.
			nodeBefore = head;
			while (nodeBefore->next != NULL && !areEqual(&nodeBefore->next->moment, moment)) {
				nodeBefore = nodeBefore->next;
			}

			// Iteration stopped. There are two reasons:
			// Either because of we reached the end of the list...
			if (nodeBefore->next == NULL) {
				return;
			}

			// ... or we found a node whose date/time matches the given moment parameters value.
			if (areEqual(&nodeBefore->next->moment, moment)) {
				// Temporarly store a reference to the node to remove from the singly linked list.
				struct measurement* nodeToDelete = nodeBefore->next;

				// Update the next-reference for the node just before the one to remove...
				nodeBefore->next = nodeToDelete->next;

				// ... and finally remove the nodeToDelete.
				free(nodeToDelete);
			}
		}
	}
}

/// <summary>
/// Deletes the last node within the singly linked list.
/// If the last node is also the first (and therefore only) node,
/// the list will be empty after a call to this function.
/// </summary>
void deleteLastNode() {
	// TODO: Implement this function...

	// Do nothing, if the list is empty.
	if (head == NULL) {
		return;
	}

	// If the head has no successor, it's the only node.
	if (head->next == NULL) {
		// Remove the singly linked lists only node...
		free(head);

		// ... and update the head accordingly.
		head = NULL;
		return;
	}

	// The list contains more than one node.
	// We now need to find the second last node.
	struct measurement* secondLastNode = head;

	while (secondLastNode->next->next != NULL) {
		secondLastNode = secondLastNode->next;
	}

	// Remove the successor of the second last node...
	free(secondLastNode->next);

	// ... and update the second last node accordingly.
	secondLastNode->next = NULL;
}

/// <summary>
/// Handles the input and output of the console to ask the user for a date and time (=moment).
/// The function returns a pointer to the newly created moment.
/// Remember to free() the moment if you don't need it anymore.
/// </summary>
struct moment* readMoment(void) {
	int year, month, day, hour, minute, second;

	// "Date [dd.mm.yyyy]",
	printf("%*.*s : ", -INPUT_PROMPT_LENGTH, INPUT_PROMPT_LENGTH, "Date [dd.mm.yyyy]");
	scanf_s("%2d.%2d.%4d", &day, &month, &year);
	// "Time [hh:mm:ss]"
	printf("%*.*s : ", -INPUT_PROMPT_LENGTH, INPUT_PROMPT_LENGTH, "Time [hh:mm:ss]");
	scanf_s("%2d:%2d:%2d", &hour, &minute, &second);

	struct moment* moment = (struct moment*)malloc(sizeof(struct moment));
	moment->year = year;
	moment->month = month;
	moment->day = day;
	moment->hour = hour;
	moment->minute = minute;
	moment->second = second;

	return moment;
}


struct measurement* readInput(void) {
	struct moment* moment;
	float temperature;

	moment = readMoment();

	printf("%*.*s : ", -INPUT_PROMPT_LENGTH, INPUT_PROMPT_LENGTH, "Temperature [\370C]");
	scanf_s("%f", &temperature);

	struct measurement* m = (struct measurement*)malloc(sizeof(struct measurement));
	m->moment = *moment;
	m->temperatureInCelcius = temperature;
	m->next = NULL;

	return m;
}

void printNode(struct measurement* node) {
	struct moment moment = node->moment;
	printf("%*s--------------\n", LEFT_PADDING, "");
	printf("%*s| %02d.%02d.%4d |\n", LEFT_PADDING, "", moment.day, moment.month, moment.year);
	printf("%*s|  %02d:%02d:%02d  |\n", LEFT_PADDING, "", moment.hour, moment.minute, moment.second);
	printf("%*s|------------|\n", LEFT_PADDING, "");
	printf("%*s|  %5.2f \370C  |\n", LEFT_PADDING, "", node->temperatureInCelcius);
	printf("%*s--------------\n", LEFT_PADDING, "");
}

void printArrow() {
	printf("%*s|\n", LEFT_PADDING + OUTPUT_LENGTH / 2, "|");
	printf("%*s|\n", LEFT_PADDING + OUTPUT_LENGTH / 2, "|");
	printf("%*s/\n", LEFT_PADDING + OUTPUT_LENGTH / 2, "\\");
}

void printList() {
	struct measurement* measurement = head;

	printf("\n\n");

	if (head == NULL) {
		printf("\tEMPTY LIST :-(");
		return;
	}

	while (measurement != NULL) {
		printNode(measurement);
		if (measurement->next != NULL) {
			printArrow();
		}
		measurement = measurement->next;
	}
}

int readMenuInput() {
	int menuInput;

	printf("\n\n");

	printf(" [1] Insert at beginning\n");
	printf(" [2] Insert chronologically\n");
	printf(" [3] Insert at end (append)\n");
	printf(" [4] Delete first node\n");
	printf(" [5] Delete node by value\n");
	printf(" [6] Delete last node\n");
	printf(" [7] Print list\n");
	printf(" [0] Exit\n");

	printf("\n> Enter digit from [1] to [7] for list operation or [0] for exit: ");

	scanf_s("%1d", &menuInput);
	return menuInput;
}


int main()
{

	struct measurement* measurement = NULL;
	struct moment* moment = NULL;
	int menuInput = readMenuInput();

	system("CLS");

	while (menuInput != 0) {

		switch (menuInput) {
		case 1:
			printf("INSERT AT BEGINNING\n\n");
			measurement = readInput();
			moment = &measurement->moment;
			insertAtBeginning((*moment).year, (*moment).month, (*moment).day, (*moment).hour, (*moment).minute, (*moment).second, measurement->temperatureInCelcius);
			free(measurement);
			break;
		case 2:
			printf("INSERT CHRONOLOGICALLY\n\n");
			measurement = readInput();
			moment = &measurement->moment;
			insertChronologically((*moment).year, (*moment).month, (*moment).day, (*moment).hour, (*moment).minute, (*moment).second, measurement->temperatureInCelcius);
			free(measurement);
			break;
		case 3:
			printf("APPEND AT THE END OF LIST\n\n");
			measurement = readInput();
			moment = &measurement->moment;
			insertAtEnd((*moment).year, (*moment).month, (*moment).day, (*moment).hour, (*moment).minute, (*moment).second, measurement->temperatureInCelcius);
			free(measurement);
			break;
		case 4:
			deleteFirstElement();
			break;
		case 5:
			moment = readMoment();
			deleteFirstOccurence(moment);
			free(moment);
			break;
		case 6:
			deleteLastNode();
			break;
		case 7:
			printList();
			break;
		default:
			printf("\n\nINVALID OPTION: %d", menuInput);
			break;
		}

		// Print list after a relevant operation.
		if (menuInput >= 1 && menuInput <= 6) {
			printList();
		}

		menuInput = readMenuInput();
		system("CLS");
	}

	return EXIT_SUCCESS;
}