#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>

using std::vector;
using std::pair;

class solution {
public:
  vector<pair<int,int>> reconstructQueue(const vector<pair<int,int>> & people) {
    std::map<int,vector<pair<int,int>>> dict;
    for (size_t i = 0; i < people.size(); ++i) {
      if (dict.find(people[i].second) == dict.end())
	dict[people[i].second] = vector<pair<int,int>>();
      dict[people[i].second].push_back(people[i]);
    }

    auto comp = [](const pair<int,int> & p1, const pair<int,int> & p2) {
      return p1.first < p2.first;
    };
    
    vector<pair<int,int>> start = dict[0];
    std::sort(start.begin(), start.end(), comp);
    dict.erase(0);

    vector<vector<pair<int,int>>> results;
    auto paths = getPath(dict, start);
    for (auto path : paths) {
      if (path.size() == people.size()) {
	results.push_back(path);
	std::for_each(path.begin(), path.end(), [](const pair<int,int> & pr){
	    std::cout << "[" << pr.first << "," << pr.second << "] ";
	  });
	std::cout << std::endl;
      }
    }

    return results[0];
  }

private:
  vector<vector<pair<int,int>>> getPath(std::map<int,vector<pair<int,int>>> & a_map, const vector<pair<int,int>> & curr) {
    vector<vector<pair<int,int>>> result;
    if (a_map.empty())
      result.push_back(curr);
    else {
      auto it = a_map.begin()->second.begin();
      if (a_map.begin()->second.size() == 1)
	a_map.erase(a_map.begin());
      else
	a_map.begin()->second.erase(it);
      
      for (size_t i = it->second; i < curr.size(); ++i) {
	int count = 0;
	size_t idx = 0;
	while (idx < i) {
	  if (curr[idx].first >= it->first)
	    count++;
	  idx++;
	}
	if (count == it->second) {
	  auto cpy = curr;
	  cpy.insert(cpy.begin()+i, *it);
	  auto temp = getPath(a_map, cpy);
	  for (auto tmp : temp)
	    result.push_back(tmp);
	}
      }
    }
    
    return result;
  }
};

int main() {
  vector<pair<int,int>> people;
  people.push_back(std::make_pair(7,0));
  people.push_back(std::make_pair(4,4));
  people.push_back(std::make_pair(7,1));
  people.push_back(std::make_pair(5,0));
  people.push_back(std::make_pair(6,1));
  people.push_back(std::make_pair(5,2));

  solution soln;
  auto qu = soln.reconstructQueue(people);
  
}
