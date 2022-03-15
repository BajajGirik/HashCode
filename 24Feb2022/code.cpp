#include <bits/stdc++.h>
#define ll long long int

using namespace std;

map<string, vector<pair<ll, int>>> global_skills_map;
map<string, vector<string>> output_map;
ll current_day = 0;

// classes
class contributer
{
public:
	string name;
	int skills;
	ll free_after;
	bool already_included_for_project;
	map<string, int> skill_and_level;

	contributer(ll index)
	{
		free_after = -1;
		already_included_for_project = false;
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

	ll project_score()
	{
		ll completion_date = current_day + duration;

		if (completion_date <= best_before)
			return score;

		if (score > completion_date - best_before)
			return score - (completion_date - best_before);

		return 0;
	}
};

struct contributers_available
{
	vector<ll> index_of_contributors;
	vector<pair<string, int>> improve_skill;
	ll completion_date;
	bool available;
};

vector<contributer> contributers_array;
vector<project> projects_array;

bool sort_by_skill(const pair<ll, int> &a, const pair<ll, int> &b)
{
	return a.second < b.second;
}

void sort_global_skills_map()
{
	for (auto &it : global_skills_map)
		sort(it.second.begin(), it.second.end(), sort_by_skill);
}

bool sort_project(const project &a, const project &b)
{
	return a.points_per_day > b.points_per_day;
}

void initializeIO()
{
	freopen("input_data/f.txt", "r", stdin);
	freopen("outputs/f.txt", "w", stdout);
}

void print_global_skills_map()
{
	for (auto i : global_skills_map)
	{
		cout << i.first << "\n";
		for (auto j : i.second)
		{
			cout << contributers_array[j.first].name << " ";
			cout << j.second << endl;
		}
		cout << "----------------------------\n";
	}
}

void set_already_included_for_project(bool val) {
	for(auto &c : contributers_array) {
		c.already_included_for_project = val;
	}
}

contributers_available check_if_contributer_available(project proj)
{
	contributers_available obj;
	set_already_included_for_project(false);

	for (auto req : proj.requirements)
	{
		bool flag = false;
		for (auto contri : global_skills_map[req.first])
		{
			if (!contributers_array[contri.first].already_included_for_project && contri.second >= req.second && contributers_array[contri.first].free_after < current_day)
			{
				obj.index_of_contributors.push_back(contri.first);
				if (contri.second == req.second)
					obj.improve_skill.push_back(make_pair(req.first, 1));
				else
					obj.improve_skill.push_back(make_pair(req.first, 0));
				contributers_array[contri.first].already_included_for_project = true;
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			obj.available = false;
			return obj;
		}
	}

	obj.available = true;
	obj.completion_date = current_day + proj.duration;
	return obj;
}

void update_free_time_and_skills_of_contributers(contributers_available a)
{
	ll j = 0;
	for (ll i : a.index_of_contributors)
	{
		contributers_array[i].free_after = a.completion_date;
		contributers_array[i].skill_and_level[a.improve_skill[j].first] += a.improve_skill[j].second;
		++j;
	}
}

bool select_project(project &proj)
{
	if(proj.completed || proj.project_score() == 0)
		return false;

	contributers_available contri_avai = check_if_contributer_available(proj);

	if (contri_avai.available)
	{
		vector<string> names_of_contris;
		update_free_time_and_skills_of_contributers(contri_avai);
		for (ll k : contri_avai.index_of_contributors)
			names_of_contris.push_back(contributers_array[k].name);

		output_map.insert(make_pair(proj.name, names_of_contris));
		proj.completed = true;
		return true;
	}

	return false;
}

void print_output()
{
	cout << output_map.size() << "\n";
	for (auto i : output_map)
	{
		cout << i.first << "\n";
		for (ll j = 0; j < i.second.size(); ++j)
			cout << i.second[j] << " ";

		cout << "\n";
	}
}

void solution()
{
	for (auto &i : projects_array)
	{
		if (select_project(i))
			current_day += i.duration;
	}
}

void solution2()
{
	vector<ll> days_until_next_proj_finishes;
	ll prev = -1, curr = 0;
	do
	{
		if (prev == curr)
		{
			sort(days_until_next_proj_finishes.begin(), days_until_next_proj_finishes.end());
			current_day = days_until_next_proj_finishes[0];
			days_until_next_proj_finishes.erase(days_until_next_proj_finishes.begin());
		}

		for (auto &i : projects_array)
		{
			if (select_project(i))
				days_until_next_proj_finishes.push_back(current_day + i.duration);
		}

		prev = curr;
		curr = days_until_next_proj_finishes.size();

	} while (!days_until_next_proj_finishes.empty());
}

int main()
{
	initializeIO();

	ll c, p;
	cin >> c >> p;

	for (ll i = 0; i < c; ++i)
	{
		contributer temp(i);
		contributers_array.push_back(temp);
	}

	for (ll i = 0; i < p; ++i)
	{
		project temp;
		projects_array.push_back(temp);
	}

	sort_global_skills_map();
	sort(projects_array.begin(), projects_array.end(), sort_project);
	solution2();
	print_output();

	return 0;
}