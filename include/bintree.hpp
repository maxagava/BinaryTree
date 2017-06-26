#include <fstream>
#include <iostream>
using namespace std;

template <class T> struct Node
{
	T key;
	Node<T>* left;
	Node<T>* right;
};
template <class T> class tree
{
private:
	Node<T>*root;
	int count;
public:
	tree();
	~tree();
	void delNode(Node<T>* temp);
	void ins_node(const T&);
	int get_count()const;
	void print()const;
	Node<T>* find_node(const T& val, Node<T>* temp)const;
	Node<T>*root_()const;
	void output()const;
	void read(const std::string& filename);
	void out(std::ostream& ost, Node<T>* temp)const;
	void disp(Node<T>* temp, unsigned int level)const;
	void writing(const std::string& filename)const;
	bool del(Node<T>* pr, Node<T>* cur, const T& val);
	bool delv(const T& value);
};

template<class T>
tree<T>::tree()
{
	root = nullptr;
	count = 0;
}
template<class T>
tree<T>::~tree()
{
	delNode(root);
}
template<class T>
void tree<T>::delNode(Node<T>* temp)
{
	if (!temp)
		return;
	if (temp->left)
	{
		delNode(temp->left);
		temp->left = nullptr;
	}

	if (temp->right)
	{
		delNode(temp->right);
		temp->right = nullptr;
	}
	delete temp;
}

template<class T>
Node<T>*tree<T>::root_()const
{
	return root;
}
template<class T>
int tree<T>::get_count()const
{
	return count;
}


template<class T>
void tree<T>::ins_node(const T&x)
{
	Node<T>* duz = new Node<T>;
	duz->key = x;
	duz->left = duz->right = 0;
	Node<T>* puz = root;
	Node<T>* temp = root;
	while (temp)
	{
		puz = temp;
		if (x < temp->key)
			temp = temp->left;
		else
			temp = temp->right;
	}
	if (!puz)
		root = duz;
	else
	{
		if (x < puz->key)
			puz->left = duz;
		else
			puz->right = duz;
	}
	count++;

}
template<class T>
Node<T>* tree<T>::find_node(const T& val, Node<T>* temp) const
{
	if (temp == 0 || val == temp->key)
		return temp;
	if (val > temp->key)
		return find_node(val, temp->right);
	else
		return find_node(val, temp->left);
}

template<typename T>
void tree<T>::read(const std::string& filename)
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
			delNode(root);
			root = nullptr;
			count = 0;
		}
	for (int i = 0; i < k; ++i)
		{
		fin >> temp;
		ins_node(temp);
		}
	fin.close();
	}
	catch (int i)
	{
		std::cout << "File not found!" << std::endl;
	}
}
template<typename T>
void tree<T>::print() const
{
	out(cout, this->root);
}
template<typename T>
void tree<T>::out(ostream& ost, Node<T>* temp)const
{
	if (!temp) return;
	ost << temp->key << " ";
	out(ost, temp->left);
	out(ost, temp->right);
}
template<class T>
void tree<T>::disp(Node<T>* temp, unsigned int lvl)const
{

	if (temp)
	{
		disp(temp->left, lvl + 1);
		for (unsigned int i = 0; i < lvl; i++)
			std::cout << "-";
		std::cout << temp->key << std::endl;
		disp(temp->right, lvl + 1);
	}
}

template<typename T>
void tree<T>::writing(const std::string& filename)const
{
	ofstream fout(filename);
	fout << count << " ";
	out(fout, root);
	fout.close();
}
template<typename T>
void tree<T>::output()const
{
	disp(root, 0);
}
template<class T>
bool tree<T>::del(Node<T>* pr, Node<T>* cur,const T& val)
{
	if (!cur) return false;
	if (cur->key == val)
	{
		if (cur->Left == NULL || cur->right == NULL) {
			Node<T>* temp = cur-left;
			if (cur->right) temp = cur->right;
			if (pr) {
				if (pr->left == cur) {
					pr->left = temp;
				}
				else {
					pr->right = temp;
				}
			}
			else {
				this->root = temp;
			}
		}
		else 
		{
			Node<T>* vals = cur->left;
			while (vals->right) 
			{
				vals = vals->right;
			}
			vals->right=cur->right->left;
			cur->right->left=cur->left;
			if (pr->left==cur)
				pr->left=cur->right;
			if (pr->right==cur)
				pr->right=cur->right;
			
		}
		delete cur;
		count--;
		return true;
	}
	if (cur->key > val)
		return del(cur, cur->left, val);
	else 
		return del(cur, cur->right, val);
}
template<class T>
bool tree<T>::delv(const T& value)
{
	return this->del(NULL,root, value);
}
