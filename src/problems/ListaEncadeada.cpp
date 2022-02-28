#include <iostream>
#include <unordered_map>

class ListCell
{
public:
	ListCell* next;
	ListCell* previous;
	ListCell* arbitrary;

	ListCell(int k);
	void SetKey(int k);
	int GetKey();

private:

	int key;
};

ListCell::ListCell(int k)
{
	next = NULL;
	previous = NULL;
	SetKey(k);
}

void ListCell::SetKey(int k)
{
	key = k;
}

int ListCell::GetKey()
{
	return key;
}

void Print(ListCell *head)
{
	ListCell* current;
	current = head;
	while (current != NULL)
	{
		std::cout << current->GetKey() << ":";
		if (current->arbitrary != NULL)
			std::cout << current->arbitrary->GetKey() << " ";
		else
			std::cout << "NULL ";
		current = current->next;
	}
	std::cout << "\n";
}

ListCell* Remove(ListCell *head, int key)
{
	ListCell* current;
	current = head;
	while (current != NULL)
	{
		if (current->GetKey() == key)
		{
			ListCell* prev, *next;
			prev = current->previous;
			next = current->next;
			if (prev != NULL)
				prev->next = next;
			if (next != NULL)
				next->previous = prev;
			if (current == head)
				head = head->next;
			delete current;
			break;
		}
		current = current->next;
	}
	return head;
}

void Clear(ListCell* head)
{
	ListCell* current;
	while (head != NULL)
	{
		current = head;
		std::cout << current->GetKey() << " ";
		head = current->next;
		delete current;
	}
	std::cout << "\n";
}

ListCell* DeepCopy(ListCell *head)
{
	ListCell* copy(NULL), *current_h, *current_c, *previous_c;
	std::unordered_map<int, ListCell*> hash;
	std::unordered_map<int, ListCell*>::const_iterator found;
	current_h = head;
	if (current_h != NULL)
	{
		copy = new ListCell(current_h->GetKey());
		hash[copy->GetKey()] = copy;
		previous_c = copy;
		current_c = NULL;
		current_h = current_h->next;

		while (current_h != NULL)
		{
			current_c = new ListCell(current_h->GetKey());
			previous_c->next = current_c;
			hash[current_c->GetKey()] = current_c;
			
			previous_c = current_c;
			current_h = current_h->next;
		}

		current_c = copy;
		current_h = head;
		while (current_h != NULL)
		{
			if (current_h->arbitrary != NULL)
			{
				found = hash.find(current_h->arbitrary->GetKey());
				if (found != hash.end())
					current_c->arbitrary = found->second;
			}
			current_c = current_c->next;
			current_h = current_h->next;
		}
	}
	return copy;
}

int main_ListaEncadeada()
{
	// -1 15 1 15 10 -1
	int test[] = { 1, 10, 11, 13, 7, 15 }, x;
	ListCell* head(NULL), *new_cell;
	ListCell* copy(NULL);
	std::unordered_map<int, ListCell*> hash;
	std::unordered_map<int, ListCell*>::const_iterator found;
	
	for (auto& num : test)
	{
		new_cell = new ListCell(num);
		hash[num] = new_cell;

		if (head == NULL)
			head = new_cell;
		else
		{
			new_cell->next = head;
			head->previous = new_cell;
			head = new_cell;
		}
	}

	new_cell = head;
	while (new_cell != NULL)
	{
		std::cin >> x;
		found = hash.find(x);
		if (found != hash.end())
			new_cell->arbitrary = found->second;
		new_cell = new_cell->next;
	}
	copy = DeepCopy(head);
	Print(head);
	Print(copy);
	std::cout << "DeepCopied\n";

	for (int i = 0; i < 20; i++)
	{
		std::cout << "Remove " << i << ":\n";
		head = Remove(head, i);
		Print(head);
		Print(copy);
	}

	Clear(head);
	Clear(copy);
	return 0;
}
