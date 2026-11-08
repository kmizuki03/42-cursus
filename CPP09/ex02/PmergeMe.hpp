#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

class PmergeMe
{
	private:
		std::vector<int>	_vec;
		std::deque<int>		_deq;

		static bool	parseArgs(int argc, char **argv, std::vector<int> &values);
		static void	sortVector(std::vector<int> &data);
		static void	sortDeque(std::deque<int> &data);
		static void	printSequence(const std::string &label, const std::vector<int> &values);

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);
		~PmergeMe();

		bool	execute(int argc, char **argv);
};

#endif
