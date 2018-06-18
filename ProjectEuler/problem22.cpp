#include "config.h"

#if SHOWN_PROBLEM <= 22

#include <assert.h>
#include <stdio.h>
#include <fmt/format.h>

#include <vector>

#include "numbers.h"
#include "bigi.h"

// Very exercise specific, 
u64 sz_str_capital_letters_sum(const char* sz)
{
	u64 sum = 0;

	while (*sz)
	{
		sum += *sz - 'A' + 1;

		++sz;
	}

	return sum;
}

auto problem22_result() {

	FILE* names_file = nullptr;	
	errno_t err = fopen_s(&names_file, "resources/p022_names.txt", "r");
	assert(err == 0);

	char buffer[65536]; // File size is 46447 bytes
	size_t read_count = fread_s(buffer, 65536, 1, 65536, names_file);
	buffer[read_count] = '\0';

	char* strtok_context = nullptr;
	char* pch = strtok_s(buffer, ",\"", &strtok_context); // Get first token

	std::vector<const char*> tokens;
	tokens.reserve(6000); // ~ 5100 names

	while (pch != nullptr)
	{
		//printf("%s\n", pch);

		tokens.push_back(pch);

		pch = strtok_s(nullptr, ",\"", &strtok_context); // Get following tokens
	}

	std::sort(tokens.begin(), tokens.end(), [](const char* left, const char* right) {
		return strcmp(left, right) == -1; // Lexicographical sort
	});

	mpz_class bigi;


	u64 total_score = 0;

	const size_t tokens_count = tokens.size();
	for (size_t i = 0; i < tokens_count; ++i)
	{
		u64 token_letters_worth = sz_str_capital_letters_sum(tokens[i]);
		u64 token_score = (i + 1) * token_letters_worth;

		total_score += token_score;
	}

	fmt::print("read_count: {}\n", read_count);
	fmt::print("tokens.size: {}\n", tokens.size());

	fmt::print("bob: {}\n", sz_str_capital_letters_sum("COLIN"));

	fmt::print("Total score: {}\n", total_score);

	return total_score;
}

void problem22() {
	fmt::print("DO NOT CLOSE THIS CONSOLE WINDOW ACCIDENTALLY!\n\n");
	fmt::print("Solving problem 22...\n\n");

	auto res = problem22_result();

	fmt::print("The result is:\n{}\n\n", res);
}

#endif
