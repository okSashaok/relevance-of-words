#include<string>
#include<vector>
#include<map>
#include"index.h"
#include"inverted_index.h"
#include"search_server.h"
void SearchServer::operator=(const std::string& list){
	InvertedIndex::MapThread first;
	first = list;
	std::map<unsigned short, std::vector<unsigned short>> sorting;
	const auto sizeFirst = first.first_words.size();
	unsigned char l0, l1;
	for(l0 = 0; l0 < sizeFirst; ++l0){
		sorting[first.index[l0].count].push_back(l0);
	}
	for(auto it = sorting.begin(); it != sorting.end(); ++it){
		l0 = it->second.size();
		for(l1 = 0; l1 < l0; ++l1){
			words.push_back(first.first_words[it->second[l1]]);
		}
	}
}
void SearchServer::operator()(std::map<std::string, std::vector<Index>>& index){
	std::vector<Index> relevance;

	const auto sizeWords = words.size();
	unsigned char l0
	, flag;

	for(l0 = 0, flag = 0; l0 < sizeWords; ++l0){
		if(index.find(words[l0]) != index.end()){++flag;}
	}
	if(flag < sizeWords){return;}
	unsigned short coincidences = 65'535;
	for(l0 = 0; l0 < sizeWords; ++l0){
		const auto sizeIndex = index[words[l0]].size();
		if(coincidences > sizeIndex){coincidences = sizeIndex;}
	}
	unsigned short i;
	for(i = 0; i < coincidences; ++i){
		Index relIndex;
		relIndex = index[words[0]][i];
		for(l0 = 0; l0 < sizeWords; ++l0){
			auto& word = words[l0];
			relIndex.count += index[word][i].count;
			
		}
		relevance.push_back(relIndex);
	}
	const auto sizeRelevance = relevance.size();
	unsigned short max = 0;
	for(i = 0; i < sizeRelevance; ++i){
		if(max < relevance[i].count){max = relevance[i].count;}
	}
	std::string cache, floatText;
	for(i = 0; i < sizeRelevance; ++i){
		cache = std::to_string((float)relevance[i].count / max);
		floatText = "";
		for(unsigned char x = 0; x < 5; ++x){floatText += cache[x];}
		GET[floatText].push_back(relevance[i].wordID);
	}
}
std::map<std::string, std::vector<unsigned short>> SearchServer::operator()(){return GET;}