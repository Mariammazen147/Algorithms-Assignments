// GROUP:   1
// ID:      20226131
// Assign:  01
// Assign:  ArrayHeap
// UVA:     10954
// Name:    Mariam Mazen Mohamed Anwer

#include <iostream>
using namespace std;

template <class Value>
struct Array
{
	int n, sz;
	Value *arr;

	void Initialize()
	{
		sz = 1;
		n = 0;
		arr = new Value[sz];
	}

	void Destroy()
	{
		delete[] arr;
	}

	void AddLast(Value v)
	{
		if (n == sz)
		{
			sz *= 2;
			Value *newArr = new Value[sz];
			for (int i = 0; i < n; i++)
			{
				newArr[i] = arr[i];
			}
			delete[] arr;
			arr = newArr;
		}
		arr[n] = v;
		n++;
	}

	void RemoveLast()
	{
		if (n > 0)
		{
			n--;
		}
	}

	Value &operator[](int i)
	{
		return arr[i];
	}
};

template <class Elem>
struct Heap
{
	Array<Elem> a;
	bool (*IsBefore)(Elem &, Elem &);

	void Initialize(bool (*_IsBefore)(Elem &, Elem &))
	{
		a.Initialize();
		IsBefore = _IsBefore;
	}

	void Destroy()
	{
		a.Destroy();
	}

	int Child(int i)
	{
		return 2 * i + 1;
	}

	int Parent(int i)
	{
		return (i - 1) / 2;
	}

	void MoveUp(int ind)
	{
		while (ind > 0 && IsBefore(a[ind], a[Parent(ind)]))
		{
			swap(a[ind], a[Parent(ind)]);
			ind = Parent(ind);
		}
	}

	void MoveDown(int ind)
	{
		int n = a.n;
		while (true)
		{
			int left = Child(ind);
			int right = left + 1;
			int smallest = ind;

			if (left < n && IsBefore(a[left], a[smallest]))
			{
				smallest = left;
			}
			if (right < n && IsBefore(a[right], a[smallest]))
			{
				smallest = right;
			}

			if (smallest == ind)
			{
				break;
			}

			swap(a[ind], a[smallest]);
			ind = smallest;
		}
	}

	void Add(Elem e)
	{
		a.AddLast(e);
		MoveUp(a.n - 1);
	}

	Elem GetFirst()
	{
		return a[0];
	}

	Elem RetrieveFirst()
	{
		Elem first = a[0];
		a[0] = a[a.n - 1];
		a.RemoveLast();
		MoveDown(0);
		return first;
	}
};

bool IsBeforeInt(int &a, int &b)
{
	return a < b;
}

int main()
{
	while (true)
	{
		int N;
		cout <<"Enter the number of elements (0 to stop): ";
		cin >> N;

		if (N == 0)
			break;

		Heap<int> h;
		h.Initialize(IsBeforeInt);

		cout <<"Enter the numbers: ";
		for (int i = 0; i < N; i++)
		{
			int num;
			cin >> num;
			h.Add(num);
		}

		int totalCost = 0;

		while (h.a.n > 1)
		{
			int first = h.RetrieveFirst();
			int second = h.RetrieveFirst();
			int cost = first + second;
			totalCost += cost;
			h.Add(cost);
		}

		cout << "Total Cost: " << totalCost << endl;
		h.Destroy();
	}

	return 0;
}
