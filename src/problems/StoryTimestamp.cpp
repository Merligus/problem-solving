#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

struct Meeting
{
	int personID1, personID2;
	int timestamp;

	Meeting()
	{
		personID1 = personID2 = -1;
		timestamp = -1;
	}
};

bool compareMeetingFunction(Meeting a, Meeting b)
{
	return a.timestamp < b.timestamp;
}

std::vector<int> WhoKnowsAboutTheStory(std::vector<Meeting> meetings, int firstIDWhoKnows, int maxID)
{
	std::vector<int> timeLearned;
	std::vector<int> peopleWhoKnow;
	for (int index = 0; index < maxID; index++)
		timeLearned.push_back(-1);
	timeLearned[--firstIDWhoKnows] = 0;

	std::sort(meetings.begin(), meetings.end(), compareMeetingFunction);
	for (Meeting meeting : meetings)
	{
		int id1 = meeting.personID1 - 1;
		int id2 = meeting.personID2 - 1;
		if (timeLearned[id1] != -1 && timeLearned[id1] <= meeting.timestamp) // id1 already knows
		{
			if (timeLearned[id1] > meeting.timestamp) // update id1 time
				timeLearned[id1] = meeting.timestamp;

			if (timeLearned[id2] > meeting.timestamp || timeLearned[id2] == -1) // id2 doesnt know
				timeLearned[id2] = meeting.timestamp;
		}

		if (timeLearned[id2] != -1 && timeLearned[id2] <= meeting.timestamp) // id2 already knows
		{
			if (timeLearned[id1] > meeting.timestamp || timeLearned[id1] == -1) // id1 doesnt know
				timeLearned[id1] = meeting.timestamp;

			if (timeLearned[id2] > meeting.timestamp) // update id1 time
				timeLearned[id2] = meeting.timestamp;
		}
	}

	for (int personID = 0; personID < timeLearned.size(); personID++)
		if (timeLearned[personID] != -1)
			peopleWhoKnow.push_back(personID + 1);

	return peopleWhoKnow;
}

int main_StoryTimestamp()
{
	std::vector<Meeting> meetings;
	int n, maxID(std::numeric_limits<int>::min());
	std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		Meeting meetingRead;
		std::cin >> meetingRead.personID1 >> meetingRead.personID2 >> meetingRead.timestamp;
		if (maxID < meetingRead.personID1)
			maxID = meetingRead.personID1;
		if (maxID < meetingRead.personID2)
			maxID = meetingRead.personID2;
		meetings.push_back(meetingRead);
	}
	int firstWhoKnows;
	std::cin >> firstWhoKnows;

	std::vector<int> peopleWhoKnows = WhoKnowsAboutTheStory(meetings, firstWhoKnows, maxID);
	for (int personID : peopleWhoKnows)
		std::cout << personID << std::endl;

	return 0;
}