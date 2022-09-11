# Meeting Notes

In this file, you are required to take notes for your weekly meetings.
In each meeting, you are required to discuss:

1. What each member has done during the week?
2. Are there challenges or problems? Discuss the possible solutions
3. Plan for the next week for everyone
4. Deviations and changes to the project plan, if any

# Meeting 1.11.2021 16:00

**Participants**:

1. Prince
2. Milla
3. Hechukwedere
4. Oriyomi

## Summary of works

First meeting, no actual work done.

## Challenges

Questions that needs to check with Markus:

1. Should user be able to control the package size that are sent between Nodes?

2. Do Nodes need to manage the dataflow on both directions at the same time (receive/send)? My guess is that some multithreading would be needed in this case.

3. Should we start building the code with Qt from the start as we are planning to use that framework to build the GUI?

4. How can we add simple pipeline to our Aalto Gitlab for testing and building or what is the best practice in our case to ensure that master branch stays unbroken?

5. In this simulation, what is expected of the TCP/IP protocol implementation?

## Actions

1. Prince is going to write the Introduction and purpose part of the plan
2. Milla will write the scope of work
   monster classes.
3. Hechukwedere is going to write about requirements
4. Oriyomi will write about High Level structure

## Project status

Plan in progress. Meeting with Markus on Friday.

---

# Meeting 8.11.2021 20:00

**Participants**:

1. Prince
2. Milla
3. Hechukwedere
4. Oriyomi

## Summary of works

Project plan done and submittted, waiting for feedback. GUI base done by Prince. Other still trying to figure out how the project is structured.

## Challenges

Big picture seems confusing. Where should I start? How about tests and git branching? The team is not familiar with the Qt.

## Actions

Prince will implement “Ok” button so the Node can be added to the GUI.

Milla will familiarize herself with Qt and start adding functionalities, she will decide together with Prince.

Hechukwedere and Oriyomi will start implementing the classes that are defined in the project plan.

Everyone should read and understand the project plan throughly and study a little about Qt.

Git branches should be done by feature - small increments at the time.

## Project status

Still on early steps but started. Only some GUI parts are done, backend missing.

# Meeting 15.11.2021 15:00

**Participants**:

1. Prince
2. Milla
3. Hechukwedere
4. Oriyomi

## Summary of works

Prince:  
Done: Working on the UI side, collaborating with the team more and trying to get a grasp of the project. Worked together with Hechukwedere to refactor the project. They have been thinking of running the project on visual studio code.  
Next step: Have been trying to figure out how to add nodes to the canvas and already have an idea.

Hechukwedere:  
Done: Class bases for back end and unit tests (Simulator, Node classes). Experimented how to run the project on VS Code -> Qt build is slow and hard to use. Seems that team members have different Qt versions and they are not compatible with each other, project does not run for everyone. Maybe it would be better not use Qt design studio.
Next step: More classes to the backend.

Oriyomi: Made Packet class as defined in the project plan. Currently not in Finland, will come back soon. Going to add the code to git later and then collaborate with others. Project structure seems clearer now,  
Next step: Planning to add functionalities

Milla:  
Done: Big git clean up done, collaborating with the team about the implementation and helping with planning. Responsible for doing merges. Getting familiar with Qt, made dialog for adding link but it’s probably not going to be used due to switching to vs code environment.  
Next step: More researching need to be done before “real coding” can begin

## Challenges

The Qt seems frustrating to everyone and creates extra hassle and work.

## Actions

Prince will implement “Ok” button so the Node can be added to the GUI.

Milla will familiarize herself with Qt and start adding functionalities, she will decide together with Prince.

Hechukwedere and Oriyomi will start implementing the classes that are defined in the project plan.

Everyone should read and understand the project plan throughly and study a little about Qt.

Git branches should be done by feature - small increments at the time.

## Project status

Still on early steps but started. Only some GUI parts are done, backend missing.

# Meeting 23.11.2021 15:00

**Participants**:

1. Prince
2. Milla
3. Hechukwedere
4. Oriyomi

## Summary of works

Prince:  
Created control buttons. Working next on the drag and drop but need help with that -> not sure how to implement it. Need so research it.

Hechukwedere:  
Working on the console output that prints all the activities and information. Investigating how to implement a stream that could be used in a system. Will work with the canvas with Prince

Oriyomi:  
Just finished Link and Packet classes, will add it to git for review. Will implement the Router class next.

Milla:  
Continue working with the backend classes + unit tests for them. FindPath algorhitm etc.

## Challenges

No challenges, maybe just running out of time. Still so much to do and everyone is busy

## Actions

All classes need to be done this week so we can get to test them.

## Project status

Behind of original plan, things did not go as smoothly as planned originally. Qt created a lot of extra hours and pain.

# Meeting 30.11.2021 15:00

**Participants**:

1. Prince
2. Milla
3. Hechukwedere
4. Oriyomi

## Summary of works

Prince:  
Got stuck implementing drag and drop but Hechukwedere helped and some solution was found. Next working on the “Run” button that opens up a dialog where user can select what IP address is sending to what IP address.

Hechukwedere:  
Stream done for the GUI “console”. Drag and drop looking nice. Implementing the connection next between nodes so user can draw lines between them.

Oriyomi:  
Problems running the project locally, enountered some errors. Link, Router, Packet class bases done-> Milla will check the problems locally and merge if everything is ok. Will implement Router class further.

Milla:  
Backend implementation done further (+ tests), now waiting for the missing classes to do more. Node class needs Send/Receive packets. FindPath also needs to be figured out, thinking of using DFS..

## Challenges

Qt keeps being pain but team has done amazing job working around it. Everyone is super busy and stressed at the end of the period with huge work load.

## Project status

Soon we can start putting things together. Discussed already about the summary functionality.

# Meeting 7.12.2021 15:00

**Participants**:

1. Prince
2. Milla
3. Oriyomi

## Summary of works

Prince:  
Made button for summary, opens up a dialog for summary. We can present different numbers. Working with the link on GUI side together with Hechukwedere. They have some ideas and will compare them tomorrow.

Oriyomi:  
Implemented Router class. Thinking about the Packet class further. Maximum size of the packet is 1500 bytes.

Milla:  
Filled up a lot of functionalities to backend, soon in a state that can start integrating with GUI. Next need to calculate the packet sending as multithreading can become too hard and is out of scope of the course.

## Challenges

One team member is sick. Everyone still busy but doing great progress nevertheless. Team will have another meeting this week.
