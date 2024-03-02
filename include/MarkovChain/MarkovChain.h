#pragma once

#include <vector>
#include <map>
#include <string>

class MarkovChain
 {
public:
	MarkovChain() = default;

	MarkovChain(const std::vector<std::string>& original_names, int order, int length);

	void resetGenerator(const std::vector<std::string>& original_names, int order, int length);

	std::string getName();
	std::vector<std::string> getNames(int count);

private:
	std::vector<std::string> v_generated;
	std::vector<std::string> v_samples;
	std::map<std::string, std::vector<char> > m_chains;
	typedef std::map<std::string, std::vector<char>>::iterator ChainsIter;

	int order{0};
	int min_name_length;

	void processName(const std::string& name);
	std::vector<std::string> & split(const std::string &s, char delim, std::vector<std::string> &elems);
	std::vector<std::string> split(const std::string &s, char delim);

	static const int MAX_NAME_ITERATION;
};
