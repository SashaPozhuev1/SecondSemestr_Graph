#include <iostream>
#include <sstream>
#include <vector>
#include <stack>

using std::vector;

template <typename T>
class graph
{
private:
	enum class color_t {
		WHITE,
		GREY,
		BLACK
	};
	vector<T> graph_;//вершины
	vector< vector<std::size_t> > contact_;//список смежности
	std::size_t elements_;
public:
	graph();
	graph(graph const &);
	graph(vector<T> const &, vector< vector<std::size_t> > const &);
	~graph();

	graph<T> & operator = (graph<T> const &);

	void insert(T, vector< vector<std::size_t> > const &);
	void dfs()const;
	void print_contact()const;
	
	std::size_t elements()const;
};

template <typename T>
graph<T>::graph() {
	elements_ = 0;
}

template <typename T>
graph<T>::graph(graph<T> const & other) {
	elements_ = other.elements_;
	graph_ = other.graph_;
	contact_ = other.contact_;
}

template <typename T>
graph<T>::graph(vector<T> const & graph, vector< vector<std::size_t> > const & contact) {
	elements_ = graph.size();
	graph_ = graph;
	contact_ = contact;
}


template <typename T>
graph<T>::~graph() {
	graph_.clear();
	contact_.clear();
	elements_ = 0;
}

template <typename T>
graph<T> & graph<T>::operator = (graph<T> const & other) {
	elements_ = other.elements_;
	graph_ = other.graph_;
	contact_ = other.contact_;
	return *this;
}

template <typename T>
std::size_t graph<T>::elements() const {
	return elements_;
}

//вставляем новую вершину и выбираем для неё связи
template <typename T>
void graph<T>::insert(T value, vector< vector<std::size_t> > const & contact) {
	if (contact.size() != elements_ + 1) {
		throw std::out_of_range("error idx");
	}

	for (std::size_t i = 0; i < contact.size(); ++i) {
		if (contact[i].size() > graph_.size() + 1) {
			throw std::out_of_range("big idx");		
		}
		for (std::size_t j = 0; j < contact[i].size(); ++j) {
			if (contact[i][j] > elements_) {
				throw std::out_of_range("big value");
			}
		}
	}

	graph_.push_back(value);
	elements_++;
	contact_ = contact;
//	contact.clear();
}

template <typename T>
void graph<T>::dfs() const {
	std::stack<std::size_t> my_stack;
	vector<color_t> color;

	for (std::size_t i = 0; i < graph_.size(); ++i) {
		color.push_back(color_t::WHITE);
	}

	for (std::size_t i = 0; i < graph_.size(); ++i) {
		my_stack.push(i);
		while (!my_stack.empty()) {
			std::size_t n = my_stack.top();
			my_stack.pop();
			if (color[n] == color_t::BLACK) {
				continue;
			}

			color[n] = color_t::BLACK;

			for (std::size_t i = contact_[n].size(); i > 0; --i) {
				if (color[i - 1] != color_t::BLACK) {
					my_stack.push(i - 1);
					color[i - 1] = color_t::GREY;
				}
			}
			std::cout << graph_[n] << ':' << n + 1 << std::endl;
		}
	}
}
	
//выводит - вершину:её номер:список связей
template <typename T>
void graph<T>::print_contact() const {
	for (std::size_t i = 0; i < elements_; ++i) {
		std::cout << graph_[i] << ':' << i + 1 << ':';

		if (contact_[i].size() < 1) {
			std::cout << '\n';
		}

		for (std::size_t j = 0; j < contact_[i].size(); ++j) {
			j == contact_[i].size() - 1 ? std::cout << contact_[i][j] + 1 << '\n':
						      std::cout << contact_[i][j] + 1 << ", ";
		}
	}
}
