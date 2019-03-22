Project1: Waht kinda typoz do people mak?

Overview
leveraging spelling correction methods over some given data, to identify the causes of typographical errors made by typical anthors, and to express the ensuing knowledge in a short technical/research report.

Marks
16/20

This README describes the data and codes for COMP90049 2018S2, Project 1. 
This archive contains eight files, of which the codes and test results for this Project.  
These files are described in more detail below.

All codes are written in C++ by myself.
Reference:
Nicholson, J., Zobel, J., & Verspoor, K. (2018) COMP90049: Approximate Matching, week 3 notes [PowerPoint slides]. 
	Retrieved from https://app.lms.unimelb.edu.au/bbcswebdav/pid-6595057-dt-content-rid-31507421_2/courses/COM
	P90049_2018_SM2/lectures/05-06-approx.pdf

  - GlobalEditDistance.cpp: The implementation of Levenshtein Distance.

  - GEDResults.txt: The test results of GlobalEditDistance.cpp. The Statistical data are appended at the end.

  - ImprovedGED.cpp: The implementation of improved Levenshtein Distance (adding operation "SWAP").

  - ImprovedGEDResults.txt: The test results of ImprovedGED.cpp. The Statistical data are appended at the end.

  - Soundex.cpp: The implementation of Soundex.

  - SoundexResult.txt: The test results of Soundex.cpp. The Statistical data are appended at the end.

  - GEDSoundex.cpp: The implementation of the Hybrid Method.

  - GEDSoundexResult.txt: The test results of GEDSoundex.cpp. The Statistical data are appended at the end.
