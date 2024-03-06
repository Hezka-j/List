#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class SinglyLinkedList
{
public:
	struct Node
	{
		int data = 0;
		Node* next = nullptr;
	};

private:
	Node* head = nullptr;
	Node* tail = nullptr;
	int count = 0;

public:
	void AddToHead(int data)
	{
		auto newElem = new Node;
		newElem->data = data;
		newElem->next = head;

		if (head == nullptr)
		{
			tail = newElem;
		}
		head = newElem;
		count++;
	}

	void AddToTail(int data)
	{
		auto newElem = new Node;
		newElem->data = data;
		if (tail == nullptr)
		{
			head = newElem;
		}
		else
		{
			tail->next = newElem;
		}
		tail = newElem;
		count++;
	}

	void InsertInto(int data, int position)
	{
		if (position >= count)
		{
			AddToTail(data);
			return;
		}
		else if (position <= 0)
		{
			AddToHead(data);
			return;
		}

		Node* newElem = new Node;
		newElem->data = data;
		int i = 1;
		Node* beforeNew = head;
		while (i++ != position)
		{
			beforeNew = beforeNew->next;
		}
		newElem->next = beforeNew->next;
		beforeNew->next = newElem;

		count++;
	}

	void DeleteFromHead()
	{
		if (count == 0)
		{
			return;
		}
		Node* temp = head;
		head = head->next;
		delete temp;
		count--;
		if (head == nullptr)
		{
			tail = nullptr;
		}
	}

	void DeleteFromTail()
	{
		if (count == 0) {
			return;
		}
		DeleteByIndex(count - 1);
	}

	void DeleteByIndex(int position)
	{
		if (position <= 0)
		{
			DeleteFromHead();
			return;
		}

		if (position >= count)
		{
			position = count - 1;
		}

		int i = 1;
		Node* beforeDel = head;
		while (i++ != position)
		{
			beforeDel = beforeDel->next;
		}
		Node* sacrifice = beforeDel->next;
		beforeDel->next = sacrifice->next;
		delete sacrifice;
		count--;
		if (beforeDel->next == nullptr)
		{
			tail = beforeDel;
		}
	}

	void Clear()
	{
		while (head != nullptr)
		{
			DeleteFromHead();
		}
	}

	void Print() const
	{
		if (count == 0)
		{
			cout << "Empty list!\n";
			return;
		}
		Node* current = head;
		while (current != nullptr)
		{
			cout << current->data << " ";
			current = current->next;
		}
		cout << "\n";
	}

	int GetCount() const
	{
		return count;
	}

	int IndexOf(int data) const
	{
		if (count == 0)
		{
			return -1;
		}
		Node* current = head;
		int i = 0;
		while (i < count)
		{
			if (data == current->data)
			{
				return i;
			}
			i++;
			current = current->next;
		}
		return -1;
	}

	~SinglyLinkedList() {
		Clear();
	}

	SinglyLinkedList() {} // просто шоб было :) для создания первого объекта списка-оригинала

	SinglyLinkedList(const SinglyLinkedList& original)
	{
		// делаю указатель на начало списка-оригинала
		Node* current = original.head;
		while (current != nullptr) // пока не дойдём до конца оригинального списка
		{
			this->AddToTail(current->data);
			current = current->next;
		}
	}

	SinglyLinkedList& operator = (const SinglyLinkedList& original)
	{
		// проверка на самоприсваивание
		if (this == &original) return *this;

		this->Clear(); // во избежание утечек памяти необходимо скинуть предыдущее состояние копии

		Node* current = original.head;
		while (current != nullptr) // пока не дойдём до конца оригинального списка
		{
			this->AddToTail(current->data);
			current = current->next;
		}
		return *this;
	}
	void Reverse()
	{
		if (count == 0 || count == 1) return;
		vector<int> ar;
		Node* current = head;
		for (int i = 0; i < count; i++)
		{
			ar.push_back(current->data);
			current = current->next;
		}
		reverse(ar.begin(),ar.end());
		current = head;
		for (int i = 0; i < count; i++)
		{
			current->data = ar[i];
			current = current->next;
		}
	}

	void SortDesc()
	{
		SortAsc();
		Reverse();
	}

	bool IsEmpty()
	{
		if (count == 0)
			return true;
		else
			return false;
	}

	vector<int>/*int**/ ToArray()
	{
		Node* current = head;
		/*int* ar = new int[count];*/
		vector<int> ar;
		for (int i = 0; i < count; i++)
		{
			ar.push_back(current->data);
			current = current->next;
		}
		return ar;
	}

	int LastIndexOf(int number)
	{
		vector<int> ar = ToArray();
		for (int i = count - 1; i >= 0; i--)
		{
			if (ar[i] == number) return i;			
		}
		return -1;
	}

	void Shuffle()
	{
		if (count == 0 || count == 1) return;
		vector<int> ar = ToArray();
		Node* current = head;
		/*random_shuffle(ar[0], ar[count - 1]);*/
		random_shuffle(ar.begin(), ar.end());
		//cout << "\nShuffle: ";
		for (int i = 0; i < count; i++)
		{
			current->data = ar[i];
			//cout << ar[i] << " ";
			current = current->next;
		}
		cout << "\n";
	}

	SinglyLinkedList Clone()
	{
		SinglyLinkedList sll;
		Node* current = head;
		for (int i = 0; i < count; i++)
		{
			sll.AddToTail(current->data);
			current = current->next;
		}
		return sll;
	}
	// ascendence
	void SortAsc() {
		if (count == 0 || count == 1) return;

		/* // перегонка списка в массив
		int* ar = new int[count];
		Node* current = head; // получаю указатель на начало списка
		for (int i = 0; i < count; i++)
		{
			ar[i] = current->data;
			current = current->next;
		}
		sort(ar, ar + count);

		current = head; // получаю указатель на начало списка
		for (int i = 0; i < count; i++)
		{
			current->data = ar[i];
			current = current->next;
		}
		delete[] ar; */ // было 15 строк кода

		// то же самое, но на векторе
		vector<int> ar;
		Node* current = head; // получаю указатель на начало списка
		for (int i = 0; i < count; i++) {
			ar.push_back(current->data);
			current = current->next;
		}
		sort(ar.begin(), ar.end());

		current = head; // получаю указатель на начало списка
		for (int i = 0; i < count; i++) {
			current->data = ar[i];
			current = current->next;
		}
	}

	void SetAt(int index, int number)
	{
		Node* current = head;
		if (index >= count)
		{
			tail->data = number;
		}
		else if (index < 0)
		{
			head->data = number;
		}
		for (int i = 0; i < count; i++)
		{
			if (i == index)
			{
				current->data = number;
				return;
			}
			current = current->next;

		}
	}

	void MergeWith(SinglyLinkedList& second)
	{
		if (second.count == 0) return;
		Node* second_current = second.head;
		while(second_current != nullptr)
		{
			this->AddToTail(second_current->data);
			second_current = second_current->next;
		}
		
	}

	
	// если в составе класса есть поле-указатель (а даже если и нету, но) 
	// присутствует работа с динамической памятью (частые делиты и нью), то
	// в классе должна быть золотая тройка методов (т.н. golden triangle)
	// 1) деструктор
	// 2) КК конструктор копирования
	// 3) перегрузка операции =
};
bool operator == (SinglyLinkedList& left,SinglyLinkedList& right)
{
	if (left.GetCount() == right.GetCount())
		return true;
	else
		return false;
}

bool operator != (SinglyLinkedList& left,SinglyLinkedList& right)
{
	if (left.GetCount() != right.GetCount())
		return true;
	else
		return false;
}
ostream& operator << (ostream& o, SinglyLinkedList& list)
{
	list.Print();
	return cout;
}

//bool operator != (SinglyLinkedList& left, SinglyLinkedList& right)
//{
//	if (left.GetCount() != right.GetCount())
//		return true;
//	else
//		return false;
//}
int main()
{
	SinglyLinkedList sll;
	/*int* a = sll.ToArray();*/
	vector<int> a = sll.ToArray();
	for (int i = 0; i < 5; i++)
	{
		sll.AddToTail(rand() % 100); // 0...99
	}
	/*cout << sll.LastIndexOf(67);*/
	//cout << *a;
	sll.Print();
	cout << "\n\n\n============================\n\n\n";
	//sll.SortAsc();
	/*
	sll.SortDesc();*/
	SinglyLinkedList ll = sll.Clone();	
	ll.Print();
	//sll.SetAt(0, 2);
	//sll.SetAt(-1, 2);
	//sll.SetAt(10, 2);
	cout << "\n\n\n============================\n\n\n";
	//sll.Shuffle();
	//sll.MergeWith(ll);
	SinglyLinkedList list;
	list.AddToTail(5);
	list.AddToTail(5);
	list.AddToTail(5);
	list.MergeWith(sll);
	cout << (sll == ll) << "\n";
	cout << (sll != list) << "\n";
	/*list.Print();*/
	sll.Print();
	cout << "End";
}