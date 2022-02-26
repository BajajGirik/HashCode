# PROJECTS

### SELECTION
	* if Completion_Date > Expiry_Date && Project Score - (Completed Date - Expiry Date) < 0
		- Not Selected
	* else
		- Can be postponed or Start Date = Current Date

### PRIORITY (BASIC)
	* if Expiry_Date - Duration (== Start_Date) is big
		- Priority is low
	* else
		- Priority is high

### SCORE CALCULATION

    * if Completion_Date > Expiry_Date
    	- Project Score - (Completed Date - Expiry Date)
    * else
    	- Project Score


# CONTRIBUTERS

### SELECTION

	* if (Free_Date < Proj_Start_Date && Skill_Level >= reqd_skill_level) ||
	  (skill level == reqd_skill_level-1 && any_contributor>=skill Level)
    	- Selected
		- Skill_Level += 1 if (Req_Skill_Level >= Skill_level)

    * else
        - Not Selected