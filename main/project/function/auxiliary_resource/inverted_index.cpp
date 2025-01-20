#include<string>
#include<vector>
#include<map>
#include"global_resource/manager.h"
#include"index.h"
#include"inverted_index.h"
void InvertedIndex::MapThread::operator=(const std::string& stringWords){
	{std::vector<std::string> words;
		{std::string word;
			for(unsigned short l0 = 0; stringWords[l0]; ++l0){
				if(stringWords[l0] != ' '){word += stringWords[l0];}
				else{
					words.push_back(word);
					word = "";
				}
			}
			if(word.size()){words.push_back(word);}
		}
		const auto sizeWords = words.size();
		for(unsigned short l0 = 0; l0 < sizeWords; ++l0){
			const auto sizeFirst = first_words.size();
			unsigned char l1;
			for(l1 = 0; l1 < sizeFirst; ++l1){
				if(words[l0] == first_words[l1]){break;}
			}
			if(l1 == sizeFirst){
				first_words.push_back(words[l0]);
				index.push_back({});
			}
			index[l1].count+=1;
		}
	}
}
void InvertedIndex::operator=(std::vector<std::string>& files){
		const auto size = files.size();
		std::vector<MapThread> first;
		first.resize(size);
		manager(first, files, size);
		for(unsigned short l0 = 0; l0 < size; ++l0){
			const auto sizeFirst = first[l0].first_words.size();
			for(unsigned char l1 = 0; l1 < sizeFirst; ++l1){
				first[l0].index[l1].wordID = l0;
				GET[(first[l0].first_words[l1])].push_back(first[l0].index[l1]);
			}
		}
	}
const std::map<std::string, std::vector<Index>>& InvertedIndex::operator()(){return GET;}