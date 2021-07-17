#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PHONE_NUMBER 1000
#define INITIAL_SIZE 2
#define INCREMENTAL_SIZE 2

typedef struct {
	char Name[24];
	float score;
} Student;


typedef struct {
	void * key;
	void * value;
} Entry;


typedef struct {
	Entry * entries;
	int size, total;
	Entry (*makeNode)(void*, void*);
	int (*compare)(void*, void*);
} SymbolTable;

/*-------------------------------------------------------------------------------------------*/

Entry make_student_node(void* Student_id, void* Student_info) {
	Entry res;
	
	res.key = malloc(sizeof(int));
	memcpy( res.key, Student_id, sizeof(int) );
	
	res.value = malloc(sizeof(Student));
	memcpy( res.value, Student_info, sizeof(Student) );
	
	return res;
}

/*-------------------------------------------------------------------------------------------*/

Entry makePhone(void* name, void* phone) {
	Entry res;
	res.key = strdup( (char*)name );
	res.value = malloc(sizeof(long));
	memcpy( res.value, phone, sizeof(long) );
	return res;
}

int comparePhone(void * key1, void* key2) {
	return strcmp((char*)key1, (char*)key2);
}

int compareNumber(void * key1, void* key2) {
	if (*(int*)key1 == *(int*)key2) return 0;
	else return 1;
}
/*-------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------*/
SymbolTable createSymbolTable(Entry (*makeNode)(void*, void*),int (*compare)(void*, void*)) {
	SymbolTable table;
	table.makeNode = makeNode;
	table.compare = compare;
	table.entries = (Entry*)malloc(INITIAL_SIZE * sizeof(Entry));
	table.total = 0;
	table.size = INITIAL_SIZE;
	return table;
}

/*-------------------------------------------------------------------------------------------*/
void dropSymbolTable(SymbolTable* tab){
	if (tab->entries != NULL) free(tab->entries);
	tab->makeNode = NULL;
	tab->compare = NULL;
}
/*-------------------------------------------------------------------------------------------*/

void addEntry(void* key, void* value, SymbolTable* book) {
	
	int pos = book->total;
	int found = 0;
	for (pos = 0;pos < book->total; pos++) {
		if (book->compare(key,book->entries[pos].key) == 0) { 
				found = 1;
				break;
			}
	}

	if (found == 0) {
		if (book->total == book->size) {
			book->size += INCREMENTAL_SIZE;
			book->entries = (Entry*)realloc(book->entries,book->size * sizeof(Entry));
		}
		book->entries[pos] = book->makeNode(key,value);
		book->total++;
	}
	else {
		book->entries[pos] = book->makeNode(key,value);
	}
	

}
/*-------------------------------------------------------------------------------------------*/

void PrintPhoneBook(SymbolTable book) {
	int i = 0;
	

	for (i = 0; i < book.total; i++) {
		printf("%-25s %ld\n",(char *)book.entries[i].key,*(long*)book.entries[i].value);
	}
}
/*-------------------------------------------------------------------------------------------*/

Entry* getEntry(void* key, SymbolTable book) {
	int i = 0;
	for (i = 0; i < book.total; i++)
	{
		if (book.compare(book.entries[i].key,key)==0) return &book.entries[i];
	}
	return NULL;
}
/*-------------------------------------------------------------------------------------------*/
void PrintStudentList(SymbolTable book) {
	int i = 0;
	

	for (i = 0; i < book.total; i++) {
		Student *data = (Student*)book.entries[i].value;
		char student_name[24];
		memcpy(student_name,data,24);
		float student_score = *(float*)((char*)data+24);
		printf("%-5d %-24s %g\n",*(int *)book.entries[i].key,student_name,student_score);
	}
}
/*-------------------------------------------------------------------------------------------*/

void Phone_Book_example() {
	SymbolTable phoneBook = createSymbolTable(makePhone, comparePhone);
	long number = 983984775;
	char name[] = "Ta Tuan Anh";
	addEntry(name, &number, &phoneBook);
	number = 123456;
	addEntry("Do Quoc Huy", &number, &phoneBook);
	number = 123456;
	addEntry("ai do", &number, &phoneBook);
	number = 67989;
	addEntry("Do Quoc Huy", &number, &phoneBook);

	PrintPhoneBook(phoneBook);
	Entry *result = getEntry("Do Huy",phoneBook);
	if (result) printf("%-25s %ld\n",(char*)result->key,*(long*)result->value);
	else printf("Khong tim thay\n");
	dropSymbolTable(&phoneBook);

}

void Student_List_Example() {
	// Tao student list
	SymbolTable Student_List = createSymbolTable(make_student_node,compareNumber);
	int new_student_id = 0;
	Student new_student_info;
	strcpy(new_student_info.Name,"Mai");
	new_student_info.score = 9.5;
	addEntry(&new_student_id,&new_student_info,&Student_List);
	strcpy(new_student_info.Name,"Mo");
	new_student_id = 1;
	new_student_info.score = 9;
	addEntry(&new_student_id,&new_student_info,&Student_List);
	strcpy(new_student_info.Name,"Man");
	new_student_id = 2;
	new_student_info.score = 8.5;
	addEntry(&new_student_id,&new_student_info,&Student_List);
	strcpy(new_student_info.Name,"Dao");
	new_student_id = 1;
	new_student_info.score = 9.5;
	addEntry(&new_student_id,&new_student_info,&Student_List);
	PrintStudentList(Student_List);
	dropSymbolTable(&Student_List);
}
int main() {
	Phone_Book_example();
	Student_List_Example();
	
	return 0;
}

