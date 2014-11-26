template <class T>
class HashTable {
public:

	explicit HashTable(const T & notFound, int size = 101);
	HashTable(const HashTable & ht);
	const T& find(const T & x) const;
	void makeEmpty();
	void insert(const T & x);
	void remove(const T & x);
	const HashTable & operator=(const HashTable & ht);

	enum EntryType {
		ACTIVE, EMPTY, DELETED
	};

private:

	struct HashEntry {
		T element;
		EntryType info;

		HashEntry(const T &e = T(), EntryType i = EMPTY) :
				element(e), info(i) {
		}
	};

	vector<HashEntry> array;
	int currentSize;
	const T ITEM_NOT_FOUND;
	bool isActive(int currentPos) const;
	int findPos(const T & x) const;
	void rehash()
}

template<class T>
HashTable<T>::HashTable(const T& notFound, int size) :
		ITEM_NOT_FOUND(notFound), array(nextPrime(size)) {
}

template<class T>
HashTable<T>::HashTable(const HashTable &ht) :
		ITEM_NOT_FOUND(ht.ITEM_NOT_FOUND), array(ht.array), currentSize(
				ht.currentSize) {
}

template<class T>
void HashTable<T>::makeEmpty() {
	currentSize = 0;
	for (int i = 0; i < array.size(); i++) {
		array[i].info = EMPTY;
	}
}

template<class T>
const T& HashTable<T>::find(const T &x) const {
	int currentPos = findPos(x);
	if (isActive(currentPos)) {
		return array[currentPos].element;
	} else {
		return ITEM_NOT_FOUND;
	}
}

template<class T> int HashTable<T>::findPos(const T & x) const {
	int collisionNum = 0;
	int currentPos = hash(x, array.size());
	while (array[currentPos].info != EMPTY && array[currentPos].element != x) {
		currentPos += 2 * ++collisionNum
		– 1;
		if (currentPos >= array.size())
			currentPos -= array.size();
	}
	return currentPos;
}

template<class T> void HashTable<T>::insert(const T & x) {
	int currentPos = findPos(x);
	if (isActive(currentPos)) {
		return;
	}
	array[currentPos] = HashEntry(x, ACTIVE);
	if (++currentSize > array.size() / 2) {
		rehash();
	}
}

template<class T> void HashTable<T>::rehash() {
	vector < HashEntry > oldArray = array;
	array.resize(nextPrime(2 * oldArray.size()));
	for (int j = 0; j < array.size(); j++) {
		array[j].info = EMPTY;
	}
	currentSize = 0;
	for (int i = 0; i < oldArray.size(); i++) {
		if (oldArray[i].info == ACTIVE) {
			insert(oldArray[i].element);
		}
	}
}

template<class T>
void HashTable<T>::remove(const T & x) {
	int currentPos = findPos(x);
	if (isActive(currentPos)) {
		array[currentPos].info = DELETED;
	}
}

template<class T>
bool HashTable<T>::isActive(int currentPos) const {
	return (array[currentPos].info == ACTIVE);
}
