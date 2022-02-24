#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <stdlib.h>
#include <string>
#include <utility>

#define ll long long int

using namespace std;

map<string, vector<pair<ll, int>>> global_skills_map;

class contributer
{
public:
	string name;
	int skills;
	ll free_after;
	map<string, int> skill_and_level;

	contributer(ll index)
	{
		free_after = 0;

		string contributer_name;
		cin >> contributer_name;
		name = contributer_name;

		int contributer_skills;
		cin >> contributer_skills;
		skills = contributer_skills;

		for (int i = 0; i < skills; ++i)
		{
			string skill_name;
			int skill_level;
			cin >> skill_name;
			cin >> skill_level;

			skill_and_level[skill_name] = skill_level;

			// add to global skills map
			if (global_skills_map.find(skill_name) != global_skills_map.end())
				global_skills_map[skill_name].push_back(make_pair(index, skill_level));
			else
			{
				vector<pair<ll, int>> v;
				v.push_back(make_pair(index, skill_level));
				global_skills_map[skill_name] = v;
			}
		}
	}
};

class project
{
public:
	string name;
	ll duration, score, best_before, no_of_requirements, points_per_day;
	vector<pair<string, int>> requirements;
	bool completed;

	project()
	{
		completed = false;
		string project_name;
		cin >> project_name;
		name = project_name;

		ll project_duration;
		cin >> project_duration;
		duration = project_duration;

		ll project_score;
		cin >> project_score;
		score = project_score;

		ll project_best_before;
		cin >> project_best_before;
		best_before = project_best_before;

		ll project_no_of_requirements;
		cin >> project_no_of_requirements;
		no_of_requirements = project_no_of_requirements;

		points_per_day = score / duration;

		for (int i = 0; i < project_no_of_requirements; ++i)
		{
			string skill_reqd;
			cin >> skill_reqd;
			int skill_level;
			cin >> skill_level;
			requirements.push_back(make_pair(skill_reqd, skill_level));
		}
	}
};

bool sort_by_skill(const pair<ll, int> &a, const pair<ll, int> &b)
{
	return a.second < b.second;
}

void sort_global_skills_map()
{
	for (auto it : global_skills_map)
		sort(it.second.begin(), it.second.end(), sort_by_skill);
}

bool sort_project(const project &a, const project &b)
{
	return a.points_per_day > b.points_per_day;
}

void initializeIO()
{
	freopen("input.txt", "r", stdin);
	freopen("outputs.txt", "w", stdout);
}

int main()
{
	initializeIO();

	ll c, p;
	cin >> c >> p;

	vector<contributer> contributers_array;
	for (ll i = 0; i < c; ++i)
	{
		contributer temp(i);
		contributers_array.push_back(temp);
	}

	vector<project> projects_array;
	for (ll i = 0; i < p; ++i)
	{
		project temp;
		projects_array.push_back(temp);
	}

	sort_global_skills_map();
	sort(projects_array.begin(), projects_array.end(), sort_project);

	// for (auto it : projects_array)
	// {
	// 	cout << it.name << "\n";
	// }

	map<string, vector<string>> output;
	ll currentDay = 0;

	for (auto it : projects_array)
	{
		for (auto req : it.requirements)
		{
			for (auto cont : global_skills_map[req.first])
			{
				bool flag = false;
				if (cont.second >= req.second)
				{
					if (contributers_array[cont.first].free_after >= currentDay)
						break;

					if (cont.second == req.second)
					{
						++cont.second;
						flag = true;
					}

					contributers_array[cont.first].free_after += it.duration
				}
			}
		}
	}

	return 0;
}