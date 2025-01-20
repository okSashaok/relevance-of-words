#pragma once
class InvertedIndex{
	private:
	std::map<std::string, std::vector<Index>> GET;
	public:
	struct MapThread{
		std::vector<std::string> first_words;
		std::vector<Index> index;
		void operator=(const std::string& oper);
	};
	void operator=(std::vector<std::string>& files);
	const std::map<std::string, std::vector<Index>>& operator()();
};