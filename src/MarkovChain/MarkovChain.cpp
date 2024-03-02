#include "MarkovChain/MarkovChain.h"
#include <cassert>
#include <ctime>
#include <sstream>
#include <algorithm>

const int MarkovChain::MAX_NAME_ITERATION = 100;

MarkovChain::MarkovChain(const std::vector<std::string>& original_names, int order, int length)
 {
	assert(order > 0);
	assert(original_names.size() > 0);	
	this->order = order;
	this->min_name_length = length;

	for(std::string s : original_names)
	{
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		processName(s);
	}
}
void MarkovChain::resetGenerator(const std::vector<std::string>& original_names, int order, int length) 
{
	assert(order > 0);
	assert(original_names.size() > 0);

	this->order = order;
	this->min_name_length = length;

	for(const std::string& name : original_names)
		processName(name);
}

std::string MarkovChain::getName()
 {
	assert(m_chains.size() > 0);
	std::string name;
	do{
		int n = rand() % v_samples.size();
		int name_length = v_samples[n].size();

		int substring_start = v_samples[n].length() == order ? 0 : rand() % (v_samples[n].length() - order);
		
		name = v_samples[n].substr(0, order);
		if(name[0] == ' ')
			continue;

		ChainsIter it = m_chains.find(name);
		char next_char;
		int iterations = 0;

		while (name.length() < name_length) {
			iterations++;
			next_char = it->second[rand() % it->second.size()];

			if(next_char != '\n'){
				name.append(1, next_char);

				std::string segment = name.substr(name.length() - order);
				it = m_chains.find(segment);
			}else{
				break;
			}
		}
	}while(find(v_generated.begin(), v_generated.end(), name) != v_generated.end() || name.length() < min_name_length);
	v_generated.push_back(name);

	transform(name.begin(), name.begin() + 1, name.begin(), ::toupper);

	return name;
}

std::vector<std::string> MarkovChain::getNames(int count)
{
	std::vector<std::string> names;
	while(count-- >0)
	{
		names.emplace_back(getName());
	}
	return names;
}

void MarkovChain::processName(const std::string& name)
{
	if(name.length() < order)
		return;

	for(int i = 0; i <= name.length() - order; i++)
	{
		std::string segment = name.substr(i, order);
		char next_char = i == name.length() - order ? '\n' : name[i+order];

		ChainsIter it = m_chains.find(segment);
		if(it != m_chains.end())
		{
			it->second.push_back(next_char);
		}else
		{
			std::vector<char> v(1, next_char);
			m_chains[segment] = v;
		}
	}
	v_generated.push_back(name);
	v_samples.push_back(name);
}

std::vector<std::string> & MarkovChain::split(const std::string &s, char delim, std::vector<std::string> &elems)
 {
	std::stringstream ss(s);
	std::string item;
	
	while(std::getline(ss, item, delim))
		elems.push_back(item);
		
	return elems;
}

std::vector<std::string> MarkovChain::split(const std::string &s, char delim)
 {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}