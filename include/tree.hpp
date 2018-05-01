#include <iostream>
template <typename T>
class tree_t
{
private:
	struct node_t {
		node_t * parent;
		node_t * left;
		node_t * right;
		T value;
		bool color;// 0-черный; 1-красный
	};
	node_t * root_;

	void rotate_left(node_t *);
	void rotate_right(node_t *);

	void insert_1(node_t *);
	void insert_2(node_t *);
	void insert_3(node_t *);
	void insert_4(node_t *);
	void insert_5(node_t *);

	bool search(T, node_t *, bool &) const;
	bool compare(bool &, node_t *, node_t *) const;
	void destroy(node_t * curr_);
	void inorder(std::ostream &, const node_t *, std::size_t) const;
	bool isLeaf(node_t *);
public:
	tree_t() : root_(nullptr) {};
	~tree_t();
	tree_t(std::initializer_list<T> keys);

	node_t * grandparent(node_t const *);
	node_t * uncle(node_t const *);
	node_t * brother(node_t const *);

	void insert(T);
	bool find(T) const;
	bool isEmpty();
	auto operator==(tree_t const & other) const;
	node_t * root();
	void print(std::ostream &) const;
};

template <typename T>
tree_t<T>::~tree_t() {
	destroy(root_);
}

template <typename T>
void tree_t<T>::destroy(node_t * curr_) {
	if (curr_) {
		destroy(curr_->right);
		destroy(curr_->left);
		delete curr_;
	}
}

template <typename T>
bool tree_t<T>::isEmpty() {
	if (root_) {
		return false;
	}
	return true;
}

template <typename T>
auto tree_t<T>::operator==(tree_t const & other) const {
	bool success = true;
	compare(success, root_, other.root_);
	return success;
}

template <typename T>
bool tree_t<T>::compare(bool & success, node_t * left, node_t * right) const {
	if (!left && !right) {

	}
	else if (left && right && left->value == right->value) {
		compare(success, left->left, right->left);
		compare(success, left->right, right->right);
	}
	else {
		success = false;
		return success;
	}
	return success;
}

template <typename T>
typename tree_t<T>::node_t * tree_t<T>::root() {
	return root_;
}

template <typename T>
typename tree_t<T>::node_t * tree_t<T>::grandparent(node_t const *n) {
	if (n && n->parent) {
		return n->parent->parent;
	}
	else {
		return nullptr;
	}
}

template <typename T>
typename tree_t<T>::node_t * tree_t<T>::uncle(node_t const *n) {
	node_t *g = grandparent(n);
	if (!g) {
		return nullptr;
	}
	if (n->parent == g->left) {
		return g->right;
	}
	else {
		return g->left;
	}
}

template <typename T>
typename tree_t<T>::node_t * tree_t<T>::brother(node_t const *n) {
	if (n == n->parent->left) {
		return n->parent->right;
	}
	else {
		return n->parent->left;
	}
}

template <typename T>
bool tree_t<T>::isLeaf(node_t *n) {
	if (n->right || n->left) {
		return false;
	}
	return true;
}

template <typename T>
void tree_t<T>::rotate_left(node_t *n) {
	node_t *pivot = n->right;

	pivot->parent = n->parent;
	if (n->parent) {
		if (n->parent->left == n) {
			n->parent->left = pivot;
		}
		else {
			n->parent->right = pivot;
		}
	}

	n->right = pivot->left;
	if (pivot->left) {
		pivot->left->parent = n;
	}
	n->parent = pivot;
	pivot->left = n;
}

template <typename T>
void tree_t<T>::rotate_right(node_t *n) {
	node_t *pivot = n->left;

	pivot->parent = n->parent;
	if (n->parent) {
		if (n->parent->left == n) {
			n->parent->left = pivot;
		}
		else {
			n->parent->right = pivot;
		}
	}

	n->left = pivot->right;
	if (pivot->right) {
		pivot->right->parent = n;
	}
	n->parent = pivot;
	pivot->right = n;
}

template <typename T>
void tree_t<T>::insert_1(node_t *n) {
	if (!n->parent) {
		n->color = 0;
	}
	else {
		insert_2(n);
	}
}

template <typename T>
void tree_t<T>::insert_2(node_t *n) {
	if (n->parent->color == 0) {
		return;
	}
	else {
		insert_3(n);
	}
}

template <typename T>
void tree_t<T>::insert_3(node_t *n) {
	node_t *u = uncle(n), *g;

	if (u && u->color == 1) {
		n->parent->color = 0;
		u->color = 0;
		g = grandparent(n);
		g->color = 1;
		insert_1(g);
	}
	else {
		insert_4(n);
	}
}

template <typename T>
void tree_t<T>::insert_4(node_t *n) {
	node_t *g = grandparent(n);

	if (n == n->parent->right && n->parent == g->left) {
		rotate_left(n->parent);
		n = n->left;
	}
	else if (n == n->parent->left && n->parent == g->right) {
		rotate_right(n->parent);
		n = n->right;
	}
	insert_5(n);
}

template <typename T>
void tree_t<T>::insert_5(node_t *n) {
	node_t *g = grandparent(n);

	n->parent->color = 0;
	g->color = 1;
	if (n == n->parent->left && n->parent == g->left) {
		if (g == root_) {
			root_ = n->parent;
		}
		rotate_right(g);
	}
	else {
		if (g == root_) {
			root_ = n->parent;
		}
		rotate_left(g);
	}
}

template <typename T>
tree_t<T>::tree_t(std::initializer_list<T> keys) {
	root_ = nullptr;
	for (size_t i = 0; i < keys.size(); i++) {
		T value = *(keys.begin() + i);
		insert(value);
	}
}

template <typename T>
void tree_t<T>::insert(T value) {
	bool success = false;
	if (search(value, root_, success)) {

	}
	else {
		if (!root_) {
			root_ = new node_t;
			root_->value = value;
			root_->parent = nullptr;
			root_->left = nullptr;
			root_->right = nullptr;
			insert_1(root_);
		}
		else {
			node_t * curr_ = root_;
			while (curr_) {
				if (value > curr_->value) {
					if (curr_->right) {
						curr_ = curr_->right;
					}
					else {
						curr_->right = new node_t;
						curr_->right->parent = curr_;
						curr_ = curr_->right;
						curr_->value = value;
						curr_->color = 1;
						curr_->left = nullptr;
						curr_->right = nullptr;
						insert_1(curr_);
						break;
					}
				}
				else if (value < curr_->value) {
					if (curr_->left) {
						curr_ = curr_->left;
					}
					else {
						curr_->left = new node_t;
						curr_->left->parent = curr_;
						curr_ = curr_->left;
						curr_->value = value;
						curr_->color = 1;
						curr_->left = nullptr;
						curr_->right = nullptr;
						insert_1(curr_);
						break;
					}
				}
			}
		}
	}
}

template <typename T>
bool tree_t<T>::find(T value) const {
	bool success = false;
	search(value, root_, success);
	return success;
}

template <typename T>
bool tree_t<T>::search(T value, node_t * curr_, bool & success) const {
	if (curr_) {
		if (curr_->value > value) {
			search(value, curr_->left, success);
		}
		else if (curr_->value < value) {
			search(value, curr_->right, success);
		}
		else if (curr_->value == value) {
			success = true;
			return success;
		}
	}
	else {
		return success;
	}
}


template <typename T>
void tree_t<T>::print(std::ostream & stream) const {
	std::size_t count = 1;
	inorder(stream, root_, count);
}

template <typename T>
void tree_t<T>::inorder(std::ostream & stream, const node_t * curr_, std::size_t count) const {
	if (curr_) {
		if (curr_->right) {
			count++;
			inorder(stream, curr_->right, count);
		}

		if (!curr_->right) {
			for (std::size_t i = 0; i < count; ++i) {
				if (i == count - 1) {
					stream << "----";
				}
				else {
					stream << "    ";
				}
			}
			stream << ' ' <<curr_->value << std::endl;
		}
		else {
			count--;
			for (std::size_t i = 0; i < count; ++i) {
				if (i == count - 1) {
					stream << "----";
				}
				else {
					stream << "    ";
				}
			}
			stream << ' ' << curr_->value << std::endl;
		}
		if (curr_->left) {
			count++;
			inorder(stream, curr_->left, count);
		}
		else {
			count--;
		}

	}
}
