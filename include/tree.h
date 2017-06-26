#include <fstream>
#include <iostream>

template <class T> struct Node
{
	T key;
	Node<T>* Left;
	Node<T>* Right;
};
template <class T> class Tree
{
private:
	Node<T>*root;
	int count;
public:
	Tree();
	~Tree();
	void deleteTr(Node<T>* temp);
	void insert_node(const T&);
	int get_count()const;
	void print()const;
	Node<T>* find_node(const T& val, Node<T>* temp)const;
	Node<T>*root_()const;
	void display(Node<T>* temp, unsigned int level)const;
	void out()const;
	void reading(const std::string& filename);
	void output(std::ostream& ost, Node<T>* temp)const;
	void writing(const std::string& filename)const;
	bool deleteValue(Node<T>* parent, Node<T>* current, const T& val);
	bool deleteVal(const T& value);
};

template<class T>
Tree<T>::Tree()
{
	root = nullptr;
	count = 0;
}
template<class T>
Tree<T>::~Tree()
{
	deleteTr(root);
	count=0;
}
template<class T>			//удаляет узел и всех его детей
void Tree<T>::deleteTr(Node<T>* temp)
{
	if (!temp)
		return;
	if (temp->Left)
	{
		deleteTr(temp->Left);
		temp->Left = nullptr;
	}

	if (temp->Right)
	{
		deleteTr(temp->Right);
		temp->Right = nullptr;
	}
	delete temp;
}

template<class T>			//возвращает корень
Node<T>*Tree<T>::root_()const
{
	return root;
}
template<class T>			//возвращает количество узлов во всем дереве
int Tree<T>::get_count()const
{
	return count;
}


template<class T>			//вставляет узел (если значение меньше текущего, то двигаемся влево, если больше или равно - вправо
void Tree<T>::insert_node(const T&x)
{
	if (find_node(x, root) != nullptr) return;
	Node<T>* dn = new Node<T>;
	dn->key = x;
	dn->Left = dn->Right = 0;
	Node<T>* pn = root;
	Node<T>* temp = root;
	while (temp)
	{
		pn = temp;
		if (x < temp->key)
			temp = temp->Left;
		else
			temp = temp->Right;
	}
	if (!pn)
		root = dn;
	else
	{
		if (x < pn->key)
			pn->Left = dn;
		else
			pn->Right = dn;
	}
	count++;
}
template<class T>			//поиск узла по значению
Node<T>* Tree<T>::find_node(const T& val, Node<T>* temp) const
{
	if (temp == nullptr || val == temp->key)
		return temp;
	if (val > temp->key)
		return find_node(val, temp->Right);
	else
		return find_node(val, temp->Left);
}

template<typename T>			//чтение из файла
void Tree<T>::reading(const std::string& filename)
{
	
	std::ifstream fin(filename);
	try
	{
		if (!fin.is_open()) throw 123;
		int k;
		fin >> k;
		T temp;
		if (root != nullptr)
		{
			deleteTr(root);
			root = nullptr;
			count = 0;
		}
		for (int i = 0; i < k; ++i)
		{
			fin >> temp;
			insert_node(temp);
		}
		fin.close();
	}
	catch (int i)
	{
		std::cout << "The file isn't found" << std::endl;
	}
}
template<typename T>
void Tree<T>::print() const
{
	output(std::cout, this->root);
}
template<typename T>
void Tree<T>::output(std::ostream& ost, Node<T>* temp)const
{
	if (!temp) return;
	ost << temp->key << " ";
	output(ost, temp->Left);
	output(ost, temp->Right);
}

template<typename T>
void Tree<T>::writing(const std::string& filename)const
{
	std::ofstream fout(filename);
	try
	{
		if (!fout.is_open())
			throw 12;
		fout << count << " ";
		output(fout, root);
		fout.close();
	}
	catch (int i)
	{
		std::cout << "The file isn't found" << std::endl;
	}
}

template<typename T>
void Tree<T>::display(Node<T>* temp, unsigned int level)const
{

	if (temp)
	{
		display(temp->Left, level + 1);
		for (unsigned int i = 0; i < level; i++)
			std::cout << "-";
		std::cout << temp->key << std::endl;
		display(temp->Right, level + 1);
	}
}
template<typename T>
void Tree<T>::out()const
{
	display(root, 0);
}

template<class T>
bool Tree<T>::deleteValue(Node<T>* parent, Node<T>* current,const T& val)
{
	if (!current) return false;
	if (current->key == val)
	{
		if (current->Left == NULL || current->Right == NULL) {
			Node<T>* temp = current->Left;
			if (current->Right) temp = current->Right;
			if (parent) {
				if (parent->Left == current) {
					parent->Left = temp;
				}
				else {
					parent->Right = temp;
				}
			}
			else {
				this->root = temp;
			}
		}
		else {
			Node<T>* validSubs = current->Right;
			while (validSubs->Left) {
				validSubs = validSubs->Left;
			}
			T temp = current->key;
			current->key = validSubs->key;
			validSubs->key = temp;
			return deleteValue(current, current->Right, temp);
		}
		delete current;
		count--;
		return true;
	}
	if (current->key > val)
		return deleteValue(current, current->Left, val);
	else 
		return deleteValue(current, current->Right, val);
}
template<class T>
bool Tree<T>::deleteVal(const T& value)
{
	return this->deleteValue(NULL,root, value);
}
