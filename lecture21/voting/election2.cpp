#include "election2.h"

void election2(const std::vector<std::string>& votes, std::unordered_map<std::string, int>& results_out) {
	for (const auto& vote : votes)
		if (results_out.find(vote) == results_out.cend())
			results_out.insert(std::pair<std::string, int>(vote, 1));
		else
			++(results_out.at(vote));
}

void election_adapted2(const std::string& stream, std::unordered_map<std::string, int>& results_out) {
	std::vector <std::string> votes;

	std::size_t start_index = 0;
	while (stream[start_index] != ' ')
		++start_index;
	++start_index;
	std::size_t finish_index = start_index;

	for (std::size_t index = start_index; index < stream.size(); ++index) {
		if (stream[index] == ' ') {
			votes.push_back(std::string(stream, start_index, finish_index - start_index));
			start_index = finish_index + 1;
		}
		++finish_index;
	}
	votes.push_back(std::string(stream, start_index, finish_index - start_index));

	election2(votes, results_out);
}
