#include "PmergeMe.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <utility>
#include <cstddef>
#include <cstdlib>
#include <cctype>
#include <climits>
#include <ctime>
#include <cerrno>


typedef std::pair<int, int>	Tagged;

static bool	taggedLess(const Tagged &a, const Tagged &b)
{
	return a.first < b.first;
}

static std::vector<std::size_t>	jacobsthalOrder(std::size_t m)
{
	std::vector<std::size_t>	order;

	if (m == 0)
	{
		return order;
	}

	std::vector<std::size_t>	ts;
	ts.push_back(1);
	ts.push_back(3);
	while (ts.back() < m)
	{
		std::size_t	next = ts[ts.size() - 1] + 2 * ts[ts.size() - 2];
		ts.push_back(next);
	}

	std::size_t	prev = 0;
	for (std::size_t i = 0; i < ts.size(); i++)
	{
		std::size_t	hi = ts[i];
		if (hi > m)
		{
			hi = m;
		}
		for (std::size_t p = hi; p > prev; p--)
		{
			order.push_back(p - 1);
		}
		prev = ts[i];
		if (ts[i] >= m)
		{
			break;
		}
	}
	return order;
}

static void	sortTaggedVector(std::vector<Tagged> &data)
{
	std::size_t	n = data.size();

	if (n < 2)
	{
		return;
	}

	bool	hasStraggler = (n % 2 == 1);
	Tagged	straggler(0, 0);
	if (hasStraggler)
	{
		straggler = data[n - 1];
	}

	std::vector<Tagged>	pairMain;
	std::vector<Tagged>	pairSmall;
	for (std::size_t i = 0; i + 1 < n; i += 2)
	{
		Tagged	a = data[i];
		Tagged	b = data[i + 1];
		if (b.first > a.first)
		{
			Tagged	tmp = a;
			a = b;
			b = tmp;
		}
		pairMain.push_back(a);
		pairSmall.push_back(b);
	}

	std::vector<Tagged>	mains(pairMain.size(), Tagged(0, 0));
	for (std::size_t i = 0; i < pairMain.size(); i++)
	{
		mains[i] = Tagged(pairMain[i].first, static_cast<int>(i));
	}
	sortTaggedVector(mains);

	std::vector<Tagged>	chain;
	chain.reserve(n);
	for (std::size_t i = 0; i < mains.size(); i++)
	{
		chain.push_back(pairMain[mains[i].second]);
	}

	std::size_t					pendCount = mains.size() + (hasStraggler ? 1 : 0);
	std::vector<std::size_t>	order = jacobsthalOrder(pendCount);
	for (std::size_t k = 0; k < order.size(); k++)
	{
		std::size_t						idx = order[k];
		Tagged							value(0, 0);
		std::vector<Tagged>::iterator	boundIt;

		if (idx < mains.size())
		{
			std::size_t	row = mains[idx].second;
			value = pairSmall[row];
			boundIt = std::find(chain.begin(), chain.end(), pairMain[row]);
		}
		else
		{
			value = straggler;
			boundIt = chain.end();
		}
		std::vector<Tagged>::iterator	pos = std::lower_bound(chain.begin(), boundIt, value, taggedLess);
		chain.insert(pos, value);
	}

	data.swap(chain);
}

static void	sortTaggedDeque(std::deque<Tagged> &data)
{
	std::size_t	n = data.size();

	if (n < 2)
	{
		return;
	}

	bool	hasStraggler = (n % 2 == 1);
	Tagged	straggler(0, 0);
	if (hasStraggler)
	{
		straggler = data[n - 1];
	}

	std::deque<Tagged>	pairMain;
	std::deque<Tagged>	pairSmall;
	for (std::size_t i = 0; i + 1 < n; i += 2)
	{
		Tagged	a = data[i];
		Tagged	b = data[i + 1];
		if (b.first > a.first)
		{
			Tagged	tmp = a;
			a = b;
			b = tmp;
		}
		pairMain.push_back(a);
		pairSmall.push_back(b);
	}

	std::deque<Tagged>	mains(pairMain.size(), Tagged(0, 0));
	for (std::size_t i = 0; i < pairMain.size(); i++)
	{
		mains[i] = Tagged(pairMain[i].first, static_cast<int>(i));
	}
	sortTaggedDeque(mains);

	std::deque<Tagged>	chain;
	for (std::size_t i = 0; i < mains.size(); i++)
	{
		chain.push_back(pairMain[mains[i].second]);
	}

	std::size_t					pendCount = mains.size() + (hasStraggler ? 1 : 0);
	std::vector<std::size_t>	order = jacobsthalOrder(pendCount);
	for (std::size_t k = 0; k < order.size(); k++)
	{
		std::size_t						idx = order[k];
		Tagged							value(0, 0);
		std::deque<Tagged>::iterator	boundIt;

		if (idx < mains.size())
		{
			std::size_t	row = mains[idx].second;
			value = pairSmall[row];
			boundIt = std::find(chain.begin(), chain.end(), pairMain[row]);
		}
		else
		{
			value = straggler;
			boundIt = chain.end();
		}
		std::deque<Tagged>::iterator	pos = std::lower_bound(chain.begin(), boundIt, value, taggedLess);
		chain.insert(pos, value);
	}

	data.swap(chain);
}

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &other) : _vec(other._vec), _deq(other._deq)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		this->_vec = other._vec;
		this->_deq = other._deq;
	}
	return *this;
}

PmergeMe::~PmergeMe()
{
}

bool PmergeMe::parseArgs(int argc, char **argv, std::vector<int> &values)
{
	if (argc < 2)
	{
		return false;
	}

	for (int i = 1; i < argc; i++)
	{
		std::string	token = argv[i];
		if (token.empty())
		{
			return false;
		}
		for (std::string::size_type j = 0; j < token.length(); j++)
		{
			if (!std::isdigit(static_cast<unsigned char>(token[j])))
			{
				return false;
			}
		}

		char	*end = NULL;
		errno = 0;
		long	value = std::strtol(token.c_str(), &end, 10);
		if (errno == ERANGE || *end != '\0' || value < 1 || value > INT_MAX)
		{
			return false;
		}
		values.push_back(static_cast<int>(value));
	}
	return true;
}

void PmergeMe::sortVector(std::vector<int> &data)
{
	std::vector<Tagged>	tagged(data.size(), Tagged(0, 0));

	for (std::size_t i = 0; i < data.size(); i++)
	{
		tagged[i] = Tagged(data[i], static_cast<int>(i));
	}
	sortTaggedVector(tagged);
	for (std::size_t i = 0; i < data.size(); i++)
	{
		data[i] = tagged[i].first;
	}
}

void PmergeMe::sortDeque(std::deque<int> &data)
{
	std::deque<Tagged>	tagged(data.size(), Tagged(0, 0));

	for (std::size_t i = 0; i < data.size(); i++)
	{
		tagged[i] = Tagged(data[i], static_cast<int>(i));
	}
	sortTaggedDeque(tagged);
	for (std::size_t i = 0; i < data.size(); i++)
	{
		data[i] = tagged[i].first;
	}
}

void PmergeMe::printSequence(const std::string &label, const std::vector<int> &values)
{
	std::cout << label;
	for (std::vector<int>::const_iterator it = values.begin(); it != values.end(); ++it)
	{
		std::cout << " " << *it;
	}
	std::cout << std::endl;
}

bool PmergeMe::execute(int argc, char **argv)
{
	std::vector<int>	values;

	if (!parseArgs(argc, argv, values))
	{
		std::cerr << "Error" << std::endl;
		return false;
	}

	printSequence("Before:", values);

	std::clock_t	startVec = std::clock();
	this->_vec.assign(values.begin(), values.end());
	sortVector(this->_vec);
	std::clock_t	endVec = std::clock();

	std::clock_t	startDeq = std::clock();
	this->_deq.assign(values.begin(), values.end());
	sortDeque(this->_deq);
	std::clock_t	endDeq = std::clock();

	if (startVec == static_cast<std::clock_t>(-1)
		|| endVec == static_cast<std::clock_t>(-1)
		|| startDeq == static_cast<std::clock_t>(-1)
		|| endDeq == static_cast<std::clock_t>(-1)
		|| endVec < startVec || endDeq < startDeq)
	{
		std::cerr << "Error: could not measure time." << std::endl;
		return false;
	}
	printSequence("After: ", this->_vec);

	double	timeVec = (static_cast<double>(endVec) - static_cast<double>(startVec)) / CLOCKS_PER_SEC * 1000000.0;
	double	timeDeq = (static_cast<double>(endDeq) - static_cast<double>(startDeq)) / CLOCKS_PER_SEC * 1000000.0;

	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << this->_vec.size()
		<< " elements with std::vector : " << timeVec << " us" << std::endl;
	std::cout << "Time to process a range of " << this->_deq.size()
		<< " elements with std::deque  : " << timeDeq << " us" << std::endl;
	return true;
}
