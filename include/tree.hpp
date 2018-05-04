#include<iostream>

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

	node_t * grandparent(node_t const *);
	node_t * uncle(node_t const *);
	node_t * brother(node_t const *);
	node_t * search_adress(T, node_t *, node_t *&) const;

	void rotate_left(node_t *);
	void rotate_right(node_t *);

	void create_node(T, node_t *, node_t *&);
	void replace_node(node_t *, node_t *);
	void delete_child(node_t *);

	void insert_1(node_t *);
	void insert_2(node_t *);
	void insert_3(node_t *);
	void insert_4(node_t *);
	void insert_5(node_t *);

	void delete_1(node_t *);
	void delete_2(node_t *);
	void delete_3(node_t *);
	void delete_4(node_t *);
	void delete_5(node_t *);
	void delete_6(node_t *);

	bool compare(bool &, node_t *, node_t *) const;
	bool isLeaf(node_t *);
	void inorder(std::ostream &, const node_t *, std::size_t) const;
	void destroy(node_t * curr_);

public:
	tree_t() : root_(nullptr) {};
	~tree_t();
	tree_t(std::initializer_list<T> keys);

	auto operator==(tree_t const & other) const;
	node_t * root();

	void insert(T);
	void print(std::ostream &) const;
	void delete_node(T);
	bool find(T) const;
	bool isEmpty();
};

template <typename T>
tree_t<T>::tree_t(std::initializer_list<T> keys) {
	root_ = nullptr;
	for (auto key : keys) {
		insert(key);
	}
}

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
bool tree_t<T>::isLeaf(node_t *n_) {
	if (n_->right || n_->left) {
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
void tree_t<T>::create_node(T value, node_t *parent_, node_t *& curr_) {
	curr_ = new node_t;
	curr_->parent = parent_;
	curr_->left = nullptr;
	curr_->right = nullptr;
	curr_->value = value;
	curr_->color = 1;
}

template <typename T>
void tree_t<T>::insert(T value) {
	if (find(value)) {

	}
	else {
		if (!root_) {
			create_node(value, nullptr, root_);
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
						create_node(value, curr_, curr_->right);
						curr_ = curr_->right;
						insert_1(curr_);
						break;
					}
				}
				else if (value < curr_->value) {
					if (curr_->left) {
						curr_ = curr_->left;
					}
					else {
						create_node(value, curr_, curr_->left);
						curr_ = curr_->left;
						insert_1(curr_);
						break;
					}
				}
			}
		}
	}
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
void tree_t<T>::replace_node(node_t *n_, node_t *child_) {
	if (n_->parent) {
		if (n_ == n_->parent->left) {
			n_->parent->left = child_;
		}
		else {
			n_->parent->right = child_;
		}
	}
}

template <typename T>
void tree_t<T>::delete_node(T value) {
	node_t *n_ = root_;
	search_adress(value, root_, n_);

	if (n_ && n_->value == value) {
		if (n_->left && n_->right) {
			node_t *curr_ = n_->right;

			while (curr_->left) {
				curr_ = curr_->left;
			}

			n_->value = curr_->value;

			delete_child(curr_);
		}
		else {
			delete_child(n_);
		}
	}
}

template <typename T>
void tree_t<T>::delete_child(node_t *n_) {
	node_t *child_ = (n_->right) ? n_->right : n_->left;

	replace_node(n_, child_);
	if (n_ == root_) {
		root_ = child_;
	}

	if (n_->color == 0 && child_) {
		if (child_->color == 1) {
			child_->color = 0;
		}
		else {
			delete_1(child_);
		}
	}
	delete n_;
}

template <typename T>
void tree_t<T>::delete_1(node_t *n_) {
	if (n_->parent != nullptr) {
		delete_2(n_);
	}
}

template <typename T>
void tree_t<T>::delete_2(node_t *n_) {
	node_t *s_ = brother(n_);

	if (s_->color == 1) {
		n_->parent->color = 1;
		s_->color = 0;
		if (n_ == n_->parent->left) {
			if (n_->parent == root_) {
				root_ = n_->parent->right;
			}
			rotate_left(n_->parent);
		}
		else {
			if (n_->parent == root_) {
				root_ = n_->parent->left;
			}
			rotate_right(n_->parent);
		}
	}
	delete_3(n_);
}

template <typename T>
void tree_t<T>::delete_3(node_t *n_) {
	node_t *s_ = brother(n_);

	if ((n_->parent->color == 0) &&
		(s_->color == 0) &&
		(s_->left->color == 0) &&
		(s_->right->color == 0)) {
		s_->color = 1;
		delete_1(n_->parent);
	}
	else
		delete_4(n_);
}

template <typename T>
void tree_t<T>::delete_4(node_t *n_) {
	node_t *s_ = brother(n_);

	if ((n_->parent->color == 1) &&
		(s_->color == 0) &&
		(s_->left->color == 0) &&
		(s_->right->color == 0)) {
		s_->color = 1;
		n_->parent->color = 0;
	}
	else
		delete_5(n_);
}

template <typename T>
void tree_t<T>::delete_5(node_t *n_) {
	node_t *s_ = brother(n_);

	if (s_->color == 0) {
		if ((n_ == n_->parent->left) &&
			(s_->right->color == 0) &&
			(s_->left->color == 1)) {
			s_->color = 1;
			s_->left->color = 0;
			rotate_right(s_);
		}
		else if ((n_ == n_->parent->right) &&
			(s_->left->color == 0) &&
			(s_->right->color == 1)) {
			s_->color = 1;
			s_->right->color = 0;
			rotate_left(s_);
		}
	}
	delete_6(n_);
}

template <typename T>
void tree_t<T>::delete_6(node_t *n_) {
	node_t *s_ = brother(n_);

	s_->color = n_->parent->color;
	n_->parent->color = 0;

	if (n_ == n_->parent->left) {
		s_->right->color = 0;
		if (n_->parent == root_) {
			root_ = n_->parent->right;
		}
		rotate_left(n_->parent);
	}
	else {
		s_->left->color = 0;
		if (n_->parent == root_) {
			root_ = n_->parent->left;
		}
		rotate_right(n_->parent);
	}
}

template <typename T>
bool tree_t<T>::find(T value) const {
	node_t *n_ = root_;
	search_adress(value, root_, n_);
	if (n_ && n_->value == value) {
		return true;
	}
	return false;
}

template <typename T>
typename tree_t<T>::node_t * tree_t<T>::search_adress(T value, node_t * curr_, node_t *& n_) const {
	if (curr_) {
		if (curr_->value > value) {
			search_adress(value, curr_->left, n_);
		}
		else if (curr_->value < value) {
			search_adress(value, curr_->right, n_);
		}
		else if (curr_->value == value) {
			n_ = curr_;
			return n_;
		}
	}
	return root_;
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
			stream << ' ' << curr_->value << std::endl;
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
